#ifndef CHAT_USERMESSAGE_H
#define CHAT_USERMESSAGE_H

#include "Message.h"

namespace chat {

class UserMessage : public Message
{
public:
    UserMessage();
    
    ROLE role() const override;
};

} // namespace chat

#endif // CHAT_USERMESSAGE_H
