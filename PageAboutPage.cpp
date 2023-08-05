/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

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

