#ifndef CHAT_SESSION_H
#define CHAT_SESSION_H

#include "SystemMessage.h"

#include <Chat.h>

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

    QString name() const;
    void setName(const QString &newName);

    bool isPersistent() const;
    void setIsPersistent(bool newIsPersistent);

    QDateTime created() const;

    SessionData data() const;

    QDateTime accessed() const;

    oaic::MsgDataList msgDataList() const;

    void saveAsTextFile() const;

private:
    SystemMessage _systemMessage;
    QList<MessagePtr> _messageList;

    QUuid _uuid;
    QString _name;
    QDateTime _created;
    QDateTime _accessed;

    bool _isPersistent;

    // TODO: oaic::ModelContext _modelCntx;
};

using SessionPtr = QSharedPointer<Session>;

struct SessionData {
    QString id;
    QString name;
    QDateTime created;
    QDateTime accessed;

    bool isPersistent = false;
};



} // namespace chat

Q_DECLARE_METATYPE(chat::SessionData);

#endif // CHAT_SESSION_H
