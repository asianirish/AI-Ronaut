/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef OAIC_AUTH_H
#define OAIC_AUTH_H

#include <QString>
#include <QMap>

#include <filesystem>

namespace oaic {

using FilePath = QString;
using EnvVar = QString;
using Headers = QMap<QByteArray, QByteArray>;

class Auth
{
public:
    Auth();

    QString key() const;
    bool setKey(const QString &newKey);

    bool setKeyFile(const FilePath &path);

    bool setKeyFile(const std::filesystem::path &path);

    bool setKeyEnv(const EnvVar &var) noexcept;

    bool setAuthorizationHeader();

    Headers headers() const;

private:
    QString _key;
    Headers _headers;
};

} // namespace oaic

#endif // OAIC_AUTH_H
