#include "Character.h"

#include <QDebug>

#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>

namespace chat {

Character::Character() : Character(QString(), QString())
{

}

Character::Character(const QString &name, const QString &message, bool useNameInMessage) :
    _id(0),
    _name(name),
    _message(message),
    _useNameInMessage(useNameInMessage)
{

}

QString Character::name() const
{
    return _name;
}

void Character::setName(const QString &newName)
{
    _name = newName;
}

QString Character::message() const
{
    return _message;
}

void Character::setMessage(const QString &newMessage)
{
    _message = newMessage;
}

bool Character::useNameInMessage() const
{
    return _useNameInMessage;
}

void Character::setUseNameInMessage(bool newUseNameInMessage)
{
    _useNameInMessage = newUseNameInMessage;
}

QString Character::fullMessage() const
{
    if (_useNameInMessage) {
        if (_name.isEmpty()) {
            return _message;
        }

        return _name + ", " + _message;
    }

    return _message;
}

oaic::MsgData Character::msgData() const
{
    return oaic::MsgData("system", fullMessage());
}

int Character::id() const
{
    return _id;
}

void Character::setId(int newId)
{
    _id = newId;
}

bool Character::save() const
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    QString queryString;
    QString dbType = db.driverName();

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
    query.bindValue(":name", _name);
    query.bindValue(":message", _message);

    if (query.exec()) {
        qDebug() << "Record successfully added or updated.";
        return true;
    } else {
        qDebug() << "Query execution error: " << query.lastError().text();
        return false;
    }
}

} // namespace chat
