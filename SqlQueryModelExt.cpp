#include "SqlQueryModelExt.h"

SqlQueryModelExt::SqlQueryModelExt(QObject *parent)
    : QSqlQueryModel{parent}
{

}

QVariant SqlQueryModelExt::data(const QModelIndex &index, int role) const
{
    if (role == SecondColumnRole) {
        QModelIndex secondColumnIndex = QSqlQueryModel::index(index.row(), 1);
        return QSqlQueryModel::data(secondColumnIndex);
    }

    return QSqlQueryModel::data(index, role);
}
