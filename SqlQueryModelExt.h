#ifndef SQLQUERYMODELEXT_H
#define SQLQUERYMODELEXT_H

#include <QSqlQueryModel>

class SqlQueryModelExt : public QSqlQueryModel
{
public:
    explicit SqlQueryModelExt(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    enum CustomRoles {
        SecondColumnRole = Qt::UserRole + 1
    };
};

#endif // SQLQUERYMODELEXT_H
