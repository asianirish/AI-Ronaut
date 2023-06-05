#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "util/OrderedMap.h"
#include "Session.h"

#include <QObject>

namespace chat {

class SessionManager : public QObject
{
    Q_OBJECT
public:
    static SessionManager *instance();

    QString createSession(const QString &sessionName = QString()); // TODO: isPersistent?

    SessionPtr session(const QString &sessionId) const;

    OrderedMap<QString, SessionPtr> sessions() const;

//    template<typename T>
//    [[deprecated("just use addSystemMessage instead")]]MessagePtr addMessage(const QString &text, const QString &sessionId) {
//        MessagePtr msgPtr = chat::MessagePtr(new T());
//        msgPtr->setText(text);
//        addMessage(msgPtr, sessionId);
//        return msgPtr;
//    }

    void addMessage(MessagePtr msgPtr, const QString &sessionId);

    void addSystemMessage(const QString &messageText, const QString &sessionId);

    void saveAsTextFile(const QString &sessionId) const;

private:
    OrderedMap<QString, SessionPtr> _sessions;

signals:
    void sessionCreated(const QString currentSessionId);

public slots:
    void onQuit();

private:
    explicit SessionManager(QObject *parent = nullptr);
    static SessionManager *_instance;


};

} // namespace chat

#define gSessions chat::SessionManager::instance()

#endif // SESSIONMANAGER_H
