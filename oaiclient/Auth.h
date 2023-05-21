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

    int timeout() const;
    void setTimeout(int newTimeout);

private:
    QString _key;
    Headers _headers;
    int _timeout;
};

} // namespace oaic

#endif // OAIC_AUTH_H
