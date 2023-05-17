#include "UserMessage.h"

namespace chat {

UserMessage::UserMessage()
{

}

Message::MSG_TYPE UserMessage::msgType() const
{
    return MSG_TYPE::USER;
}

} // namespace chat
