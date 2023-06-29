#include "Session.h"
#include "SystemMessage.h"

#include <QFile>

using namespace oaic;

namespace chat {

Session::Session() : _isPersistent(false)
{
    _created = QDateTime::currentDateTime();
    _accessed = _created;

    _uuid = QUuid::createUuid();
    _name = _created.toString("yyyyMMddhhmmss");
}

QList<MessagePtr> Session::messageList() const
{
    return _messageList;
}

void Session::addMessage(const MessagePtr &msgPtr)
{
    auto sysMsgPtr = qSharedPointerDynamicCast<SystemMessage>(msgPtr);

    if (sysMsgPtr) {
        _character.setMessage(msgPtr->text());
    } else {
        _messageList.append(msgPtr);
    }
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

QString Session::id() const
{
    return uuidToString();
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

QDateTime Session::accessed() const
{
    return _accessed;
}

oaic::MsgDataList Session::msgDataList() const
{
    MsgDataList lst;

    lst.append(_character.msgData());

    for (auto &msg : _messageList) {
        auto msgData = msg->msgData();
        lst.append(msgData);
    }

    return lst;
}

void Session::saveAsTextFile() const
{
    QFile file(fileName() + ".log");

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.write(_character.msgData().role().toLatin1() + ": "); // write "system: "
        file.write(_character.fullMessage().toUtf8() + "\n"); // can be in different languages

        for (auto &msg : _messageList) {
            file.write(msg->roleAsString().toLatin1() + ": "); // write "user: " or "assistant"
            file.write(msg->text().toUtf8() + "\n"); // can be in different languages
        }
    }

    file.close();
}

void Session::deleteMessage(MessagePtr msgPtr)
{
    _messageList.removeAll(msgPtr);
}

QString Session::fileName() const
{
    QString createdStr(_created.toString("yyyyMMddhhmmss"));
    if (name().isEmpty()) {
        return createdStr;
    } else {
        return name() + "_" + createdStr;
    }
}

Character Session::character() const
{
    return _character;
}

void Session::setCharacter(const Character &newCharacter)
{
    _character = newCharacter;
    _accessed = QDateTime::currentDateTime();
}

} // namespace chat
