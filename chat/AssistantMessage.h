#ifndef CHAT_ASSISTANTMESSAGE_H
#define CHAT_ASSISTANTMESSAGE_H

#include "Message.h"

namespace chat {

class AssistantMessage : public Message
{
public:
    AssistantMessage();

    MSG_TYPE msgType() const override;
};

} // namespace chat

#endif // CHAT_ASSISTANTMESSAGE_H
