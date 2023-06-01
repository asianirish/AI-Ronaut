#include "PageGeneralChatPage.h"
#include "ui_PageGeneralChatPage.h"

#include "chat/SessionManager.h"

PageGeneralChatPage::PageGeneralChatPage(QWidget *parent) :
    PageWidget(parent),
    ui(new Ui::PageGeneralChatPage)
{
    ui->setupUi(this);

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
    connect(this, &PageGeneralChatPage::sendSingleMessage, client->chat(), &oaic::Chat::onSingleMessageSent);
    // TODO: connect sendSessionMessages


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
    auto sm = chat::SessionManager::instance();

    if (sm->isSession()) {
        auto session = sm->currentSession();
        auto messages = session->msgDataList();
        emit sendSessionMessages(modelCntx, messages);
    } else {
        emit sendSingleMessage(modelCntx, message, systemMessage);
    }
}

