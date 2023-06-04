#include "PageGeneralChatPage.h"
#include "ui_PageGeneralChatPage.h"

#include "chat/SessionManager.h"
#include "chat/UserMessage.h"

PageGeneralChatPage::PageGeneralChatPage(QWidget *parent) :
    PageWidget(parent),
    ui(new Ui::PageGeneralChatPage)
{
    ui->setupUi(this);

    // good place to create a session (TODO: rename on the first message using CamelCase)
    _currentSessionId = gSessions->createSession();
    ui->chatWidget->setCurrentSessionId(_currentSessionId);
    ui->chatSessionWidget->setCurrentSessionId(_currentSessionId);
    ui->systemMessageWidget->setCurrentSessionId(_currentSessionId);
    ui->chatConfigWidget->setCurrentSessionId(_currentSessionId); // TODO: tries to read model context from the session!

    // connect sessionChage with onSessionChage
    // ChatSessionWidget::onSessionChanged does nothing because ChatSessionWidget changes sessions itself
    // ChatSessionWidget::onSessionCreated connected with chat::SessionManager::sessionCreated
    connect(ui->chatWidget, &ChatWidget::sessionChaged, ui->systemMessageWidget, &SystemMessageWidget::onCurrentSessionChange);
    connect(ui->chatWidget, &ChatWidget::sessionChaged, ui->chatConfigWidget, &ChatConfigWidget::onCurrentSessionChange);

    connect(ui->chatWidget, &ChatWidget::sessionChaged, this, &PageGeneralChatPage::onCurrentSessionChange);

    // TODO: implement & connect ChatSessionWidget signals

    // TODO: connect to change _currentSessionId of this

    ui->chatConfigWidget->setModelCntx(&_modelCntx);
    ui->chatWidget->setModelCntx(&_modelCntx);
}

PageGeneralChatPage::~PageGeneralChatPage()
{
    delete ui;
}

void PageGeneralChatPage::synchronizeClient(oaic::Manager *client)
{
//    connect(ui->chatWidget, &ChatWidget::sendMessage, client->chat(), &oaic::Chat::onSingleMessageSent);
    connect(ui->chatWidget, &ChatWidget::sendMessage, this, &PageGeneralChatPage::onUserMessage);

    // TODO: do not connect to to oaic::Chat but call SessionManager functions
    connect(this, &PageGeneralChatPage::sendSessionMessages, client->chat(), &oaic::Chat::onSessionMessagesSent);

    ui->chatWidget->setClient(client);
    ui->chatConfigWidget->synchronizeClient(client);
}

void PageGeneralChatPage::changeCurrentToolPage(int index)
{
    ui->tabWidget->setCurrentIndex(index);
}

void PageGeneralChatPage::onUserMessage(const oaic::ModelContext &modelCntx, const QString &message)
{
    QString systemMessage = ui->systemMessageWidget->systemMessage();
    qDebug() << "SYSTEM_MESSAGE:" << systemMessage;


    // TODO: call oaic::Chat from SessionManager
    gSessions->addMessage<chat::SystemMessage>(systemMessage, _currentSessionId); // special case

    gSessions->addMessage<chat::UserMessage>(message, _currentSessionId);
    // TODO: move to ChatWidget (?)

    auto messages = gSessions->session(_currentSessionId)->msgDataList();
    emit sendSessionMessages(modelCntx, messages);

//    else {
//        emit sendSingleMessage(modelCntx, message, systemMessage);
    //    }
}

void PageGeneralChatPage::onCurrentSessionChange(const QString &sessionId)
{
    _currentSessionId = sessionId;
}

