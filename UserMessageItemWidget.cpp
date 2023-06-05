#include "UserMessageItemWidget.h"
#include "ui_UserMessageItemWidget.h"

#include <QAbstractTextDocumentLayout>

UserMessageItemWidget::UserMessageItemWidget(QWidget *parent) :
    ChatSessionItemWidget(parent),
    ui(new Ui::UserMessageItemWidget)
{
    ui->setupUi(this);

    addAction(ui->actionCopy);
    addAction(ui->actionEdit);
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


void UserMessageItemWidget::on_actionCopy_triggered()
{
    onCopyAction();
}

