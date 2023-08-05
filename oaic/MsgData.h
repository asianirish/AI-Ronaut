/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef OAIC_MSGDATA_H
#define OAIC_MSGDATA_H

#include <QString>
#include <QJsonObject>

namespace oaic {

using Role = QString; // TODO: protected class instead of QString (with operator QString)

class MsgData
{
public:
    MsgData();
    MsgData(const Role &role, const QString &content);

    Role role() const;
    void setRole(const Role &newRole);

    QString content() const;
    void setContent(const QString &newContent);

    QVariantMap toMap() const;

    QJsonObject toJson() const;

private:
    Role _role;
    QString _content;
};

} // namespace oaic

#endif // OAIC_MSGDATA_H
