#include "Session.h"

namespace chat {

Session::Session() : _isPersistent(false)
{

}

SystemMessage Session::systemMessage() const
{
    return _systemMessage;
}

void Session::setSystemMessage(const SystemMessage &newSystemMessage)
{
    _systemMessage = newSystemMessage;
}

QList<MessagePtr> Session::messageList() const
{
    return _messageList;
}

void Session::addMessage(const MessagePtr &msgPtr)
{
    _messageList.append(msgPtr);
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

bool Session::isNull() const
{
    return _uuid.isNull();
}

Session::operator bool() const
{
    return !isNull();
}

void Session::activate()
{
    _uuid = QUuid::createUuid();
}

QString Session::name() const
{
    return _name;
}

void Session::setName(const QString &newName)
{
    _name = newName;
}

bool Session::isPersistent() const
{
    return _isPersistent;
}

void Session::setIsPersistent(bool newIsPersistent)
{
    _isPersistent = newIsPersistent;
}

} // namespace chat
