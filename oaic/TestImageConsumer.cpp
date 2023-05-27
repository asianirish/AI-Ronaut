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
    connect(_client->image(), &Component::networkError, this, &TestImageConsumer::onNetworkError);
    connect(_client->image(), &Component::responseError, this, &TestImageConsumer::onResponseError);
    connect(_client->image(), &Component::replyDestroyed, this, &TestImageConsumer::onReplyDestroyed);
}

void TestImageConsumer::requestImage()
{
    std::string userImagePrompt;
    std::cout << "user image prompt: ";
    std::getline(std::cin, userImagePrompt);
    QString userImagePromptStr = QString::fromUtf8(userImagePrompt.c_str());

    if (userImagePrompt == "exit") {
        exit(0);
    } else {
        _client->image()->sendGenImageRequest(userImagePromptStr, "256x256");
    }
}

void TestImageConsumer::onUrlResponse(const QStringList &urls)
{
    for (const auto &url : urls) {
        qDebug() << "URL:" << url;
    }
}

void TestImageConsumer::onNetworkError(const QString &errMsg, int errCode)
{
    qDebug() << "NETWORK ERROR:" << errMsg << " code:" << errCode;
}

void TestImageConsumer::onResponseError(const QString &errMsg)
{
    qDebug() << "ERROR! " << errMsg;
}

void TestImageConsumer::onReplyDestroyed(QObject *)
{
    qDebug() << "the reply is destroyed";
    requestImage();
}

} // namespace oaic
