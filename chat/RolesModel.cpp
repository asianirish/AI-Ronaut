#include "RolesModel.h"

#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>

namespace chat {

RolesModel::RolesModel(QObject *parent) : QSqlTableModel(parent)
{
    setTable("roles");
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();
}

QVariant RolesModel::data(const QModelIndex &index, int role) const
{
    /*
    if (!index.isValid() || index.row() >= rowCount()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        QString columnName = headerData(index.column(), Qt::Horizontal, Qt::DisplayRole).toString();
        int columnIndex = record().indexOf(columnName);
        return QSqlTableModel::data(index.sibling(index.row(), columnIndex), role);
    }

    return QSqlTableModel::data(index, role);
    */
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        return QSqlTableModel::data(index, role);
    }

    return QVariant();
}

AssistantRole RolesModel::assistantRole(int row) const
{
    if (row < 0 || row >= rowCount()) {
        return AssistantRole();
    }

    QModelIndex nameIndex = index(row, 1);
    QModelIndex messageIndex = index(row, 2);

    QString name = data(nameIndex).toString();
    QString message = data(messageIndex).toString();

    AssistantRole role;
    role.setName(name);
    role.setMessage(message);

    return role;
}

bool RolesModel::insertOrReplaceRecord(const QString &name, const QString &message)
{
    QSqlQuery query(database());
    QString queryString;
    QString dbType = database().driverName();

    if (dbType == "QSQLITE") {
        queryString = "INSERT OR REPLACE INTO roles (name, message) VALUES(:name, :message)";
    } else if (dbType == "QMYSQL") {
        queryString = "INSERT INTO roles (name, message) VALUES(:name, :message) "
                      "ON DUPLICATE KEY UPDATE name = VALUES(name), message = VALUES(message)";
    } else if (dbType == "QPSQL") {
        queryString = "INSERT INTO roles (name, message) VALUES(:name, :message) "
                      "ON CONFLICT (name) DO UPDATE SET message = EXCLUDED.message";
    } else {
        // TODO: use model functions
        qDebug() << "Unsupported database type:" << dbType;
        return false;
    }

    query.prepare(queryString);
    query.bindValue(":name", name);
    query.bindValue(":message", message);

    if (query.exec()) {
        qDebug() << "Record successfully added or updated.";
        select(); // Update the model after changes in the database
        return true;
    } else {
        qDebug() << "Query execution error: " << query.lastError().text();
        return false;
    }
}

bool RolesModel::insertOrReplaceRecord(const AssistantRole &role)
{
    return insertOrReplaceRecord(role.name(), role.message());
}

} // namespace chat
