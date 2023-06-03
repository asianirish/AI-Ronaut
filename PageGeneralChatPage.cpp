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
    gSessions->createSession();

    ui->chatConfigWidget->setModelCntx(&_modelCntx);
    ui->chatWidget->setModelCntx(&_modelCntx);
}

PageGeneralChatPage::~PageGeneralChatPage()
{
    delete ui;
}

void PageGeneralChatPage::updateClient(oaic::Manager *client)
{
//    connect(ui->chatWidget, &ChatWidget::sendMessage, client->chat(), &oaic::Chat::onSingleMessageSent);
    connect(ui->chatWidget, &ChatWidget::sendMessage, this, &PageGeneralChatPage::onUserMessage);

    // TODO: do not connect to to oaic::Chat but call SessionManager functions
    connect(this, &PageGeneralChatPage::sendSessionMessages, client->chat(), &oaic::Chat::onSessionMessagesSent);

    ui->chatWidget->setClient(client);
    ui->chatConfigWidget->updateClient(client);
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
    gSessions->addMessage<chat::SystemMessage>(systemMessage); // special case

    gSessions->addMessage<chat::UserMessage>(message);
    // TODO: move to ChatWidget (?)

    auto messages = gSessions->currentSession()->msgDataList();
    emit sendSessionMessages(modelCntx, messages);

//    else {
//        emit sendSingleMessage(modelCntx, message, systemMessage);
//    }
}

