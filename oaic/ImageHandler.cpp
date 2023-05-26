#include "ImageHandler.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

namespace oaic {

ImageHandler::ImageHandler(Image *image, QObject *parent)
    : QObject{parent},
    _image(image)
{
    connect(_image, &Component::jsonResponse, this, &ImageHandler::onResponse);
}

void ImageHandler::onResponse(const QString &response)
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
