#include "Message.h"

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

} // namespace chat
