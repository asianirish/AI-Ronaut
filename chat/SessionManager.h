#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "Session.h"

#include <OrderedMap.h>

#include <QObject>

namespace chat {

class SessionManager : public QObject
{
    Q_OBJECT
public:
    static SessionManager *instance();

    QString createSession(int pageIndex, const QString &sessionName = QString());

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
    
    void addCharacter(const Character &character, const QString &sessionId);

    void saveAsTextFile(const QString &sessionId) const;
    void save(const QString &sessionId) const;

    void deleteMessage(const QString &sessionId, MessagePtr msgPtr);

private:
    OrderedMap<QString, SessionPtr> _sessions;

signals:
    void sessionCreated(int pageIndex, const QString currentSessionId);

public slots:
    void onQuit();

private:
    explicit SessionManager(QObject *parent = nullptr);
    static SessionManager *_instance;


};

} // namespace chat

#define gSessions chat::SessionManager::instance()

#endif // SESSIONMANAGER_H
