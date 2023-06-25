#include "RolesModel.h"

#include <QSqlRecord>

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

} // namespace chat
