#include "TestChatConsumer.h"
#include "Chat.h"

#include <QDebug>
#include <iostream>

#include <QDateTime>
#include <QFile>

namespace oaic {

TestChatConsumer::TestChatConsumer(QObject *parent)
    : QObject{parent},
    _useSession(true)
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

        {
            std::string x;
            std::getline(std::cin,x); // According to authoritative sources (in particular, my opinion ;), this is an acceptable way to solve this well-known issue.
        }

        {
            std::string userPrompt;
            std::cout << "\nsystem message: ";
            std::getline(std::cin, userPrompt);
            QString userPromptStr = QString::fromUtf8(userPrompt.c_str());

            setSystemMessage(userPromptStr); // add to _msgs
        }

        firstTime = false;
    }

    std::string userPrompt;
    std::cout << "\nuser prompt: ";
    std::getline(std::cin, userPrompt);
    QString userPromptStr = QString::fromUtf8(userPrompt.c_str());



    if (userPrompt == "exit") {
        exit(0);
    } else if (userPrompt == "save") {
        save();
        exit(0);
    } else if (userPrompt == "history") {
        history();
        requestChat();
    } else if (_useSession) {
        MsgData curData("user", userPromptStr);
        _msgs.append(curData);
        ModelContext cntx; // default values, model == gpt-3.5-turbo
        //        cntx.setModelName("gpt-4");
        _client->chat()->sendChatRequest(cntx, _msgs, useStream);
    } else {
        qDebug() << "SENDING:" << userPromptStr;
        ModelContext cntx; // default values, model == gpt-3.5-turbo
//        cntx.setModelName("gpt-4");
        _client->chat()->sendChatRequest(cntx, userPromptStr, useStream);
    }
}

void TestChatConsumer::save()
{
    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("yyyyMMddhhmmss");
    QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();

    QFile file(formattedTimeMsg);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    for (auto &msg : _msgs) {
        file.write(msg.role().toLatin1() + ": ");
        file.write(msg.content().toUtf8());
        file.write("\n");
    }

    file.close();

}

void TestChatConsumer::history()
{
    qDebug() << "\n..........History:.........\n";
    for (auto &msg : _msgs) {
        qDebug() << msg.role() + ": " << msg.content();
    }
    qDebug() << "\n............................\n";
}

void TestChatConsumer::setSystemMessage(const QString &content)
{
    QString contentCp(content);

    if (content.isEmpty()) {
        contentCp = "Use your creativity to inspire positivity and promote well-being in your response";
    }

    MsgData curData("system", contentCp);
    _msgs.append(curData);
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

        if (_useSession) {
            _currentAssistantMessage += msg;
        }

        std::cout << msg.toStdString();
        std::cout.flush();
    }
}

void TestChatConsumer::onReplyDestroyed(QObject *)
{
    if (_useSession) {
        MsgData curData;
        curData.setRole("assistant");
        curData.setContent(_currentAssistantMessage);
        _msgs.append(curData);
        _currentAssistantMessage.clear();
    }

    requestChat();
}

} // namespace oaic
