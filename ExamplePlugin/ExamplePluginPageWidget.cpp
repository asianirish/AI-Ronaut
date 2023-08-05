/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#include "ExamplePluginPageWidget.h"
#include "ui_ExamplePluginPageWidget.h"

ExamplePluginPageWidget::ExamplePluginPageWidget(QWidget *parent) :
    PageWidget(parent),
    ui(new Ui::ExamplePluginPageWidget)
{
    ui->setupUi(this);
}

ExamplePluginPageWidget::~ExamplePluginPageWidget()
{
    delete ui;
}

void ExamplePluginPageWidget::synchronizeClient(oaic::Manager *client)
{
    Q_UNUSED(client)
    // DO NOTHING
}
