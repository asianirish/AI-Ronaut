#include "ErrorMessageItemWidget.h"
#include "ui_ErrorMessageItemWidget.h"

ErrorMessageItemWidget::ErrorMessageItemWidget(QWidget *parent) :
    ChatItemWidget(parent),
    ui(new Ui::ErrorMessageItemWidget)
{
    ui->setupUi(this);

    addAction(ui->actionCopy);
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

