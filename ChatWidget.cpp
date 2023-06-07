#include "ChatWidget.h"

#include "ErrorMessageItemWidget.h"
#include "UserMessageItemWidget.h"
#include "AIMessageItemWidget.h"

#include "chat/SessionManager.h"

#include "ui_ChatWidget.h"

#include <gfunc.h>

#include <QDebug>
#include <QListWidgetItem>
#include <QTimer>
#include <QKeyEvent>

using namespace oaic;

ChatWidget::ChatWidget(QWidget *parent) :
    ChatToolWidget(parent),
    ui(new Ui::ChatWidget),
    _modelCntx(nullptr),
    _client(nullptr)
{
    ui->setupUi(this);

    ui->textEdit->setTabChangesFocus(true);
}

ChatWidget::~ChatWidget()
{
    delete ui;
}

void ChatWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateItemsHeight();
}

void ChatWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {

        if (event->modifiers() & Qt::ControlModifier) {
            on_sendButton_clicked();
            return;
        }
    }

    QWidget::keyPressEvent(event);
}

void ChatWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    ui->textEdit->setFocus(Qt::OtherFocusReason);
}

void ChatWidget::on_sendButton_clicked()
{
    if (ui->textEdit->document()->isEmpty()) {
        // TODO: just forward the entire array of messages again in this case
        ui->textEdit->setFocus(Qt::OtherFocusReason);
        return; // do not send an empty string
    }

    auto input = ui->textEdit->toPlainText();

    UserMessageItemWidget *itemWidget = new UserMessageItemWidget(currentSessionId(), this);
    addMessageItem(itemWidget, input); // sets itemWidget text here
    itemWidget->refreshMsg(); // do not refresh in addMessageItem not to refresh after every delta!

    if (ui->listWidget->count() == 1) {
        auto camelInput = potato_util::phraseToCamelCase(input, 7);
        camelInput = camelInput.left(64);
        emit renameSession(camelInput);
        qDebug() << "LIST ITEM COUNT:" << ui->listWidget->count() << camelInput;
    }
}

void ChatWidget::adjustLastItem()
{
    auto cnt = ui->listWidget->count();
    auto item = ui->listWidget->item(cnt - 1);
    auto widget = ui->listWidget->itemWidget(item);
    auto chatWidget = qobject_cast<ChatItemWidget*>(widget);

    if (chatWidget) {
        int idealHeight = chatWidget->textHeight();
        item->setSizeHint({chatWidget->sizeHint().width(), idealHeight});
        ui->listWidget->scrollToBottom();
    }

    auto userWidget = qobject_cast<UserMessageItemWidget*>(widget);

    if (userWidget) {
        queryAiModel();
    }
}

void ChatWidget::queryAiModel()
{
    ui->textEdit->clear();

    emit sendCurrentSessionMessages(*_modelCntx);
}

void ChatWidget::onDeltaReady(const QString &deltaData)
{
    auto lastWidget = lastChatItemMessageWidget();
    auto aiWidget = qobject_cast<AIMessageItemWidget*>(lastWidget);

    if (aiWidget == nullptr) {
        aiWidget = new AIMessageItemWidget(currentSessionId(), this);
        addMessageItem(aiWidget, deltaData);
        QTimer::singleShot(1, this, &ChatWidget::adjustLastItem);
        return;
    }
    aiWidget->appendText(deltaData);
    QTimer::singleShot(1, this, &ChatWidget::adjustLastItem);
}

void ChatWidget::onDeltaError(const QString &deltaError)
{
    qDebug() << "ERROR:" << deltaError;
    ErrorMessageItemWidget *itemWidget = new ErrorMessageItemWidget(this);
    addMessageItem(itemWidget, deltaError);
}

ModelContext *ChatWidget::modelCntx() const
{
    return _modelCntx;
}

void ChatWidget::setModelCntx(ModelContext *newModelCntx)
{
    _modelCntx = newModelCntx;
}

void ChatWidget::updateItemsHeight()
{
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        auto item = ui->listWidget->item(i);
        auto widget = qobject_cast<ChatItemWidget*>(ui->listWidget->itemWidget(item));
        if (widget) {
            int idealHeight = widget->textHeight();
            item->setSizeHint({widget->sizeHint().width(), int(idealHeight)});
        }
    }
}

void ChatWidget::addMessageItem(ChatItemWidget *itemWidget, const QString &text)
{
    QListWidgetItem *listItem = new QListWidgetItem(ui->listWidget);

    ui->listWidget->addItem(listItem);
    ui->listWidget->setItemWidget(listItem, itemWidget);

    itemWidget->stylize();
    itemWidget->setText(text);

    itemWidget->setListItem(listItem);

    listItem->setSizeHint(itemWidget->sizeHint());

    QTimer::singleShot(1, this, &ChatWidget::adjustLastItem);
}

QWidget *ChatWidget::lastChatItemMessageWidget() const
{
    auto cnt = ui->listWidget->count();
    auto item = ui->listWidget->item(cnt - 1);
    return ui->listWidget->itemWidget(item);
//    auto chatWidget = qobject_cast<ChatItemWidget*>(widget);
}

void ChatWidget::onMessageResponseStream(const QStringList &deltaMessages)
{
    for (auto &delta : deltaMessages) {
        onDeltaReady(delta);
    }
}

void ChatWidget::onMessageResponseComplete(QObject *)
{
    auto lastItemWidget = lastChatItemMessageWidget();
    auto aiItemWidget = qobject_cast<AIMessageItemWidget*>(lastItemWidget);

    if (aiItemWidget) {
        aiItemWidget->refreshMsg();
    }

    qDebug() << "MESSAGE RESPONSE COMPLETE";
    ui->textEdit->setFocus();
}

oaic::Manager *ChatWidget::client() const
{
    return _client;
}

void ChatWidget::setClient(oaic::Manager *newClient)
{
    _client = newClient;

    // good place to connect the _client
    connect(_client->chat(), &oaic::Chat::messageResponseStream, this, &ChatWidget::onMessageResponseStream);
    connect(_client->chat(), &oaic::Component::replyDestroyed, this, &ChatWidget::onMessageResponseComplete);
    connect(_client->chat(), &oaic::Component::responseError, this, &ChatWidget::onDeltaError);

    connect(gSessions, &chat::SessionManager::sessionCreated, this, &ChatWidget::onSessionCreated);
}

void ChatWidget::synchronizeCurrentSession(const QString &sessionId)
{
    Q_UNUSED(sessionId);
    // TODO: display session(sessionId) messages
}

void ChatWidget::on_newSessionButton_clicked()
{
    QString sessionId = gSessions->createSession();

    setCurrentSessionId(sessionId);

    ui->listWidget->clear();

    ui->textEdit->setFocus();

    emit sessionChaged(sessionId);
}

void ChatWidget::onSessionCreated(const QString &sessionId)
{
    Q_UNUSED(sessionId);
    // TODO: NOT every session creation should cause this page current session changing!
}




void ChatWidget::on_abortChatButton_clicked()
{
    // TODO: place your chat abort code here (of current session!)
    qDebug() << "CHAT ABORT BUTTON CLICKED";
}

