/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#include "Chat.h"
#include "ModelContext.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>


namespace oaic {

Chat::Chat(Auth *auth, Manager *parent)
    : Component{auth, parent}
{
    connect(this, &Component::jsonResponse, this, &Chat::handleResponse);
    connect(this, &Component::jsonResponseStream, this, &Chat::handleResponseStream);
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

void Chat::sendSimpleChatRequest(const QString &model, const MsgDataList messages, bool stream) const
{
    QJsonObject obj;
    obj.insert("model", model); // "gpt-4"

    QJsonArray conv;

    for (auto &msg : messages) {
        conv.append(msg.toJson());
    }

    obj.insert("messages", conv);
    obj.insert("stream", stream);

    auto resp = sendJsonRequest("/chat/completions", obj, stream);

    // TODO: use resp
    (void)resp;
}

void Chat::sendChatRequest(const ModelContext &modelCntx, const QString &content, const QString &sysMsg, bool stream) const
{
    // "Use your creativity to inspire positivity and promote well-being in your response"
    MsgData systemMsg("system", sysMsg);

    MsgData userMsg("user", content);
    QList<MsgData> messages{systemMsg, userMsg};

    sendChatRequest(modelCntx, messages, stream);

}

void Chat::sendChatRequest(const ModelContext &modelCntx, const MsgDataList messages, bool stream) const
{
    QJsonObject obj;
    obj.insert("model", modelCntx.modelName());
    obj.insert("temperature", modelCntx.temperature());
    obj.insert("top_p", modelCntx.topP());
    // TODO:    obj.insert("n", modelCntx.n());
    obj.insert("stream", stream);
    // TODO:   obj.insert("stop", modelCntx.stop());
    obj.insert("max_tokens", modelCntx.maxTokens());
    obj.insert("presence_penalty", modelCntx.presencePenalty());
    obj.insert("frequency_penalty", modelCntx.frequencyPenalty());
    // TODO:   obj.insert("logit_bias", modelCntx.?
    // TODO:   obj.insert("user", modelCntx.user());

    QJsonArray conv;

    for (auto &msg : messages) {
        conv.append(msg.toJson());
    }

    obj.insert("messages", conv);
    obj.insert("stream", stream);

    auto resp = sendJsonRequest("/chat/completions", obj, stream);



    // TODO: use resp
    (void)resp;
}

void Chat::abortCurrentResponse()
{
    auto reply = postReply();
    if (reply) {
        reply->abort();
    }
}

QStringList Chat::extractMessages(const QString &response, const QString &msgKey)
{
    // TODO: do not emit response for specific delta messages!
    QJsonParseError jerr;

    auto jDoc = QJsonDocument::fromJson(response.toUtf8(), &jerr);

    if (jerr.error != QJsonParseError::NoError) {
        emit responseError(QString("Error parsing JSON:") + jerr.errorString() + "\n" + response);
        return QStringList();
    }
    if (!jDoc.isObject()) {
        emit responseError("the JSON is not an object: " + response);
        return {};
    }
    auto root = jDoc.object();

    // TODO: handle error field?

    if (!root.contains("choices")) {
        emit responseError("unknown API error");
        return {};
    }

    auto choices = root.value("choices").toArray();

    QStringList messages;

    for (auto choice : choices) {
        if (!choice.isObject()) {
            emit responseError("choice JSON is not an object" + response);
            return {};
        }

        auto choiceObj = choice.toObject();

        if (!choiceObj.contains(msgKey)) {
            emit responseError("lack of message JSON" + response);
            return {};
        }

        auto messageVal = choiceObj.value(msgKey);
        if (!messageVal.isObject()) {
            emit responseError("message JSON is not an object" + response);
            return {};
        }

        auto messageObj = messageVal.toObject();

        if (messageObj.contains("content")) {
            auto message = messageObj.value("content").toString();
            //            qDebug() << "MESSAGE:" << message;
            messages.append(message);
        }
    }

    return messages;
}

void Chat::onSingleMessageSent(const ModelContext &modelCntx, const QString &content, const QString &sysMsg)
{
    sendChatRequest(modelCntx, content, sysMsg, true);
}

void Chat::onSessionMessagesSent(const ModelContext &modelCntx, const MsgDataList messages)
{
    sendChatRequest(modelCntx, messages, true);
}

void Chat::handleResponse(const QString &response)
{
    QStringList messages = extractMessages(response, "message");

    if (!messages.isEmpty()) {
        emit messageResponse(messages);
    }
}

void Chat::handleResponseStream(const QString &response)
{
//    qDebug() << "\nstream:" << response;

    QStringList messages;

    bool ok = false;

    auto jsons = _jx.parse(response, ok);

    if (!ok) {
        return;
    }

    for (auto &jsonStr : jsons) {
        QStringList deltas = extractMessages(jsonStr, "delta");
        if (!deltas.isEmpty()) {
            messages.append(deltas);
        }
    }

    if (!messages.isEmpty()) {
        emit messageResponseStream(messages);
    }
}

} // namespace oaic
