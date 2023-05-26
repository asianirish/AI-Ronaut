#ifndef OAIC_MSGDATA_H
#define OAIC_MSGDATA_H

#include <QString>
#include <QJsonObject>

namespace oaic {

class MsgData
{
public:
    MsgData();

    QString role() const;
    void setRole(const QString &newRole);

    QString content() const;
    void setContent(const QString &newContent);

    QVariantMap toMap() const;

    QJsonObject toJson() const;

private:
    QString _role;
    QString _content;
};

} // namespace oaic

#endif // OAIC_MSGDATA_H
