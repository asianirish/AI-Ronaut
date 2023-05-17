#include "PageAboutPage.h"
#include "ui_PageAboutPage.h"

#include <QDesktopServices>

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

void PageAboutPage::on_commandLinkButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/asianirish/AI-Ronaut"));
}

