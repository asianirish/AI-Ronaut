#include "PageAboutPage.h"
#include "ui_PageAboutPage.h"

PageAboutPage::PageAboutPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageAboutPage)
{
    ui->setupUi(this);
}

PageAboutPage::~PageAboutPage()
{
    delete ui;
}
