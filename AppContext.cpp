#include "AppContext.h"

#include <ModelContext.h>

#include <QStringList>
#include <QDebug>

using namespace liboai;
using namespace oaic;

const int32_t AppContext::DEFAULT_TIMEOUT_MS = 60 * 1000;

AppContext::AppContext() : _timeOutMs(DEFAULT_TIMEOUT_MS)
{

}

const OpenAI &AppContext::oai() const
{
    return _oai;
}

bool AppContext::openKeyFile(const QString &fileName, QString &key, QString *err)
{
    auto ok = _oai.auth.SetKeyFile(fileName.toStdString());

    if (!ok) {
        return false;
    }

    try {
        auto list = _oai.Model->list();
    } catch (liboai::exception::OpenAIException &ex) {
        if (err) {
            *err = ex.what();
        }
        return false;
    } catch (...) {
        if (err) {
            *err = "unknown error";
        }
        return false;
    }

    key = _oai.auth.GetKey().data();

    return true;
}

bool AppContext::setKey(const QString &key, QString *err)
{
    auto ok = _oai.auth.SetKey(key.toStdString());

    if (!ok) {
        return false;
    }

    try {
        auto list = _oai.Model->list();
    } catch (liboai::exception::OpenAIException &ex) {
        if (err) {
            *err = ex.what();
        }
        return false;
    } catch (...) {
        if (err) {
            *err = "unknown error";
        }
        return false;
    }

    return true;
}

QString AppContext::key() const
{
    return QString(_oai.auth.GetKey().data());
}

bool AppContext::setKeyEnv(const QString &envKey, QString *err)
{
    auto ok = _oai.auth.SetKeyEnv(envKey.toStdString());

    if (!ok) {
        return false;
    }

    try {
        auto list = _oai.Model->list();
    } catch (liboai::exception::OpenAIException &ex) {
        if (err) {
            *err = ex.what();
        }
        return false;
    } catch (...) {
        if (err) {
            *err = "unknown error";
        }
        return false;
    }

    return true;
}

QString AppContext::loadImage(const QString &text, const QString &size, QString *err) const
{
    std::string urlStr;
    try {
        Response res = _oai.Image->create(
            text.toStdString(),
            1,
            size.toStdString()
            );

        auto urlRes = res["data"][0]["url"];
        urlStr = urlRes.get<std::string>();
    } catch (liboai::exception::OpenAIException &ex) {
        if (err) {
            *err = ex.what();
        }
        return QString();
    } catch (...) {
        if (err) {
            *err = "unknown error";
        }
        return QString();
    }

    return QString(urlStr.data());
}

void AppContext::modelList(QStringList &list, QString *err) const
{
    try {
        auto response = _oai.Model->list();

        for (auto model : response["data"]) {
            auto strModel = model["id"].get<std::string>();
            qDebug() << strModel.data();
            list.append(QString(strModel.data()));
        }

    } catch (liboai::exception::OpenAIException &ex) {
        if (err) {
            *err = ex.what();
        }
    } catch (...) {
        if (err) {
            *err = "unknown error";
        }
    }
}

QString AppContext::queryAiModel(const QString &input, const ModelContext &modelCntx, QString *err) const
{
    Conversation convo;
    convo.AddUserData(input.toStdString());

    _oai.auth.SetMaxTimeout(_timeOutMs);

    try {
        auto response = _oai.ChatCompletion->create/*_async*/(
            modelCntx.modelName().toStdString(), convo, modelCntx.temperature(),
            std::nullopt, std::nullopt, std::nullopt, std::nullopt,
            modelCntx.maxTokens()
            );

//        response.wait();

        // update our conversation with the response
        convo.Update(response/*.get()*/);

        return QString(convo.GetLastResponse().data());
    } catch (liboai::exception::OpenAIException &ex) {
        if (err) {
            *err = ex.what();
        }
    } catch (...) {
        if (err) {
            *err = "unknown error";
        }
    }

    return QString();
}

void AppContext::queryAiModel(const QString &input, const ModelContext &modelCntx, std::function<bool (std::string, intptr_t)> stream, intptr_t ptr) const
{
    Conversation convo;
    convo.AddUserData(input.toStdString());

    _oai.auth.SetMaxTimeout(_timeOutMs);

    auto response = _oai.ChatCompletion->create(
        modelCntx.modelName().toStdString(), convo, modelCntx.temperature(),
        std::nullopt, std::nullopt, stream, ptr, std::nullopt,
        modelCntx.maxTokens()
        );

}

int32_t AppContext::timeOutMs() const
{
    return _timeOutMs;
}

void AppContext::setTimeOutMs(int32_t newTimeOutMs)
{
    _timeOutMs = newTimeOutMs;
}

