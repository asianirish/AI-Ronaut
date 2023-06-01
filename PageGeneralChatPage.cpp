#include "PageGeneralChatPage.h"
#include "ui_PageGeneralChatPage.h"

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
    // TODO: connect to SystemMEssageWidget and resend with a system message, not directly with oaic::Chat
    connect(ui->chatWidget, &ChatWidget::sendSingleMessage, client->chat(), &oaic::Chat::onSingleMessageSent);

    // TODO: ui->systemMessageWidget
    // TODO: connect(ui->chatWidget, &ChatWidget::sendSingleMessage, ui->systemMessageWidget, ...


    ui->chatWidget->setClient(client);
    ui->chatConfigWidget->updateClient(client);
}

void PageGeneralChatPage::changeCurrentToolPage(int index)
{
    ui->tabWidget->setCurrentIndex(index);
}

