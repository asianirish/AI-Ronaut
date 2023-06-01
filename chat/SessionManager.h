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

    QString currentSessionId() const;
    void setCurrentSessionId(const QString &sessionId);
    void selectSession(const QString &sessionId); // synonim of setCurrentSessionId
    void deselectSession();

    bool isSession() const;

private:
    OrderedMap<QString, SessionPtr> _sessions;

signals:
    void sessionCreated(const QString currentSessionId);

public slots:
    void onQuit();

private:
    QString _currentSessionId;

private:
    explicit SessionManager(QObject *parent = nullptr);
    static SessionManager *_instance;


};

} // namespace chat

#endif // SESSIONMANAGER_H
