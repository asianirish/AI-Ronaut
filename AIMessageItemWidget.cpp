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

