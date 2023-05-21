#include "Chat.h"

#include <QJsonObject>
#include <QJsonArray>

namespace oaic {

Chat::Chat(Auth *auth, Manager *parent)
    : Component{auth, parent}
{

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

    auto resp = sendJsonRequest("/chat/completions", obj);

    // TODO: use resp
    (void)resp;
}

} // namespace oaic
