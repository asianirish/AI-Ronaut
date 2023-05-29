#ifndef CHAT_MESSAGE_H
#define CHAT_MESSAGE_H

#include <oaic/MsgData.h>

#include <QString>
#include <QSharedPointer>
#include <QMap>

namespace chat {

class Message
{
public:
    enum ROLE {
        UNDEFINED,
        SYSTEM,
        USER,
        ASSISTANT
    };

    Message();

    virtual ~Message() = default;

    virtual ROLE role() const = 0;

    QString text() const;
    void setText(const QString &newText);

    QString roleAsString() const;

    oaic::MsgData msgData() const;

private:
    QString _text;

    static const QMap<ROLE, QString> ROLE_TO_STRING;
};

using MessagePtr = QSharedPointer<Message>;

} // namespace chat

#endif // CHAT_MESSAGE_H
