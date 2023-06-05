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

//        qDebug() << modelId;
        if (modelId.left(4) == "gpt-" || modelId == "text-davinci-002") {
            QJsonDocument doc(part.toObject());
            qDebug().noquote() << doc.toJson() << "\n";
        }
    }

    emit models(mdls);

//    qDebug() << "MODELS:" << mdls;
}

} // namespace oaic
