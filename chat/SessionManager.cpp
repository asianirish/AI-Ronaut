#include "SessionManager.h"

#include <QDebug>
#include <QDateTime>

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

SessionManager::SessionManager(QObject *parent)
    : QObject{parent}
{

}

} // namespace chat
