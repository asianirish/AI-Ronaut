#ifndef CHAT_SESSION_H
#define CHAT_SESSION_H

#include "SystemMessage.h"

#include <QList>

namespace chat {

class Session
{
public:
    Session();

    SystemMessage systemMessage() const;
    void setSystemMessage(const SystemMessage &newSystemMessage);

    QList<MessagePtr> messageList() const;
    void addMessage(const MessagePtr &msgPtr);

private:
    SystemMessage _systemMessage;
    QList<MessagePtr> _messageList;
};

} // namespace chat

#endif // CHAT_SESSION_H
