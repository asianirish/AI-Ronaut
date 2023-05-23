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

void ChatSessionWidget::on_startSessionBox_stateChanged(int state)
{
    if (state) {
        ui->sessionFrame->setEnabled(true);
    } else {
        ui->sessionFrame->setEnabled(false);
    }
}

