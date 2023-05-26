#include "MsgData.h"

#include <QVariantMap>

namespace oaic {

MsgData::MsgData()
{

}

QString MsgData::role() const
{
    return _role;
}

void MsgData::setRole(const QString &newRole)
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
