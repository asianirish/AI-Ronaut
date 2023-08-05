/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef CHAT_SESSION_H
#define CHAT_SESSION_H

#include "Message.h"
#include "Character.h"

#include <Chat.h>

#include <QList>
#include <QUuid>
#include <QDateTime>

#include <QSharedPointer>
#include <QSqlQuery>

namespace chat {

class Session
{
public:
    Session();

    // for select
    Session(const QString &sessionId, const QString &name,
            const QDateTime &created, const QDateTime &accessed);

    QList<MessagePtr> messageList() const;
    void addMessage(const MessagePtr &msgPtr);

    QUuid uuid() const;
    void setUuid(const QUuid &newUuid);
    void setUuid(const QString &uuidStr);


    QByteArray uuidToByteArray() const;
    QString uuidToString() const;
    QString id() const; // same as uuidToString

    void setUuid(const QByteArray &uuid);

    QString name() const;
    void setName(const QString &newName);

    bool isPersistent() const;
    void setIsPersistent(bool newIsPersistent);

    QDateTime created() const;

    QDateTime accessed() const;

    oaic::MsgDataList msgDataList() const;

    void saveAsTextFile() const;

    void save();

    void deleteMessage(MessagePtr msgPtr);
    
    Character character() const;
    void setCharacter(const Character &newCharacter, bool doTouch = true);

    void setCreated(const QDateTime &newCreated);

    void setAccessed(const QDateTime &newAccessed);

    void touch();

private:
    QString fileName() const;
    bool save(QSqlQuery &query);

    void selectMessages() const;

private:
    // TODO: use character_id and gCharacter instead?
    Character _character;

    mutable QList<MessagePtr> _messageList;

    QUuid _uuid;
    QString _name;
    QDateTime _created;
    QDateTime _accessed;

    bool _isPersistent;

    // TODO: oaic::ModelContext _modelCntx;
};

using SessionPtr = QSharedPointer<Session>;

} // namespace chat

#endif // CHAT_SESSION_H
