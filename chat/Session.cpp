#include "Session.h"

namespace chat {

Session::Session() : _isPersistent(false)
{
    _created = QDateTime::currentDateTime();
    _accessed = _created;

    _uuid = QUuid::createUuid();
}

SystemMessage Session::systemMessage() const
{
    return _systemMessage;
}

void Session::setSystemMessage(const SystemMessage &newSystemMessage)
{
    _systemMessage = newSystemMessage;
    _accessed = QDateTime::currentDateTime();
}

QList<MessagePtr> Session::messageList() const
{
    return _messageList;
}

void Session::addMessage(const MessagePtr &msgPtr)
{
    _messageList.append(msgPtr);
    _accessed = QDateTime::currentDateTime();
}

QUuid Session::uuid() const
{
    return _uuid;
}

void Session::setUuid(const QUuid &newUuid)
{
    _uuid = newUuid;
}

QByteArray Session::uuidToByteArray() const
{
    return _uuid.toByteArray();
}

QString Session::uuidToString() const
{
    return _uuid.toString();
}

void Session::setUuid(const QByteArray &uuid)
{
    _uuid = QUuid::fromString(uuid);
}

QString Session::name() const
{
    return _name;
}

void Session::setName(const QString &newName)
{
    _name = newName;
    _accessed = QDateTime::currentDateTime();
}

bool Session::isPersistent() const
{
    return _isPersistent;
}

void Session::setIsPersistent(bool newIsPersistent)
{
    _isPersistent = newIsPersistent;
}

QDateTime Session::created() const
{
    return _created;
}

SessionData Session::data() const
{
    return SessionData{_uuid.toString(), _name, _created, _accessed, _isPersistent};
}

QDateTime Session::accessed() const
{
    return _accessed;
}

} // namespace chat
