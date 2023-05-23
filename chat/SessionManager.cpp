#include "SessionManager.h"

#include <QDebug>

namespace chat {

SessionManager *SessionManager::_instance = nullptr;

SessionManager *SessionManager::instance()
{
    if (_instance == nullptr) {
        _instance = new SessionManager();
    }

    return _instance;
}

QString SessionManager::createSession()
{
    SessionPtr session = SessionPtr(new Session());
    QUuid sessionId = QUuid::createUuid();
    session->setUuid(sessionId);

    return sessionId.toString();
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

SessionManager::SessionManager(QObject *parent)
    : QObject{parent}
{

}

} // namespace chat
