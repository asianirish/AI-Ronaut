#include "PageDonatePage.h"
#include "ui_PageDonatePage.h"

PageDonatePage::PageDonatePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageDonatePage)
{
    ui->setupUi(this);
}

PageDonatePage::~PageDonatePage()
{
    delete ui;
}
