#include "Manager.h"
#include "TestImageConsumer.h"

#include <QCoreApplication>
#include <iostream>

using namespace oaic;


Manager &authorize() {
    static Manager client;
    EnvVar env("OPENAI_API_KEY");
    client.auth().setKeyEnv(env);

    return client;
}

void sendImgRequest() {

    Manager &client = authorize();
    std::string userImagePrompt;
    std::cout << "user image prompt: ";
    std::getline(std::cin, userImagePrompt);
    QString userImagePromptStr = QString::fromUtf8(userImagePrompt.c_str());

    client.image()->sendGenImageRequest(userImagePromptStr, "256x256");
}

void sendChatRequest() {
    Manager &client = authorize();

    std::string userImagePrompt;
    std::cout << "user message: ";
    std::getline(std::cin, userImagePrompt);

    QString qmsg(userImagePrompt.data());

    std::string stream;
    bool isStream = false;
    std::cout << "use stream? (y/n)";
    std::cin >> stream;

    if (stream.at(0) == 'y') {
        isStream = true;
    }

    client.chat()->sendSimpleChatRequest("gpt-4", qmsg, isStream);
}


// TODO: make it async!
//void sendMultiChatRequest() {
//    Manager &client = authorize();

//    while (1) {
//        std::string userImagePrompt;
//        std::cout << "user image prompt: ";
//        std::getline(std::cin, userImagePrompt);

//        if (userImagePrompt == "exit") {
//            return;
//        }

//        QString qmsg(userImagePrompt.data());


//        client.chat()->sendSimpleChatRequest("gpt-4", qmsg, false);

//    }
//}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TestImageConsumer *consumer = new TestImageConsumer();
    consumer->requestImage();

//    sendImgRequest();
//    sendChatRequest();

    return a.exec();
}
