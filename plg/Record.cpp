/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

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
