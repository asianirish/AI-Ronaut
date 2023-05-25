#ifndef SESSIONITEM_H
#define SESSIONITEM_H

#include "Session.h"

#include <QListWidgetItem>

namespace chat {

class SessionItem : public QListWidgetItem
{
public:
    static const int SESSION_ITEM_TYPE = ItemType::UserType + 1;

    SessionItem();

    void setSessionData(const SessionData &sessionData);

    QVariant data(int role) const override;
    SessionData sessionData() const;

    bool operator<(const QListWidgetItem &other) const override;

private:
    SessionData _sessionData;

};

} // namespace chat

#endif // SESSIONITEM_H
