#ifndef PLG_VERSION_H
#define PLG_VERSION_H

#include <QString>


namespace plg {

class Version
{
public:
    Version();

    Version(int major, int minor, int patch);

    Version(const QString &strVersion);

    int major() const;
    void setMajor(int newMajor);

    int minor() const;

    int patch() const;
    void setPatch(int newPatch);

    bool operator<(const Version &other) const;

    bool operator==(const Version &other) const;

    bool operator!=(const Version &other) const;

    bool operator>(const Version &other) const;

    QString toString() const;

    void fromString(const QString &strVersion);

    operator QString() const;

private:
    int _major;
    int _minor;
    int _patch;
};

} // namespace plg

#endif // PLG_VERSION_H
