#include "OpenAIApiHandler.h"
#include "AppContext.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

using namespace liboai;

std::vector<std::string> extractJSON(const std::string& input) {
    std::vector<std::string> jsons;
    std::size_t start = 0;
    std::size_t end = 0;
    int brackets = 0;
    bool in_json = false;
    for (std::size_t i = 0; i < input.size(); ++i) {
        if (input[i] == '{') {
            if (!in_json) {
                start = i;
                in_json = true;
            }
            brackets++;
        } else if (input[i] == '}') {
            brackets--;
            if (brackets == 0 && in_json) {
                end = i;
                in_json = false;
                jsons.push_back(input.substr(start, end - start + 1));
            }
        }
    }
    return jsons;
}

std::vector<std::string> extractJSONByDataKeyword(const std::string& input) {
    std::vector<std::string> jsons;
    std::size_t start = 0;
    std::size_t end = 0;
    while ((start = input.find("data:", end)) != std::string::npos) {
        start += 5; // skip "data:"
        end = input.find("data:", start);
        if (end == std::string::npos) {
            // this is the last json
            jsons.push_back(input.substr(start));
        } else {
            // there are more jsons
            jsons.push_back(input.substr(start, end - start));
        }
    }
    return jsons;
}

bool myStream(std::string data, intptr_t userdata)
{
    std::vector<std::string> jsons = extractJSON(data);

    OpenAIApiHandler *handler = (OpenAIApiHandler *)userdata;

    for (const auto& json : jsons) {
        handler->handle(json);
    }

    return true;
}

OpenAIApiHandler::OpenAIApiHandler(QObject *parent)
    : QObject{parent}
{

}

void OpenAIApiHandler::queryAiModel(const QString &input, const QString &key, const ModelContext &modelCntx)
{
    AppContext appContext;
    appContext.setKey(key);

    // set timeout here?

    try {
        appContext.queryAiModel(input, modelCntx, myStream, (intptr_t)this);
    } catch (std::exception &ex) {
        emit error(ex.what());
    } catch (...) {
        qDebug() << "UNKNOWN ERROR";
        emit error("unknown error");
    }

    // TODO: emit error(err);

    emit complete();
}

void OpenAIApiHandler::handle(const std::string jData)
{
    static bool first = true;
    QString str(jData.data());

    if (first) {
        qDebug() << "FIRST WHOLE DATA:" << str;
        qDebug() << "END OF FIRST WHOLE DATA";
    }

    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
    QJsonObject jRoot;

    jRoot = doc.object();
    QJsonArray jChoices = jRoot.value("choices").toArray();

    if (jChoices.count() > 0) {
        QJsonObject jFirstObj = jChoices.at(0).toObject();
        QJsonObject jDelta = jFirstObj.value("delta").toObject();

        if (!jDelta.isEmpty()) {
            QJsonValue jContent = jDelta.value("content");
            QString strContent = jContent.toString();

            if (first) {
                qDebug() << "FIRST CONTENT:" << strContent;
                first = false;
            }
            emit delta(strContent);
        }
    }



    // TODO: emit error

}
