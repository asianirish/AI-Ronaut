#ifndef CHAT_SESSION_H
#define CHAT_SESSION_H

#include "Message.h"
#include "AssistantRole.h"

#include <Chat.h>

#include <QList>
#include <QUuid>
#include <QDateTime>

#include <QSharedPointer>

namespace chat {

class Session
{
public:
    Session();

    QList<MessagePtr> messageList() const;
    void addMessage(const MessagePtr &msgPtr);

    QUuid uuid() const;
    void setUuid(const QUuid &newUuid);

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

    void deleteMessage(MessagePtr msgPtr);

    AssistantRole role() const;
    void setRole(const AssistantRole &newRole);

private:
    QString fileName() const;

private:
    AssistantRole _role;

    QList<MessagePtr> _messageList;

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
