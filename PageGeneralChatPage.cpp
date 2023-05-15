#include "PageGeneralChatPage.h"
#include "ui_PageGeneralChatPage.h"

PageGeneralChatPage::PageGeneralChatPage(QWidget *parent) :
    PageWidget(parent),
    ui(new Ui::PageGeneralChatPage)
{
    ui->setupUi(this);

    ui->chatConfigWidget->setModelCntx(&_modelCntx);
    ui->chatWidget->setModelCntx(&_modelCntx);

    ui->toolComboBox->addItem(tr("Model configuration"), 0);
    ui->toolComboBox->addItem(tr("Network configuration"), 1);
    ui->toolComboBox->addItem(tr("System message"), 2);
    ui->toolComboBox->addItem(tr("Sessions"), 3);
}

PageGeneralChatPage::~PageGeneralChatPage()
{
    delete ui;
}

void PageGeneralChatPage::updateCntx(AppContext *cntx)
{
    ui->chatConfigWidget->updateCntx(cntx);
    ui->chatWidget->setAppCntx(cntx);
    ui->networkConfigWidget->updateCntx(cntx);
}

void PageGeneralChatPage::on_toolComboBox_currentIndexChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

