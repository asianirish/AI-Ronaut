/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

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

bool Character::save()
{
    if (_id) {
        return updateInDb();
    }

    return insertIntoDb();
}

Character::operator bool() const
{
    return (_id != 0) && !_name.isEmpty();
}

bool Character::insertIntoDb()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    QString queryString;

    queryString = "INSERT INTO characters (name, message, useNameInMessage) VALUES(:name, :message, :useNameInMessage)";
    query.prepare(queryString);
    query.bindValue(":name", _name);
    query.bindValue(":message", _message);
    query.bindValue(":useNameInMessage", _useNameInMessage);

    if (query.exec()) {
        qDebug() << "Record successfully added.";

        int lastId = query.lastInsertId().toInt();
        qDebug() << "LAST CHARACTER ID IS" << lastId;

        setId(lastId);
        return true;
    }

    qDebug() << "(INSERT) Query execution error: " << query.lastError().text();
    return false;
}

bool Character::updateInDb()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    QString queryString;

    queryString = "UPDATE characters "
                    "SET name = :name, "
                    "message = :message, "
                    "useNameInMessage = :useNameInMessage "
                    "WHERE id = :id";

    query.prepare(queryString);
    query.bindValue(":name", _name);
    query.bindValue(":message", _message);
    query.bindValue(":useNameInMessage", _useNameInMessage);
    query.bindValue(":id", _id);

    if (query.exec()) {
        qDebug() << "Record successfully updated.";
        return true;
    }

    qDebug() << "(UPDATE) Query execution error: " << query.lastError().text();
    return false;
}

} // namespace chat
