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

    auto sessionIdStr = sessionId.toString();
    emit sessionCreated(sessionIdStr);

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

void SessionManager::addSystemMessage(const QString &messageText, const QString &sessionId)
{
    session(sessionId)->addSystemMessage(messageText);
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

SessionManager::SessionManager(QObject *parent)
    : QObject{parent}
{

}

} // namespace chat
