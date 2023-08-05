/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#include "Version.h"

#include <QStringList>

namespace plg {

Version::Version() : Version(0, 0, 0)
{

}

Version::Version(int major, int minor, int patch) :
    _major(major),
    _minor(minor),
    _patch(patch)
{

}

Version::Version(const QString &strVersion)
{
    fromString(strVersion);
}

int Version::major() const
{
    return _major;
}

void Version::setMajor(int newMajor)
{
    _major = newMajor;
}

int Version::minor() const
{
    return _minor;
}

int Version::patch() const
{
    return _patch;
}

void Version::setPatch(int newPatch)
{
    _patch = newPatch;
}

bool Version::operator<(const Version &other) const
{
    if (_major < other._major) {
        return true;
    }

    if (_minor < other._minor) {
        return true;
    }

    if (_patch < other._patch) {
        return true;
    }

    return false;
}

bool Version::operator==(const Version &other) const
{
    return ((_major == other._major) &&
            (_minor == other._minor) &&
            (_patch == other._patch));
}

bool Version::operator!=(const Version &other) const
{
    return !(*this == other);
}

bool Version::operator>(const Version &other) const
{
    return !(*this<other) && (*this!=other);
}

QString Version::toString() const
{
    return QString::number(_major) + "." + QString::number(_minor) + "." + QString::number(_patch);
}

void Version::fromString(const QString &strVersion)
{
    auto list = strVersion.split(".");

    if (list.size() < 3) {
        // TODO: exception or set "0.0.0"?
        _major = 0;
        _minor = 0;
        _patch = 0;
        return;
    }

    _major = list.at(0).toInt();
    _minor = list.at(1).toInt();
    _patch = list.at(2).toInt();
}

Version::operator QString() const
{
    return toString();
}

} // namespace plg
