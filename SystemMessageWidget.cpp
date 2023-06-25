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

QString SystemMessageWidget::systemMessage() const
{
    QString sysMsg;

    QString name = ui->roleBox->currentText();
    QString role = ui->textEdit->toPlainText();

    if (name.isEmpty() && role.isEmpty()) {
        return QString();
    } else if (name.isEmpty()) {
        sysMsg = role;
    } else {
        sysMsg = name + ", " + role;
    }

    return sysMsg;
}

void SystemMessageWidget::synchronizeCurrentSession()
{
    auto sessionId = pageContext()->currentSessionId();

    qDebug() << "SYSTEM MESSAGE SESSION ID:" << sessionId;

    auto session = gSessions->session(sessionId);
    auto msg = session->systemMessage();

    qDebug() << "SYSTEM MESSAGE:" << msg.text();

    // TODO: role attrs (not only just a message text)
    ui->textEdit->setText(msg.text());
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
    QSqlQuery query;
    QString name(ui->roleBox->currentText());

    // TODO: inside the model class
    query.prepare("DELETE FROM roles WHERE name=:name");

    query.bindValue(":name", name);

    if (!query.exec()) {
        qDebug() << "error deliting role:" << query.lastError().text();
        return;
    }

    _model->select();
    ui->roleBox->setCurrentIndex(-1);
    ui->textEdit->clear();
}


void SystemMessageWidget::on_clearButton_clicked()
{
    ui->roleBox->clearEditText();
    ui->textEdit->clear();
}

