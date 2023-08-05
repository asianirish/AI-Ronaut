/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef CHAT_MESSAGE_H
#define CHAT_MESSAGE_H

#include <oaic/MsgData.h>

#include <QString>
#include <QSharedPointer>
#include <QMap>

namespace chat {

class Message;

using MessagePtr = QSharedPointer<Message>;

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

    static MessagePtr createMessage(const oaic::Role &role);
    static MessagePtr createMessage(const oaic::MsgData &msgData);
    static MessagePtr createMessage(const oaic::Role &role, const QString &content);

    bool save(const QString &sessionUuid, int orderNum);

private:
    QString _text;

    static const QMap<ROLE, QString> ROLE_TO_STRING;
};


} // namespace chat

#endif // CHAT_MESSAGE_H
