#include "SystemMessageWidget.h"
#include "ui_SystemMessageWidget.h"

#include "chat/SessionManager.h"

SystemMessageWidget::SystemMessageWidget(QWidget *parent) :
    ChatToolWidget(parent),
    ui(new Ui::SystemMessageWidget)
{
    ui->setupUi(this);
}

SystemMessageWidget::~SystemMessageWidget()
{
    delete ui;
}

QString SystemMessageWidget::systemMessage() const
{
    QString msg = ui->textEdit->toPlainText();
    if (msg.isEmpty()) {
        msg = ui->textEdit->placeholderText();
    }
    return msg;
}

void SystemMessageWidget::updateCurrentSession(const QString &sessionId)
{
    auto session = gSessions->session(sessionId);
    auto msg = session->systemMessage();
    ui->textEdit->setText(msg.text());
}

void SystemMessageWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    ui->textEdit->setFocus();
}
