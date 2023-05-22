#ifndef CHAT_SYSTEMMESSAGE_H
#define CHAT_SYSTEMMESSAGE_H

#include "Message.h"

namespace chat {

class SystemMessage : public Message
{
public:
    SystemMessage();
    
    ROLE role() const override;
};

} // namespace chat

#endif // CHAT_SYSTEMMESSAGE_H
