#ifndef CHAT_CHARACTERSMODEL_H
#define CHAT_CHARACTERSMODEL_H

#include "Character.h"

#include <QSqlQueryModel>

namespace chat {

class CharactersModel : public QSqlQueryModel
{
public:
    static const QString QUERY_STRING;

    explicit CharactersModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    
    Character character(int row) const;

    bool insertOrReplaceRecord(const QString &name, const QString &message, bool useNameInMessage = true);
    bool insertOrReplaceRecord(Character &character);

    bool removeRowByName(const QString &name);
};

} // namespace chat

#endif // CHAT_CHARACTERSMODEL_H
