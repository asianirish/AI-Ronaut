#include "CharactersModel.h"

#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>


namespace chat {

const QString CharactersModel::QUERY_STRING = "SELECT * FROM characters ORDER BY name";


CharactersModel::CharactersModel(QObject *parent) : QSqlQueryModel(parent)
{
    setQuery(QUERY_STRING);
//    setEditStrategy(QSqlTableModel::OnManualSubmit);

}

QVariant CharactersModel::data(const QModelIndex &index, int role) const
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
        return QSqlQueryModel::data(index, role);
    }

    return QVariant();
}

Character CharactersModel::character(int row) const
{
    if (row < 0 || row >= rowCount()) {
        return Character();
    }

    QModelIndex idIndex = index(row, 0);
    QModelIndex nameIndex = index(row, 1);
    QModelIndex messageIndex = index(row, 2);

    int id = data(idIndex).toInt();
    QString name = data(nameIndex).toString();
    QString message = data(messageIndex).toString();

    Character character;
    character.setId(id);
    character.setName(name);
    character.setMessage(message);

    return character;
}

bool CharactersModel::insertOrReplaceRecord(const QString &name, const QString &message, bool useNameInMessage)
{
    Character character(name, message, useNameInMessage);
    return insertOrReplaceRecord(character);
}

bool CharactersModel::insertOrReplaceRecord(Character &character)
{
    if (character.save()) {
        setQuery(QUERY_STRING); // Update the model after changes in the database
        return true;
    }

    return false;
}

bool CharactersModel::removeRowByName(const QString &name)
{
    QSqlQuery query(QSqlDatabase::database());
    query.prepare("DELETE FROM characters WHERE name = :name");
    query.bindValue(":name", name);

    if (!query.exec()) {
        qDebug() << "Error deleting row by name:" << query.lastError();
        return false;
    }

    setQuery(QUERY_STRING); // Update the model after changes in the database
    return true;

/* native methods:
    int nameColumn = fieldIndex("name");
    if (nameColumn == -1) {
        qDebug() << "Error: column 'name' not found";
        return false;
    }

    QModelIndexList matches = match(index(0, nameColumn), Qt::DisplayRole, name, 1, Qt::MatchExactly);
    if (!matches.isEmpty()) {
        int row = matches.first().row();

        if (removeRow(row)) {
            submitAll();
            select();
            return true;
        } else {
            qDebug() << "Error deleting row by name";
            return false;
        }
    } else {
        qDebug() << "Error: name not found";
        return false;
    }
*/
}

} // namespace chat
