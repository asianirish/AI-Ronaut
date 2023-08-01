#include "Record.h"

namespace plg {

Record::Record() : _id(0)
{

}

int Record::id() const
{
    return _id;
}

void Record::setId(int newId)
{
    _id = newId;
}

Info Record::info() const
{
    return _info;
}

void Record::setInfo(const Info &newInfo)
{
    _info = newInfo;
}

QByteArray Record::hash() const
{
    return _hash;
}

void Record::setHash(const QByteArray &newHash)
{
    _hash = newHash;
}


} // namespace plg
