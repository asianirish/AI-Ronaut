#include "Image.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>


namespace oaic {

Image::Image(Auth *auth, Manager *parent) : Component(auth, parent)
{
    connect(this, &Component::jsonResponse, this, &Image::handleResponse);
}

void Image::sendGenImageRequest(const QString &prompt, const QString &size) const
{
    QJsonObject obj;
    obj.insert("prompt", prompt);
    obj.insert("size", size);

    auto resp = sendJsonRequest("/images/generations", obj, false);

    // TODO: use resp
    (void)resp;
}

void Image::handleResponse(const QString &response)
{
    auto jDoc = QJsonDocument::fromJson(response.toUtf8()); // TODO: use json parser error
    auto root = jDoc.object();

    auto dataArr = root.value("data").toArray();

    QStringList urls;

    for (auto urlVal : dataArr) {
        auto urlObj = urlVal.toObject();
        QString url = urlObj.value("url").toString();
        urls.append(url);
    }

    emit urlResponse(urls);
}

} // namespace oaic
