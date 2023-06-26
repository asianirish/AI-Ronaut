#include "AssistantRole.h"

namespace chat {

AssistantRole::AssistantRole() : AssistantRole(QString(), QString())
{

}

AssistantRole::AssistantRole(const QString &name, const QString &message, bool useNameInMessage) :
    _name(name),
    _message(message),
    _useNameInMessage(useNameInMessage)
{

}

QString AssistantRole::name() const
{
    return _name;
}

void AssistantRole::setName(const QString &newName)
{
    _name = newName;
}

QString AssistantRole::message() const
{
    return _message;
}

void AssistantRole::setMessage(const QString &newMessage)
{
    _message = newMessage;
}

bool AssistantRole::useNameInMessage() const
{
    return _useNameInMessage;
}

void AssistantRole::setUseNameInMessage(bool newUseNameInMessage)
{
    _useNameInMessage = newUseNameInMessage;
}

QString AssistantRole::fullMessage() const
{
    if (_useNameInMessage) {
        if (_name.isEmpty()) {
            return _message;
        }

        return _name + ", " + _message;
    }

    return _message;
}

oaic::MsgData AssistantRole::msgData() const
{
    return oaic::MsgData("system", fullMessage());
}

} // namespace chat
