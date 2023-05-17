#include "AssistantMessage.h"

namespace chat {

AssistantMessage::AssistantMessage()
{

}

Message::MSG_TYPE AssistantMessage::msgType() const
{
    return MSG_TYPE::ASSISTANT;
}

} // namespace chat
