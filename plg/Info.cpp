/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

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
