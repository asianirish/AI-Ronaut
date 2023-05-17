#include "SystemMessage.h"

namespace chat {

SystemMessage::SystemMessage()
{

}

Message::MSG_TYPE SystemMessage::msgType() const
{
    return MSG_TYPE::SYSTEM;
}

} // namespace chat
