#include "UserMessageItemWidget.h"
#include "ui_UserMessageItemWidget.h"

#include "chat/UserMessage.h"

#include <QAbstractTextDocumentLayout>

UserMessageItemWidget::UserMessageItemWidget(const QString &sessionId, QWidget *parent) :
    ChatSessionItemWidget(sessionId, parent),
    ui(new Ui::UserMessageItemWidget)
{
    ui->setupUi(this);

    addAction(ui->actionCopy);
    addAction(ui->actionEdit);
    addAction(ui->actionDelete);
}

UserMessageItemWidget::~UserMessageItemWidget()
{
    delete ui;
}

QTextBrowser *UserMessageItemWidget::textBrowser() const
{
    return ui->textBrowser;
}

int UserMessageItemWidget::extraSpaceHeight() const
{
    auto topMargin = this->layout()->contentsMargins().top();

    auto bottomMargin = this->layout()->contentsMargins().bottom();

    // TODO: what is the magic number for?
    return topMargin + bottomMargin + 4; // TODO: other controls
}

chat::Message *UserMessageItemWidget::createMessage() const
{
    return new chat::UserMessage();
}


void UserMessageItemWidget::on_actionCopy_triggered()
{
    onCopyAction();
}


void UserMessageItemWidget::on_actionEdit_triggered()
{
    editMessage();
}


void UserMessageItemWidget::on_textBrowser_textChanged()
{
    adjustHeight();
}


void UserMessageItemWidget::on_actionDelete_triggered()
{
    emit deleteMe();
}

