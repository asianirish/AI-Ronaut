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

    QString createSession();

    SessionPtr session(const QString &sessionId) const;

    OrderedMap<QString, SessionPtr> sessions() const;

private:
    OrderedMap<QString, SessionPtr> _sessions;

signals:

public slots:
    void onQuit();

private:
    explicit SessionManager(QObject *parent = nullptr);
    static SessionManager *_instance;


};

} // namespace chat

#endif // SESSIONMANAGER_H