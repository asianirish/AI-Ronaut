#include "ChatWidget.h"

#include "ErrorMessageItemWidget.h"
#include "UserMessageItemWidget.h"
#include "AIMessageItemWidget.h"

#include "chat/UserMessage.h"
#include "chat/AssistantMessage.h"
#include "chat/SessionManager.h"

#include "ui_ChatWidget.h"

#include "util/gfunc.h"

#include <QDebug>
#include <QListWidgetItem>
#include <QTimer>
#include <QKeyEvent>

using namespace oaic;

ChatWidget::ChatWidget(QWidget *parent) :
    QWidget(parent),
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
        ui->textEdit->setFocus(Qt::OtherFocusReason);
        return; // do not send an empty string
    }


    UserMessageItemWidget *itemWidget = new UserMessageItemWidget(this);
    addMessageItem(itemWidget, ui->textEdit->toPlainText());
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
        QTimer::singleShot(1, this, &ChatWidget::queryAiModel);
    }
}

void ChatWidget::queryAiModel()
{
    auto input = ui->textEdit->toPlainText();
    ui->textEdit->clear();

    qDebug() << "MODEL_NAME:" << _modelCntx->modelName();

    // ChatWidget don't care about sessions & the system message
    emit sendMessage(*_modelCntx, input);
}

void ChatWidget::onDeltaReady(const QString &deltaData)
{
    auto lastWidget = lastChatItemMessageWidget();
    auto aiWidget = qobject_cast<AIMessageItemWidget*>(lastWidget);

    if (aiWidget == nullptr) {
        aiWidget = new AIMessageItemWidget(this);
        _currentResponse = deltaData;
        addMessageItem(aiWidget, deltaData);
        QTimer::singleShot(1, this, &ChatWidget::adjustLastItem);
        return;
    }

    _currentResponse += deltaData;
    qDebug() << "DELTA:" << deltaData;
    qDebug() << "SUM:" << _currentResponse;

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

//void ChatWidget::on_isSessionBox_stateChanged(int isSession)
//{
//    if (isSession == Qt::Unchecked) {
////         gSessions->deselectSession();
//        ui->isSessionPersistentBox->setEnabled(false);
//    } else {

//        QString msg;

//        if (ui->listWidget->count()) {
//            UserMessageItemWidget *userWidget = lastChatItemMessageWidgetByType<UserMessageItemWidget>();

//            if (userWidget) {
//                msg = userWidget->text();
//            }

//        } else {
//            msg = ui->textEdit->toPlainText();
//        }

//        QString camelMsg;
//        if (!msg.isNull()) {
//            camelMsg = potato_util::phraseToCamelCase(msg, 7);
//        }

//        // TODO: from the beginning
//        gSessions->createSession(camelMsg);

//        // add last two messages to the current session
//        if (!msg.isEmpty()) {
//            gSessions->addMessage<chat::UserMessage>(msg);
//        }
//        if (!_currentResponse.isEmpty()) {
//            qDebug() << "_currentResponse:" << _currentResponse;
//            gSessions->addMessage<chat::AssistantMessage>(_currentResponse); // TODO: already empty after _currentResponse.clear();
//        }

//        ui->isSessionPersistentBox->setEnabled(true);

//        // TODO: set system message?
//        ui->textEdit->setFocus();
//    }
//}

void ChatWidget::onMessageResponseStream(const QStringList &deltaMessages)
{
    for (auto &delta : deltaMessages) {
        onDeltaReady(delta);
    }
}

void ChatWidget::onMessageResponseComplete(QObject *)
{
    gSessions->addMessage<chat::AssistantMessage>(_currentResponse);
    _currentResponse.clear();

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
}


void ChatWidget::on_newSessionButton_clicked()
{
    gSessions->createSession();
    ui->listWidget->clear();

    ui->textEdit->setFocus();
}

