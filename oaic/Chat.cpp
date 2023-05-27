#include "Chat.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

namespace oaic {

Chat::Chat(Auth *auth, Manager *parent)
    : Component{auth, parent}
{
    connect(this, &Component::jsonResponse, this, &Chat::handleResponse);
}

void Chat::sendSimpleChatRequest(const QString &model, const QString &content, bool stream) const
{
    QJsonObject obj;
    obj.insert("model", model); // "gpt-4"

    QJsonObject sysMsg;
    sysMsg.insert("role", "system");
    sysMsg.insert("content",
                  "Use your creativity to inspire positivity and promote well-being in your response");


    QJsonObject msg;
    msg.insert("role", "user");
    msg.insert("content", content);

    QJsonArray conv;
    conv.append(sysMsg);
    conv.append(msg);

    obj.insert("messages", conv);
    obj.insert("stream", stream);

    auto resp = sendJsonRequest("/chat/completions", obj, stream);

    // TODO: use resp
    (void)resp;
}

void Chat::sendSimpleChatRequest(const QString &model, const QList<MsgData> messages, bool stream) const
{
    QJsonObject obj;
    obj.insert("model", model); // "gpt-4"

    QJsonObject sysMsg;
    sysMsg.insert("role", "system");
    sysMsg.insert("content",
                  "Use your creativity to inspire positivity and promote well-being in your response");

    QJsonArray conv;
    conv.append(sysMsg);

    for (auto &msg : messages) {
        conv.append(msg.toJson());
    }

    obj.insert("messages", conv);
    obj.insert("stream", stream);

    auto resp = sendJsonRequest("/chat/completions", obj, stream);

    // TODO: use resp
    (void)resp;
}

void Chat::handleResponse(const QString &response)
{
    QJsonParseError jerr;

    auto jDoc = QJsonDocument::fromJson(response.toUtf8(), &jerr);

    if (jerr.error != QJsonParseError::NoError) {
        emit responseError(QString("Error parsing JSON:") + jerr.errorString());
        return;
    }
    if (!jDoc.isObject()) {
        emit responseError("the JSON is not an object: " + response);
        return;
    }
    auto root = jDoc.object();

    // TODO: handle error field?

    if (!root.contains("choices")) {
        emit responseError("unknown API error");
        return;
    }

    auto choices = root.value("choices").toArray();

    QStringList messages;

    for (auto choice : choices) {
        if (!choice.isObject()) {
            emit responseError("choice JSON is not an object" + response);
            return;
        }

        auto choiceObj = choice.toObject();

        if (!choiceObj.contains("message")) {
            emit responseError("lack of message JSON" + response);
            return;
        }

        auto messageVal = choiceObj.value("message");
        if (!messageVal.isObject()) {
            emit responseError("message JSON is not an object" + response);
            return;
        }

        auto messageObj = messageVal.toObject();

        if (messageObj.contains("content")) {
            auto message = messageObj.value("content").toString();
//            qDebug() << "MESSAGE:" << message;
            messages.append(message);
        }
    }

    emit messageResponse(messages);

}

} // namespace oaic
