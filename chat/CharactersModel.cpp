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

    QModelIndex nameIndex = index(row, 1);
    QModelIndex messageIndex = index(row, 2);

    QString name = data(nameIndex).toString();
    QString message = data(messageIndex).toString();

    Character character;
    character.setName(name);
    character.setMessage(message);

    return character;
}

bool CharactersModel::insertOrReplaceRecord(const QString &name, const QString &message)
{
    QSqlQuery query(database());
    QString queryString;
    QString dbType = database().driverName();

    if (dbType == "QSQLITE") {
        queryString = "INSERT OR REPLACE INTO characters (name, message) VALUES(:name, :message)";
    } else if (dbType == "QMYSQL") {
        queryString = "INSERT INTO characters (name, message) VALUES(:name, :message) "
                      "ON DUPLICATE KEY UPDATE name = VALUES(name), message = VALUES(message)";
    } else if (dbType == "QPSQL") {
        queryString = "INSERT INTO characters (name, message) VALUES(:name, :message) "
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

bool CharactersModel::insertOrReplaceRecord(const Character &character)
{
    return insertOrReplaceRecord(character.name(), character.message());
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
