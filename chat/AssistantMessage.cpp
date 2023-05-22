#include "AssistantMessage.h"

namespace chat {

AssistantMessage::AssistantMessage()
{

}

Message::ROLE AssistantMessage::role() const
{
    return ROLE::ASSISTANT;
}

} // namespace chat
