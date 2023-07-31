#include "Session.h"
#include "SystemMessage.h"

#include <QDebug>

#include <QSqlError>

#include <QFile>

using namespace oaic;

namespace chat {

Session::Session() : _isPersistent(false)
{
    _created = QDateTime::currentDateTime();
    _accessed = _created;

    _uuid = QUuid::createUuid();
    _name = _created.toString("yyyyMMddhhmmss");

    qDebug() << "\nTEST CREATING SESSION ():" << _uuid << "\n";
}

Session::Session(const QString &sessionId, const QString &name, const QDateTime &created, const QDateTime &accessed) :
    _uuid(QUuid(sessionId)),
    _name(name),
    _created(created),
    _accessed(accessed),
    _isPersistent(true)
{

}

Session::~Session()
{
    qDebug() << "\nDELETING SESSION:" << _uuid << "\n";
}

QList<MessagePtr> Session::messageList() const
{
    if (_messageList.isEmpty()) {
        selectMessages();
    }

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

    touch();
}

QUuid Session::uuid() const
{
    return _uuid;
}

void Session::setUuid(const QUuid &newUuid)
{
    _uuid = newUuid;
}

void Session::setUuid(const QString &uuidStr)
{
    setUuid(QUuid(uuidStr));
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
    touch();
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

void Session::save()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    db.transaction();

    qDebug() << "SAVING CHARACTER:" << _character.id();

    if (_character) {
        if (!_character.save()) {
            db.rollback();
            return;
        }
    }

    qDebug() << "SAVING SESSION..." << _uuid.toString() << _name;
    if (!save(query)) {
        db.rollback();
        return;
    }

    int i = 10;
    for (auto &msg : _messageList) {
        msg->save(_uuid.toString(), i);
        i += 10;
    }


    db.commit();
    setIsPersistent(true);
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

bool Session::save(QSqlQuery &query)
{
    QString queryString;

    // TODO: for other db engines
    queryString = "INSERT OR REPLACE INTO sessions (uuid, character_id, name, created, accessed) "
                  "VALUES(:uuid, :character_id, :name, :created, :accessed)";

    query.prepare(queryString);
    query.bindValue(":uuid", _uuid);

    if (_character.id()) {
        query.bindValue(":character_id", _character.id());
    } else {
        query.bindValue(":character_id", QVariant(QMetaType::fromType<int>()));
    }

    query.bindValue(":name", _name);
    query.bindValue(":created", _created);
    query.bindValue(":accessed", _accessed);

    if (query.exec()) {
        qDebug() << "Record successfully added or updated.";
        return true;
    }

    qDebug() << "Query execution error: " << query.lastError().text();
    return false;
}

void Session::selectMessages() const
{
    QString queryString("SELECT id, order_num, role, content  FROM messages WHERE session_uuid=:session_uuid AND role <> 'system' ORDER BY order_num");

    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":session_uuid", uuidToString());

    if (query.exec()) {
        while (query.next()) {
            // TODO: read and use id
// TODO: use?            int orderNum = query.value("order_num").toInt();
            auto role = query.value("role").toString();
            QString content = query.value("content").toString();

            auto msg = Message::createMessage(role, content);
            _messageList.append(msg);
        }
    } // TODO: error messages
}

void Session::setAccessed(const QDateTime &newAccessed)
{
    _accessed = newAccessed;
}

void Session::touch()
{
    _accessed = QDateTime::currentDateTime();
}

void Session::setCreated(const QDateTime &newCreated)
{
    _created = newCreated;
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
