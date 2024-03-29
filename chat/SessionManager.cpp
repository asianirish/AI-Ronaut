/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

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

    qDebug() << "CREATED SESION:" << session->uuid();

    // TODO: uuid already set in the Session constructor, no sense doing it again:
    QUuid sessionId = QUuid::createUuid();
    session->setUuid(sessionId);

    qDebug() << "RESET SESSION_ID:" << session->uuid();

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

void SessionManager::addCharacter(const Character &character, const QString &sessionId, bool doTouch)
{
    session(sessionId)->setCharacter(character, doTouch);
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

    QSqlQuery query("SELECT uuid, character_id, name, created, accessed  FROM sessions ORDER BY accessed DESC");

    while (query.next()) {
        QString sessionId = query.value(0).toString();

        // prevent sessions from being recreated
        if (_sessions.contains(sessionId)) {
            continue;
        }

        QVariant characterIdVar = query.value(1);
        int characterId = characterIdVar.isValid() ? query.value(1).toInt() : 0; // if NULL

        QString name = query.value(2).toString();
        QDateTime created = query.value(3).toDateTime();
        QDateTime accessed = query.value(4).toDateTime();

        SessionPtr session = SessionPtr(new Session(sessionId, name, created, accessed));

        _sessions.insert(sessionId, session);

        if (characterId) {
            auto pCharacter = gCharacters->character(characterId);

            if (pCharacter) {
                addCharacter(*pCharacter, sessionId, false);
            }
        }

        // TODO: load messages?
    }
}

void SessionManager::deleteSession(int pageIndex, const QString &sessionId, bool deletePermanently)
{
    deleteSession(sessionId, deletePermanently);
    emit sessionDeleted(pageIndex, sessionId);
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
