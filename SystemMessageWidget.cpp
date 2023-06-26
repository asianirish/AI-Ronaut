#include "SystemMessageWidget.h"
#include "ui_SystemMessageWidget.h"

#include "chat/SessionManager.h"
#include "chat/AssistantRole.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

SystemMessageWidget::SystemMessageWidget(QWidget *parent) :
    ChatToolWidget(parent),
    ui(new Ui::SystemMessageWidget)
{
    ui->setupUi(this);

    initRoleList();
}

SystemMessageWidget::~SystemMessageWidget()
{
    delete ui;
}

chat::AssistantRole SystemMessageWidget::role() const
{
    QString name = ui->roleBox->currentText();
    QString message = ui->textEdit->toPlainText();

    return chat::AssistantRole(name, message);
}

void SystemMessageWidget::synchronizeCurrentSession()
{
    auto sessionId = pageContext()->currentSessionId();

    qDebug() << "SYSTEM MESSAGE SESSION ID:" << sessionId;

    auto session = gSessions->session(sessionId);
//    auto msg = session->systemMessage();
    auto role = session->role();

    qDebug() << "SYSTEM MESSAGE:" << role.fullMessage();

    ui->textEdit->setText(role.message());
    ui->roleBox->setEditText(role.name());
}

void SystemMessageWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    ui->textEdit->setFocus();
}

void SystemMessageWidget::initRoleList()
{
    _model = new chat::RolesModel(this);

    ui->roleBox->setModel(_model);
    ui->roleBox->setModelColumn(1); // TODO: inside the model class

    ui->roleBox->setCurrentIndex(-1);

}

void SystemMessageWidget::on_roleBox_currentIndexChanged(int index)
{
//    QVariant data = _model->data(_model->index(index, 2));
    auto role = _model->assistantRole(index);
    ui->textEdit->setText(role.message());
}


void SystemMessageWidget::on_saveRoleButton_clicked()
{
    QString name(ui->roleBox->currentText());
    QString message(ui->textEdit->toPlainText());

    _model->insertOrReplaceRecord(name, message);

    ui->roleBox->setCurrentText(name);
    ui->textEdit->setText(message);
}


void SystemMessageWidget::on_deleteRoleButton_clicked()
{
    QString name(ui->roleBox->currentText());

    _model->removeRowByName(name);

    ui->roleBox->setCurrentIndex(-1);
    ui->textEdit->clear();
}


void SystemMessageWidget::on_clearButton_clicked()
{
    ui->roleBox->clearEditText();
    ui->textEdit->clear();
}

