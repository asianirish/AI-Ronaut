/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef CHARACTER_H
#define CHARACTER_H

#include <oaic/MsgData.h>

#include <QMetaType>
#include <QString>

namespace chat {

class Character
{
public:
    Character();

    Character(const QString &name, const QString &message, bool useNameInMessage = true);

    QString name() const;
    void setName(const QString &newName);

    QString message() const;
    void setMessage(const QString &newMessage);

    bool useNameInMessage() const;
    void setUseNameInMessage(bool newUseNameInMessage);

    QString fullMessage() const;

    oaic::MsgData msgData() const;

    int id() const;
    void setId(int newId);

    bool save();

    operator bool() const;

private:
    int _id;
    QString _name;
    QString _message;
    bool _useNameInMessage;

private:
    bool insertIntoDb();
    bool updateInDb();
};

using CharacterPtr = QSharedPointer<Character>;

} // namespace chat

Q_DECLARE_METATYPE(chat::Character)

#endif // CHARACTER_H
