#include "Character.h"

namespace chat {

Character::Character() : Character(QString(), QString())
{

}

Character::Character(const QString &name, const QString &message, bool useNameInMessage) :
    _name(name),
    _message(message),
    _useNameInMessage(useNameInMessage)
{

}

QString Character::name() const
{
    return _name;
}

void Character::setName(const QString &newName)
{
    _name = newName;
}

QString Character::message() const
{
    return _message;
}

void Character::setMessage(const QString &newMessage)
{
    _message = newMessage;
}

bool Character::useNameInMessage() const
{
    return _useNameInMessage;
}

void Character::setUseNameInMessage(bool newUseNameInMessage)
{
    _useNameInMessage = newUseNameInMessage;
}

QString Character::fullMessage() const
{
    if (_useNameInMessage) {
        if (_name.isEmpty()) {
            return _message;
        }

        return _name + ", " + _message;
    }

    return _message;
}

oaic::MsgData Character::msgData() const
{
    return oaic::MsgData("system", fullMessage());
}

} // namespace chat
