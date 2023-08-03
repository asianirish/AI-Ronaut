#include "Info.h"

namespace plg {

Info::Info()
{

}

QString Info::name() const
{
    return _name;
}

void Info::setName(const QString &newName)
{
    _name = newName;
}

QString Info::desc() const
{
    return _desc;
}

void Info::setDesc(const QString &newDesc)
{
    _desc = newDesc;
}

QString Info::author() const
{
    return _author;
}

void Info::setAuthor(const QString &newAuthor)
{
    _author = newAuthor;
}

Version Info::version() const
{
    return _version;
}

void Info::setVersion(const Version &newVersion)
{
    _version = newVersion;
}

} // namespace plg
