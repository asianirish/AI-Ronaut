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

    ui->abortChatButton->setHidden(true);
    ui->textEdit->setTabChangesFocus(true);

    addAction(ui->actionDelete_Item);
    addAction(ui->actionEditItem);

    connect(gSessions, &chat::SessionManager::sessionDeleted, this, &ChatWidget::onSessionDeleted);

    ui->newSessionButton->setHidden(true);

    on_textEdit_textChanged();
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

//void ChatWidget::keyPressEvent(QKeyEvent *event)
//{
//    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {

//        if (event->modifiers() & Qt::ControlModifier) {
//            on_sendButton_clicked();
//            return;
//        }
//    }

//    QWidget::keyPressEvent(event);
//}

void ChatWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    ui->textEdit->setFocus(Qt::OtherFocusReason);
}

void ChatWidget::on_sendButton_clicked()
{
    if (ui->textEdit->document()->isEmpty()) {
        if (ui->textEdit->hasFocus() || ui->sendButton->hasFocus()) {
            continueChat();
        } else {
            ui->textEdit->setFocus(Qt::OtherFocusReason);
        }
        return; // do not send an empty string
    }

    auto input = ui->textEdit->toPlainText();

    UserMessageItemWidget *itemWidget = createMessageItemWidget<UserMessageItemWidget>(input);

    itemWidget->refreshMsg(); // do not refresh in addMessageItem not to refresh after every delta!

    if (ui->listWidget->count() <= 2) {
        auto camelInput = potato_util::phraseToCamelCase(input, 7);
        camelInput = camelInput.left(64);

        auto sessionId = pageContext()->currentSessionId();
        auto session = gSessions->session(sessionId);
        auto characterName = session->character().name();

        QString sessionName;
        if (!characterName.isEmpty()) {
            characterName = potato_util::phraseToCamelCase(characterName, 7);
            sessionName = characterName + "_";
        }

        sessionName += camelInput;

        emit renameSession(sessionName);
    }

    enableOrDisableControls(true);

    sendAiModelRequest();
}

void ChatWidget::sendAiModelRequest()
{
    ui->textEdit->clear();

    emit sendCurrentSessionMessages(*_modelCntx);
}

void ChatWidget::onDeltaReady(const QString &deltaData)
{
    auto lastWidget = lastChatItemMessageWidget();
    auto aiWidget = qobject_cast<AIMessageItemWidget*>(lastWidget);

    if (aiWidget == nullptr) {
        aiWidget = createMessageItemWidget<AIMessageItemWidget>(deltaData);

        aiWidget->callAdjustHeight();
        return;
    }
    aiWidget->appendText(deltaData);
    aiWidget->callAdjustHeight();
    ui->listWidget->scrollToBottom();
}

void ChatWidget::enableOrDisableControls(bool isSending)
{
    ui->textEdit->setDisabled(isSending);
    ui->sendButton->setHidden(isSending);
    ui->newSessionButton->setDisabled(isSending);

    ui->abortChatButton->setVisible(isSending);

    // TODO: emit for other widgets of this page
}

void ChatWidget::continueChat()
{
    enableOrDisableControls(true);
    sendAiModelRequest();
}

void ChatWidget::onDeltaError(const QString &deltaError)
{
    qDebug() << "ERROR:" << deltaError;
    ErrorMessageItemWidget *itemWidget = new ErrorMessageItemWidget(this);
    connect(itemWidget, &ErrorMessageItemWidget::deleteMe, this, &ChatWidget::onDeleteItemRequest);
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

    itemWidget->callAdjustHeight();
    ui->listWidget->scrollToBottom();
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

    enableOrDisableControls(false);
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

void ChatWidget::synchronizeCurrentSession()
{
    auto sessionId = pageContext()->currentSessionId();
    qDebug() << "\nSYNCHRONIZE_CURRENT_SESSION:" << sessionId;

    ui->listWidget->clear();

    auto session = gSessions->session(sessionId);

    auto lst = session->messageList();

    for (auto &msgPtr : lst) {
        qDebug() << "CURRENT_SESSION CHAT MESSAGE:" << msgPtr->role() << ":" << msgPtr->text();
        ChatSessionItemWidget *itemWidget = nullptr;
        if (msgPtr->role() == chat::Message::USER) {
            itemWidget = createMessageItemWidget<UserMessageItemWidget>(msgPtr->text(), msgPtr);
        } else if (msgPtr->role() == chat::Message::ASSISTANT) {
            itemWidget = createMessageItemWidget<AIMessageItemWidget>(msgPtr->text(), msgPtr);
        }

        if (itemWidget) {
            itemWidget->refreshMsg();
            itemWidget->callAdjustHeight();
        }
    }

    ui->listWidget->scrollToBottom();
    ui->textEdit->setFocus();

}

void ChatWidget::onSessionCreatedSpecific(int pageIndex, const QString &newSessionId)
{
    Q_UNUSED(pageIndex)
    Q_UNUSED(newSessionId)
//    qDebug() << "ChatWidget CREATE SESSION ON PAGE:" << pageIndex << "NEW SESSION:" << newSessionId;
}

void ChatWidget::on_newSessionButton_clicked()
{
    QString sessionId = gSessions->createSession(pageContext()->pageIndex());

    pageContext()->setCurrentSessionId(sessionId);

    ui->listWidget->clear();

    ui->textEdit->setFocus();

    emit sessionChaged();
}

void ChatWidget::on_abortChatButton_clicked()
{
    _client->chat()->abortCurrentResponse();
}

void ChatWidget::onDeleteItemRequest()
{
    on_actionDelete_Item_triggered();
}


void ChatWidget::on_actionDelete_Item_triggered()
{
    auto item = ui->listWidget->currentItem();
    if (item) {
        auto itemWidget = ui->listWidget->itemWidget(item);
        auto chatItemWidget = qobject_cast<ChatSessionItemWidget *>(itemWidget);

        if (chatItemWidget) {
            chatItemWidget->deleteMessage();
        }

        ui->listWidget->removeItemWidget(item);
        delete item;
    }
}


void ChatWidget::on_actionEditItem_triggered()
{
    auto item = ui->listWidget->currentItem();
    if (item) {
        auto itemWidget = ui->listWidget->itemWidget(item);
        auto chatItemWidget = qobject_cast<ChatSessionItemWidget *>(itemWidget);

        if (chatItemWidget) {
            chatItemWidget->editMessage();
        }

    }
}

void ChatWidget::onSessionDeleted(int pageIndex, const QString sessionId)
{
    qDebug() << pageIndex << "vs." << pageContext()->pageIndex();
    qDebug() << sessionId << "vs." << pageContext()->currentSessionId();
    qDebug() << "......................................................";

    // session id can be just created
    if (pageIndex == pageContext()->pageIndex()) {

        if (sessionId == pageContext()->currentSessionId()) {
            ui->listWidget->clear();
        }

        ui->textEdit->setFocus();
    }

}

void ChatWidget::on_textEdit_textChanged()
{
    auto doc = ui->textEdit->document();
    int newHeight = doc->size().toSize().height();
    ui->textEdit->setFixedHeight(newHeight);

    ui->messageWidget->setFixedHeight(newHeight + MSG_WIDGET_EXTRA_HEIGHT);
}

