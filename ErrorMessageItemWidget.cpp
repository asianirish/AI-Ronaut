/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#include "ErrorMessageItemWidget.h"
#include "ui_ErrorMessageItemWidget.h"

ErrorMessageItemWidget::ErrorMessageItemWidget(QWidget *parent) :
    ChatItemWidget(parent),
    ui(new Ui::ErrorMessageItemWidget)
{
    ui->setupUi(this);

    addAction(ui->actionCopy);
    addAction(ui->actionDelete);
}

ErrorMessageItemWidget::~ErrorMessageItemWidget()
{
    delete ui;
}

QTextBrowser *ErrorMessageItemWidget::textBrowser() const
{
    return ui->textBrowser;
}

int ErrorMessageItemWidget::extraSpaceHeight() const
{
    auto topMargin = this->layout()->contentsMargins().top();

    auto bottomMargin = this->layout()->contentsMargins().bottom();

    return topMargin + bottomMargin;
}

void ErrorMessageItemWidget::on_actionCopy_triggered()
{
    onCopyAction();
}


void ErrorMessageItemWidget::on_actionDelete_triggered()
{
    emit deleteMe();
}

