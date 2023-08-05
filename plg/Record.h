/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

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
