/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#include "Auth.h"

#include <QFile>
#include <QProcessEnvironment>

namespace oaic {

Auth::Auth()
{

}

QString Auth::key() const
{
    return _key;
}

bool Auth::setKey(const QString &newKey)
{
    _key = newKey;
    return setAuthorizationHeader();
}

bool Auth::setKeyFile(const FilePath &path)
{
    std::string str = path.toStdString();
    return setKeyFile(std::filesystem::path(str));
}

bool Auth::setKeyFile(const std::filesystem::__cxx11::path &path)
{
    if (std::filesystem::exists(path) && std::filesystem::is_regular_file(path) && std::filesystem::file_size(path) > 0) {
        QFile file(path);

        file.open(QIODeviceBase::ReadOnly| QIODevice::Text);

        if (file.isOpen()) {
            _key = file.readLine();
            _key = _key.trimmed();
            return setAuthorizationHeader();
        }
    }
    return false;
}

bool Auth::setKeyEnv(const EnvVar &var) noexcept
{
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    // OPENAI_API_KEY

    if (env.contains(var)) { // OPENAI_API_KEY
        _key = env.value(var);
        return setAuthorizationHeader();
    }

    return false;
}

bool Auth::setAuthorizationHeader()
{
    if (!_key.isEmpty()) {
        _headers.insert(QByteArray("Authorization"), QByteArray("Bearer ") + _key.toLatin1());
        return true;
    }

    return false;
}

Headers Auth::headers() const
{
    return _headers;
}

bool Auth::isEmpty()
{
    return _key.isEmpty() && _headers.isEmpty();
}



} // namespace oaic
