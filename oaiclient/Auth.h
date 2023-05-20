#ifndef OAIC_AUTH_H
#define OAIC_AUTH_H

#include <QString>
#include <QMap>

#include <filesystem>

namespace oaic {

using FilePath = QString;
using EnvVar = QString;
using Headers = QMap<QString, QString>;

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
