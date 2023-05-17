#ifndef CHAT_MESSAGE_H
#define CHAT_MESSAGE_H

#include <QString>
#include <QSharedPointer>

namespace chat {

class Message
{
public:
    enum MSG_TYPE {
        UNDEFINED,
        SYSTEM,
        USER,
        ASSISTANT
    };

    Message();

    virtual ~Message() = default;

    virtual MSG_TYPE msgType() const = 0;

    QString text() const;
    void setText(const QString &newText);

private:
    QString _text;
};

using MessagePtr = QSharedPointer<Message>;

} // namespace chat

#endif // CHAT_MESSAGE_H
