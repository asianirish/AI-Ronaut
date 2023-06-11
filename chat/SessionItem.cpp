#include "SessionItem.h"
#include "SessionManager.h"

namespace chat {

SessionItem::SessionItem() : QListWidgetItem(nullptr, SESSION_ITEM_TYPE)
{

}

QVariant SessionItem::data(int role) const
{
    if (role == Qt::DisplayRole) {
        return session()->name();
    }

    if (role == SessionIdRole) {
        return _sessionId;
    }

    return QListWidgetItem::data(role);
}

bool SessionItem::operator<(const QListWidgetItem &other) const
{
    const SessionItem *pOther = dynamic_cast<const SessionItem *>(&other);

    if (pOther) {
        return (session()->created() < pOther->session()->created());
    }

    return QListWidgetItem::operator<(other);
}

QString SessionItem::sessionId() const
{
    return _sessionId;
}

void SessionItem::setSessionId(const QString &newSessinId)
{
    _sessionId = newSessinId;
}

QString SessionItem::name() const
{
    session()->name();
}

SessionPtr SessionItem::session() const
{
    return gSessions->session(_sessionId);
}

} // namespace chat
