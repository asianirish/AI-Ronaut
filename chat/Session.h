#ifndef CHAT_SESSION_H
#define CHAT_SESSION_H

#include "SystemMessage.h"

#include <QList>
#include <QUuid>

#include <QSharedPointer>

namespace chat {

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

private:
    SystemMessage _systemMessage;
    QList<MessagePtr> _messageList;

    QUuid _uuid;
    QString _name;

    bool _isPersistent;
};

using SessionPtr = QSharedPointer<Session>;

} // namespace chat

#endif // CHAT_SESSION_H
