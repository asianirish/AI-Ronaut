#include "Message.h"

#include "chat/SystemMessage.h"
#include "chat/AssistantMessage.h"
#include "chat/UserMessage.h"

namespace chat {

const QMap<Message::ROLE, QString> Message::ROLE_TO_STRING = {
    {Message::UNDEFINED, "undefined"},
    {Message::SYSTEM, "system"},
    {Message::USER, "user"},
    {Message::ASSISTANT, "assistant"},
};

Message::Message()
{

}

QString Message::text() const
{
    return _text;
}

void Message::setText(const QString &newText)
{
    _text = newText;
}

QString Message::roleAsString() const
{
    auto rl = role();
    return ROLE_TO_STRING.value(rl);
}

oaic::MsgData Message::msgData() const
{
    return oaic::MsgData(roleAsString(), text());
}

MessagePtr Message::createMessage(const oaic::MsgData &msgData)
{
    MessagePtr msg;

    if (msgData.role() == ROLE_TO_STRING.value(Message::SYSTEM)) {
        msg = MessagePtr(new chat::SystemMessage());
    } else if (msgData.role() == ROLE_TO_STRING.value(Message::USER)) {
        msg = MessagePtr(new chat::UserMessage());
    } else if (msgData.role() == ROLE_TO_STRING.value(Message::ASSISTANT)) {
        msg = MessagePtr(new chat::AssistantMessage());
    }

    if (msg) {
        msg->setText(msgData.content());
    }

    return msg;
}

MessagePtr Message::createMessage(const oaic::Role &role, const QString &content)
{
    return createMessage(oaic::MsgData(role, content));
}

} // namespace chat
