#include "CharactersModel.h"

#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>

namespace chat {

CharactersModel::CharactersModel(QObject *parent) : QSqlTableModel(parent)
{
    setTable("characters");
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();
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
        return QSqlTableModel::data(index, role);
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

bool CharactersModel::insertOrReplaceRecord(const QString &name, const QString &message)
{
    Character character(name, message);
    return insertOrReplaceRecord(character);
}

bool CharactersModel::insertOrReplaceRecord(const Character &character)
{
    if (character.save()) {
        select(); // Update the model after changes in the database
        return true;
    }

    return false;
}

bool CharactersModel::removeRowByName(const QString &name)
{
    QSqlQuery query(database());
    query.prepare("DELETE FROM characters WHERE name = :name");
    query.bindValue(":name", name);

    if (!query.exec()) {
        qDebug() << "Error deleting row by name:" << query.lastError();
        return false;
    }

    select();
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
