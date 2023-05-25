#ifndef CHAT_SESSION_H
#define CHAT_SESSION_H

#include "SystemMessage.h"

#include <QList>
#include <QUuid>
#include <QDateTime>

#include <QSharedPointer>

namespace chat {

struct SessionData;

class Session
{
public:
    Session();

    SystemMessage systemMessage() const;
    void setSystemMessage(const SystemMessage &newSystemMessage);

    QList<MessagePtr> messageList() const;
    void addMessage(const MessagePtr &msgPtr);

    QUuid uuid() const;
    void setUuid(const QUuid &newUuid);

    QByteArray uuidToByteArray() const;
    QString uuidToString() const;

    void setUuid(const QByteArray &uuid);

    bool isNull() const;
    operator bool() const;

    void activate();

    QString name() const;
    void setName(const QString &newName);

    bool isPersistent() const;
    void setIsPersistent(bool newIsPersistent);

    QDateTime created() const;

    SessionData data() const;

private:
    SystemMessage _systemMessage;
    QList<MessagePtr> _messageList;

    QUuid _uuid;
    QString _name;
    QDateTime _created;

    bool _isPersistent;
};

using SessionPtr = QSharedPointer<Session>;

struct SessionData {
    QString id;
    QString name;
    QDateTime created;

    bool isPersistent = false;
};



} // namespace chat

Q_DECLARE_METATYPE(chat::SessionData);

#endif // CHAT_SESSION_H
