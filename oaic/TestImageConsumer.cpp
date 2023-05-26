#include "TestImageConsumer.h"
#include "Image.h"

#include <QDebug>
#include <iostream>

namespace oaic {

TestImageConsumer::TestImageConsumer(QObject *parent)
    : QObject{parent}
{
    _client = new Manager(this);
    EnvVar env("OPENAI_API_KEY");
    _client->auth().setKeyEnv(env);

    connect(_client->image(), &Image::urlResponse, this, &TestImageConsumer::onUrlResponse);
}

void TestImageConsumer::requestImage()
{

    std::string userImagePrompt;
    std::cout << "user image prompt: ";
    std::getline(std::cin, userImagePrompt);
    QString userImagePromptStr = QString::fromUtf8(userImagePrompt.c_str());

    if (userImagePrompt != "exit") {
        _client->image()->sendGenImageRequest(userImagePromptStr, "256x256");
    }
}

void TestImageConsumer::onUrlResponse(const QStringList &urls)
{
    for (const auto &url : urls) {
        qDebug() << "URL:" << url;
    }

    requestImage();
}

} // namespace oaic
