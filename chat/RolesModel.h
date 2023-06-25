#ifndef CHAT_ROLESMODEL_H
#define CHAT_ROLESMODEL_H

#include "AssistantRole.h"

#include <QSqlTableModel>

namespace chat {

class RolesModel : public QSqlTableModel
{
public:
    explicit RolesModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    AssistantRole assistantRole(int row) const;
};

} // namespace chat

#endif // CHAT_ROLESMODEL_H
