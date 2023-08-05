/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#include "PagePlotPage.h"
#include "ui_PagePlotPage.h"

PagePlotPage::PagePlotPage(QWidget *parent) :
    PageWidget(parent),
    ui(new Ui::PagePlotPage)
{
    ui->setupUi(this);
}

PagePlotPage::~PagePlotPage()
{
    delete ui;
}

void PagePlotPage::synchronizeClient(oaic::Manager *_client)
{
    Q_UNUSED(_client)
    // TODO: do nothing?
}
