#include "SystemMessageWidget.h"
#include "ui_SystemMessageWidget.h"

SystemMessageWidget::SystemMessageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemMessageWidget)
{
    ui->setupUi(this);
}

SystemMessageWidget::~SystemMessageWidget()
{
    delete ui;
}

void SystemMessageWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    ui->textEdit->setFocus();
}
