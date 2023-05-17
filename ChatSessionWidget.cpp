#include "ChatSessionWidget.h"
#include "ui_ChatSessionWidget.h"

ChatSessionWidget::ChatSessionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatSessionWidget)
{
    ui->setupUi(this);
}

ChatSessionWidget::~ChatSessionWidget()
{
    delete ui;
}
