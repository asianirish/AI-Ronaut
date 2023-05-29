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

void PageGeneralChatPage::updateCntx(AppContext *cntx)
{
    ui->chatConfigWidget->updateCntx(cntx);
    ui->chatWidget->setAppCntx(cntx);
}

void PageGeneralChatPage::updateClient(oaic::Manager *_client)
{

}

void PageGeneralChatPage::changeCurrentToolPage(int index)
{
    ui->tabWidget->setCurrentIndex(index);
}

