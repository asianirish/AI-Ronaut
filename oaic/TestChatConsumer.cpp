#include "TestChatConsumer.h"
#include "Chat.h"

#include <QDebug>
#include <iostream>

namespace oaic {

TestChatConsumer::TestChatConsumer(QObject *parent)
    : QObject{parent}
{
    _client = new Manager(this);
    EnvVar env("OPENAI_API_KEY");
    _client->auth().setKeyEnv(env);

   connect(_client->chat(), &Chat::messageResponse, this, &TestChatConsumer::onMessageResponse);
   connect(_client->chat(), &Component::replyDestroyed, this, &TestChatConsumer::onReplyDestroyed);
    // TODO: other connects
}

void TestChatConsumer::requestChat()
{
    std::string userPrompt;
    std::cout << "user prompt: ";
    std::getline(std::cin, userPrompt);
    QString userPromptStr = QString::fromUtf8(userPrompt.c_str());

    if (userPrompt == "exit") {
        exit(0);
    } else {
        _client->chat()->sendSimpleChatRequest("gpt-4", userPromptStr, false);
    }
}

void TestChatConsumer::onMessageResponse(const QStringList &messages)
{
    for (auto &msg : messages) {
        qDebug().noquote() << "MESSAGE:" << msg;
    }
}

void TestChatConsumer::onReplyDestroyed(QObject *)
{
    requestChat();
}

} // namespace oaic
