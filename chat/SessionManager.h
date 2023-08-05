/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

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
    
    void addCharacter(const Character &character, const QString &sessionId, bool doTouch = true);

    void saveAsTextFile(const QString &sessionId) const;
    void save(const QString &sessionId) const;

    void deleteMessage(const QString &sessionId, MessagePtr msgPtr);

    void select();

    void deleteSession(int pageIndex, const QString &sessionId, bool deletePermanently);

private:
    OrderedMap<QString, SessionPtr> _sessions;

private:
    void deleteSession(const QString &sessionId, bool deletePermanently);
    bool deleteSessionFromDb(const QString &sessionId);

signals:
    void sessionCreated(int pageIndex, const QString currentSessionId);
    void sessionDeleted(int pageIndex, const QString sessionId);


public slots:
    void onQuit();

private:
    explicit SessionManager(QObject *parent = nullptr);
    static SessionManager *_instance;
};

} // namespace chat

#define gSessions chat::SessionManager::instance()

#endif // SESSIONMANAGER_H
