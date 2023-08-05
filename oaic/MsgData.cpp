/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#include "MsgData.h"

#include <QVariantMap>

namespace oaic {

MsgData::MsgData()  : MsgData(Role(), QString())
{

}

MsgData::MsgData(const Role &role, const QString &content) :
    _role(role),
    _content(content)
{

}

Role MsgData::role() const
{
    return _role;
}

void MsgData::setRole(const Role &newRole)
{
    _role = newRole;
}

QString MsgData::content() const
{
    return _content;
}

void MsgData::setContent(const QString &newContent)
{
    _content = newContent;
}

QVariantMap MsgData::toMap() const
{
    QVariantMap mp;
    mp.insert("role", _role);
    mp.insert("content", _content);

    return mp;
}

QJsonObject MsgData::toJson() const
{
    return QJsonObject::fromVariantMap(toMap());
}

} // namespace oaic
