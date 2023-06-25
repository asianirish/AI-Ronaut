#include "AssistantRole.h"

namespace chat {

AssistantRole::AssistantRole()
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

} // namespace chat
