/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#include "Models.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

namespace oaic {

Models::Models(Auth *auth, Manager *parent)
    : Component{auth, parent}
{
    connect(this, &Component::jsonResponse, this, &Models::handleResponse);
}

void Models::modelList() const
{
    auto resp = sendGetRequest("/models");

    // TODO: use resp
    (void)resp;
}

void Models::handleResponse(const QString &response)
{
    QJsonParseError jerr;

    auto jDoc = QJsonDocument::fromJson(response.toUtf8(), &jerr);

    if (jerr.error != QJsonParseError::NoError) {
        emit responseError(QString("Error parsing JSON:") + jerr.errorString());
        return;
    }

    if (!jDoc.isObject()) {
        emit responseError("the JSON is not an object: " + response);
        return;
    }

    auto root = jDoc.object();

    if (!root.contains("data")) {
        emit responseError("unknown API error");
        return;
    }

    QJsonArray data = root.value("data").toArray();

    QStringList mdls;
    for (auto part : data) {
        if (!part.isObject()) {
            emit responseError("part JSON is not an object" + response);
            return;
        }

        auto partObj = part.toObject();

        if (!partObj.contains("id")) {
            emit responseError("lack of id JSON" + response);
            return;
        }

        auto modelId = partObj.value("id").toString();

        mdls.append(modelId);
    }

    emit models(mdls);
}

} // namespace oaic
