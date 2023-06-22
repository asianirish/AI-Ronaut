#include "SystemMessageWidget.h"
#include "ui_SystemMessageWidget.h"

#include "chat/SessionManager.h"

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

void SystemMessageWidget::synchronizeCurrentSession(const QString &sessionId)
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

void SystemMessageWidget::initRoleList()
{
    _model = new SqlQueryModelExt(this);
    _model->setQuery("SELECT name, message FROM roles");

    ui->roleBox->setModel(_model);
    ui->roleBox->setModelColumn(0);

    ui->roleBox->setCurrentIndex(-1);

}

void SystemMessageWidget::on_roleBox_currentIndexChanged(int index)
{
    QVariant data = _model->data(_model->index(index, 0), SqlQueryModelExt::SecondColumnRole);
    ui->textEdit->setText(data.toString());
}


void SystemMessageWidget::on_saveRoleButton_clicked()
{
    QSqlQuery query;
    QString name(ui->roleBox->currentText());
    QString message(ui->textEdit->toPlainText());

    query.prepare("INSERT OR REPLACE INTO roles (name, message) "
                  "VALUES(:name, :message)");

    query.bindValue(":name", name);
    query.bindValue(":message", message);

    if (!query.exec()) {
        qDebug() << "error creating role:" << query.lastError().text();
        return;
    }

    _model->setQuery("SELECT name, message FROM roles");
    ui->roleBox->setCurrentText(name);
    ui->textEdit->setText(message);
}


void SystemMessageWidget::on_deleteRoleButton_clicked()
{
    QSqlQuery query;
    QString name(ui->roleBox->currentText());

    query.prepare("DELETE FROM roles WHERE name=:name");

    query.bindValue(":name", name);

    if (!query.exec()) {
        qDebug() << "error deliting role:" << query.lastError().text();
        return;
    }

    _model->setQuery("SELECT name, message FROM roles");
    ui->roleBox->setCurrentIndex(-1);
    ui->textEdit->clear();
}

