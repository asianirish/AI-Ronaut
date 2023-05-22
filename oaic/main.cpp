#include "Manager.h"

#include <QCoreApplication>
#include <iostream>

using namespace oaic;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Manager client;
    EnvVar env("OPENAI_API_KEY");
    client.auth().setKeyEnv(env);

    std::string userImagePrompt;
    std::cout << "user image prompt: ";
    std::getline(std::cin, userImagePrompt);

    QString userImagePromptStr = QString::fromUtf8(userImagePrompt.c_str());

    client.image()->sendGenImageRequest(userImagePromptStr, "256x256");

    client.chat()->sendSimpleChatRequest("gpt-4", "hi", false);

    return a.exec();
}
