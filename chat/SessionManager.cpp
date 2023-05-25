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

QString SessionManager::createSession(const QString &sessionName)
{
    SessionPtr session = SessionPtr(new Session());
    QUuid sessionId = QUuid::createUuid();
    session->setUuid(sessionId);

    if (sessionName.isEmpty()) {
        QDateTime date = QDateTime::currentDateTime();
        QString formattedTime = date.toString("yyyyMMddhhmmss");
        QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();
        session->setName(formattedTimeMsg);
    } else {
        session->setName(sessionName);
    }

    _sessions.insert(sessionId.toString(), session);

    _currentSessionId = sessionId.toString();
    emit sessionCreated(_currentSessionId);

    return _currentSessionId;
}

SessionPtr SessionManager::session(const QString &sessionId) const
{
    return _sessions.value(sessionId);
}

OrderedMap<QString, SessionPtr> SessionManager::sessions() const
{
    return _sessions;
}

void SessionManager::onQuit()
{
    qDebug() << "cleaning sessions";
    _sessions.clear();
}

QString SessionManager::currentSessionId() const
{
    return _currentSessionId;
}

void SessionManager::setCurrentSessionId(const QString &sessionId)
{
    if (_sessions.contains(sessionId)) {
        _currentSessionId = sessionId;
    }
}

void SessionManager::selectSession(const QString &sessionId)
{
    setCurrentSessionId(sessionId);
}

void SessionManager::deselectSession()
{
    _currentSessionId.clear();
}

SessionManager::SessionManager(QObject *parent)
    : QObject{parent}
{

}

} // namespace chat
