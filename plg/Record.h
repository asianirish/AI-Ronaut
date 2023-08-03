#ifndef PLG_RECORD_H
#define PLG_RECORD_H

#include "Info.h"


namespace plg {

class Record
{
public:
    Record();

    int id() const;
    void setId(int newId);

    Info info() const;
    void setInfo(const Info &newInfo);

    QByteArray hash() const;
    void setHash(const QByteArray &newHash);


private:
    int _id;

    Info _info;

    QByteArray _hash;
};

} // namespace plg

#endif // PLG_RECORD_H
