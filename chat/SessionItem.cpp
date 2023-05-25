#include "SessionItem.h"

namespace chat {

SessionItem::SessionItem() : QListWidgetItem(nullptr, SESSION_ITEM_TYPE)
{

}

QVariant SessionItem::data(int role) const
{
    if (role == Qt::DisplayRole) {
        return _sessionData.name;
    }

//    if (role == Qt::InitialSortOrderRole) {
//        return QVariant::fromValue(_sessionData);
//    }

    return QListWidgetItem::data(role);
}

SessionData SessionItem::sessionData() const
{
    return _sessionData;
}

void SessionItem::setSessionData(const SessionData &sessionData)
{
    _sessionData = sessionData;
//    setData(Qt::InitialSortOrderRole, QVariant::fromValue(sessionData));
}

bool SessionItem::operator<(const QListWidgetItem &other) const
{
    const SessionItem *pOther = dynamic_cast<const SessionItem *>(&other);

    if (pOther) {
        SessionData mySessionData = data(Qt::InitialSortOrderRole).value<SessionData>();
        SessionData otherData = pOther->data(Qt::InitialSortOrderRole).value<SessionData>();
        return (mySessionData.created < otherData.created);
    }

    return QListWidgetItem::operator<(other);
}

} // namespace chat
