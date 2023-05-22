#include "SystemMessage.h"

namespace chat {

SystemMessage::SystemMessage()
{

}

Message::ROLE SystemMessage::role() const
{
    return ROLE::SYSTEM;
}

} // namespace chat
