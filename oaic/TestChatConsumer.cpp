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
   connect(_client->chat(), &Chat::messageResponseStream, this, &TestChatConsumer::onMessageResponseStream);

   connect(_client->chat(), &Component::replyDestroyed, this, &TestChatConsumer::onReplyDestroyed);
    // TODO: other connects
}

void TestChatConsumer::requestChat()
{
    static bool firstTime = true;
    static bool useStream = false;


    if (firstTime) {
        std::string useStreamStr;

        std::cout << "Would you like to use a stream response (y/n):";
        std::cin >> useStreamStr;

        if (useStreamStr == "y" || useStreamStr == "yes") {
           useStream = true;
        }

        std::string x;
        std::getline(std::cin,x); // According to authoritative sources (in particular, my opinion ;), this is an acceptable way to solve this well-known issue.

        firstTime = false;
    }

    std::string userPrompt;
    std::cout << "\nuser prompt: ";
    std::getline(std::cin, userPrompt);
    QString userPromptStr = QString::fromUtf8(userPrompt.c_str());



    if (userPrompt == "exit") {
        exit(0);
    } else {
        _client->chat()->sendSimpleChatRequest("gpt-3.5-turbo", userPromptStr, useStream); // "gpt-4"
    }
}

void TestChatConsumer::onMessageResponse(const QStringList &messages)
{
    for (auto &msg : messages) {
        qDebug().noquote() << "MESSAGE:" << msg;
    }
}

void TestChatConsumer::onMessageResponseStream(const QStringList &messages)
{
    for (auto &msg : messages) {
        std::cout << msg.toStdString();
        std::cout.flush();
    }
}

void TestChatConsumer::onReplyDestroyed(QObject *)
{
    requestChat();
}

} // namespace oaic
