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

private:
    int _id;
    QString _name;
    QString _message;
    bool _useNameInMessage;
};

} // namespace chat

Q_DECLARE_METATYPE(chat::Character)

#endif // CHARACTER_H
