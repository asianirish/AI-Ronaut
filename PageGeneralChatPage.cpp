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
    ui->chatWidget->setClient(client);
    ui->chatConfigWidget->updateClient(client);
}

void PageGeneralChatPage::changeCurrentToolPage(int index)
{
    ui->tabWidget->setCurrentIndex(index);
}

