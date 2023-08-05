/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#include "AIMessageItemWidget.h"

#include "ui_AIMessageItemWidget.h"

#include "chat/AssistantMessage.h"

AIMessageItemWidget::AIMessageItemWidget(const QString &sessionId, chat::MessagePtr msgPtr, QWidget *parent) :
    ChatSessionItemWidget(sessionId, msgPtr, parent),
    ui(new Ui::AIMessageItemWidget)
{
    ui->setupUi(this);

    addAction(ui->actionCopy);
    addAction(ui->actionEdit);
//    addAction(ui->actionSave_to_list);
//    addAction(ui->actionSave_to_file);
    addAction(ui->actionDelete);
}

AIMessageItemWidget::~AIMessageItemWidget()
{
    delete ui;
}

void AIMessageItemWidget::appendText(const QString &deltaText)
{
    QString prevText = textBrowser()->toPlainText();
    textBrowser()->setPlainText(prevText + deltaText);
}

QTextBrowser *AIMessageItemWidget::textBrowser() const
{
    return ui->textBrowser;
}

int AIMessageItemWidget::extraSpaceHeight() const
{
    auto topMargin = this->layout()->contentsMargins().top();

    auto bottomMargin = this->layout()->contentsMargins().bottom();

    // TODO: what is the magic number for?
    return topMargin + bottomMargin + 4; // TODO: other controls
}

chat::Message *AIMessageItemWidget::createMessage() const
{
    return new chat::AssistantMessage();
}

void AIMessageItemWidget::on_actionCopy_triggered()
{
    onCopyAction();
}


void AIMessageItemWidget::on_actionEdit_triggered()
{
    editMessage();
}


void AIMessageItemWidget::on_textBrowser_textChanged()
{
    adjustHeight();
}


void AIMessageItemWidget::on_actionDelete_triggered()
{
    emit deleteMe();
}

