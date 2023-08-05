/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef SESSIONITEM_H
#define SESSIONITEM_H

#include "Session.h"

#include <QListWidgetItem>

namespace chat {

class SessionItem : public QListWidgetItem
{
public:
    static const int SESSION_ITEM_TYPE = ItemType::UserType + 1;

    enum SessionItemRoles {
        SessionIdRole = Qt::UserRole + 1
    };

    SessionItem();

    QVariant data(int role) const override;

    bool operator<(const QListWidgetItem &other) const override;

    QString sessionId() const;
    void setSessionId(const QString &newSessinId);

    QString name() const;

private:
    QString _sessionId;

    chat::SessionPtr session() const;
};

} // namespace chat

#endif // SESSIONITEM_H
