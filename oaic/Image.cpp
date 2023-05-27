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
    QJsonParseError jerr;

    auto jDoc = QJsonDocument::fromJson(response.toUtf8(), &jerr); // TODO: use json parser error

    if (jerr.error != QJsonParseError::NoError) {
        emit responseError(QString("Error parsing JSON:") + jerr.errorString());
        return;
    }

    if (!jDoc.isObject()) {
        emit responseError("the JSON is not an object: " + response);
        return;
    }
    auto root = jDoc.object();

    if (root.contains("error")) {
        auto errorValue = root.value("error");
        if (errorValue.isObject()) {
            auto errObj = errorValue.toObject();

            if (errObj.contains("message") && errObj.value("message").isString()) {
                auto errMsg = errObj.value("message").toString();
                emit responseError(QString("API error: ") + errMsg);
            } else {
                emit responseError(QString("unknown API error"));
            }
        } else {
            emit responseError(QString("API error: ") + root.value("error").toString());
        }
        return;
    }

    if (!root.contains("data")) {
        emit responseError("unknown API error");
        return;
    }

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
