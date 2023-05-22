#include "UserMessage.h"

namespace chat {

UserMessage::UserMessage()
{

}

Message::ROLE UserMessage::role() const
{
    return ROLE::USER;
}

} // namespace chat
