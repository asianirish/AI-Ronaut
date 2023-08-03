#ifndef PLG_INFO_H
#define PLG_INFO_H

#include "Version.h"

#include <QMetaType>

namespace plg {

class Info
{
public:
    Info();

    QString name() const;
    void setName(const QString &newName);

    QString desc() const;
    void setDesc(const QString &newDesc);

    QString author() const;
    void setAuthor(const QString &newAuthor);

    Version version() const;
    void setVersion(const Version &newVersion);

private:
    QString _name;
    QString _desc;
    QString _author;
    Version _version;
};

} // namespace plg

Q_DECLARE_METATYPE(plg::Info)

#endif // PLG_INFO_H
