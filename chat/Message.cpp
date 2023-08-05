/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#include "Message.h"

#include "chat/SystemMessage.h"
#include "chat/AssistantMessage.h"
#include "chat/UserMessage.h"

#include <QSqlQuery>
#include <QSqlError>

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

MessagePtr Message::createMessage(const oaic::Role &role)
{
    MessagePtr msg;
    if (role == ROLE_TO_STRING.value(Message::SYSTEM)) {
        msg = MessagePtr(new chat::SystemMessage());
    } else if (role == ROLE_TO_STRING.value(Message::USER)) {
        msg = MessagePtr(new chat::UserMessage());
    } else if (role == ROLE_TO_STRING.value(Message::ASSISTANT)) {
        msg = MessagePtr(new chat::AssistantMessage());
    }

    return msg;
}

MessagePtr Message::createMessage(const oaic::MsgData &msgData)
{
    MessagePtr msg = createMessage(msgData.role());

    if (msg) {
        msg->setText(msgData.content());
    }

    return msg;
}

MessagePtr Message::createMessage(const oaic::Role &role, const QString &content)
{
    return createMessage(oaic::MsgData(role, content));
}

bool Message::save(const QString &sessionUuid, int orderNum)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    QString queryString;

    // TODO: for other db engines
    queryString = "INSERT OR REPLACE INTO messages (session_uuid, order_num, role, content) "
                  "VALUES(:session_uuid, :order_num, :role, :content)";

    auto rl = roleAsString();

    qDebug() << "ROLE:" << rl;

    query.prepare(queryString);
    query.bindValue(":session_uuid", sessionUuid);
    query.bindValue(":order_num", orderNum);
    query.bindValue(":role", rl);
    query.bindValue(":content", _text);

    if (query.exec()) {
        qDebug() << "Record successfully added or updated.";
        return true;
    }

    qDebug() << "Query execution error: " << query.lastError().text() << query.lastQuery();
    return false;

    return true;
}

} // namespace chat
