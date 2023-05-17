#include "Session.h"

namespace chat {

Session::Session()
{

}

SystemMessage Session::systemMessage() const
{
    return _systemMessage;
}

void Session::setSystemMessage(const SystemMessage &newSystemMessage)
{
    _systemMessage = newSystemMessage;
}

QList<MessagePtr> Session::messageList() const
{
    return _messageList;
}

void Session::addMessage(const MessagePtr &msgPtr)
{
    _messageList.append(msgPtr);
}

} // namespace chat
