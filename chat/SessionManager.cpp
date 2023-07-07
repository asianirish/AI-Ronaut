#include "SessionManager.h"

#include "CharacterManager.h"

#include <QDebug>
#include <QDateTime>

#include <QSqlError>

namespace chat {

SessionManager *SessionManager::_instance = nullptr;

SessionManager *SessionManager::instance()
{
    if (_instance == nullptr) {
        _instance = new SessionManager();
    }

    return _instance;
}

QString SessionManager::createSession(int pageIndex, const QString &sessionName)
{
    SessionPtr session = SessionPtr(new Session());
    QUuid sessionId = QUuid::createUuid();
    session->setUuid(sessionId);

    if (!sessionName.isEmpty()) {
        session->setName(sessionName);
    }

    _sessions.insert(sessionId.toString(), session);

    auto sessionIdStr = sessionId.toString();
    emit sessionCreated(pageIndex, sessionIdStr);

    return sessionIdStr;
}

SessionPtr SessionManager::session(const QString &sessionId) const
{
    return _sessions.value(sessionId);
}

OrderedMap<QString, SessionPtr> SessionManager::sessions() const
{
    return _sessions;
}

void SessionManager::addMessage(MessagePtr msgPtr, const QString &sessionId)
{
    session(sessionId)->addMessage(msgPtr);
}

void SessionManager::addCharacter(const Character &character, const QString &sessionId)
{
    session(sessionId)->setCharacter(character);
}

void SessionManager::onQuit()
{
    qDebug() << "cleaning sessions";
    _sessions.clear();
}

void SessionManager::saveAsTextFile(const QString &sessionId) const
{
    session(sessionId)->saveAsTextFile();
}

void SessionManager::save(const QString &sessionId) const
{
    session(sessionId)->save();
}

void SessionManager::deleteMessage(const QString &sessionId, MessagePtr msgPtr)
{
    auto sssn = session(sessionId);
    sssn->deleteMessage(msgPtr);
}

void SessionManager::select()
{
    gCharacters->select();

    // Do not clear the _sessions, as it also leads to the removal of values not from the database

    QSqlQuery query("SELECT uuid, character_id, name, created, accessed  FROM sessions ORDER BY created DESC");

    while (query.next()) { // TODO: error?
        QString sessionId = query.value(0).toString();

        QVariant characterIdVar = query.value(1);
        int characterId = characterIdVar.isValid() ? query.value(1).toInt() : 0; // if NULL

        QString name = query.value(2).toString();
        QDateTime created = query.value(3).toDateTime();
        QDateTime accessed = query.value(4).toDateTime();

        SessionPtr session = SessionPtr(new Session());
        session->setUuid(sessionId);
        session->setName(name);
        session->setCreated(created);
        session->setAccessed(accessed);

        session->setIsPersistent(true);

        _sessions.insert(sessionId, session);

        if (characterId) {
            auto pCharacter = gCharacters->character(characterId);

            if (pCharacter) {
                addCharacter(*pCharacter, sessionId);
            }
        }
    }
}

void SessionManager::deleteSession(const QString &sessionId, bool deletePermanently)
{
    auto session = _sessions.value(sessionId);
    bool isPersistent = session->isPersistent();

    if (!isPersistent || !deletePermanently) {
        _sessions.remove(sessionId);
        return;
    }

    if (deletePermanently) {
        if (deleteSessionFromDb(sessionId)) {
            _sessions.remove(sessionId);
        }
    }
}

bool SessionManager::deleteSessionFromDb(const QString &sessionId)
{
    // TODO: transaction
    // TODO: delete messages
    QSqlQuery query(QSqlDatabase::database());
    query.prepare("DELETE FROM sessions WHERE uuid=:uuid");
    query.bindValue(":uuid", sessionId);

    if (!query.exec()) {
        qDebug() << "Error deleting row by name:" << query.lastQuery() << query.lastError();
        return false;
    }

    select();
    return true;
}

SessionManager::SessionManager(QObject *parent)
    : QObject{parent}
{

}

} // namespace chat
