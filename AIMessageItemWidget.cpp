#include "AIMessageItemWidget.h"
#include "ui_AIMessageItemWidget.h"

AIMessageItemWidget::AIMessageItemWidget(QWidget *parent) :
    ChatItemWidget(parent),
    ui(new Ui::AIMessageItemWidget)
{
    ui->setupUi(this);
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
