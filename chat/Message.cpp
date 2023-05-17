#include "Message.h"

namespace chat {

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

} // namespace chat
