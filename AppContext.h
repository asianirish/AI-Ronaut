#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreorder"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <liboai.h>
#pragma GCC diagnostic pop


#include <optional>

#include <QString>

class ModelContext;

class AppContext
{
public:
    static const int32_t DEFAULT_TIMEOUT_MS;
    AppContext();

    const liboai::OpenAI &oai() const;

    bool openKeyFile(const QString &fileName, QString &key, QString *err = nullptr);
    bool setKey(const QString &key, QString *err = nullptr);
    QString key() const;

    // TODO: add other args
    QString loadImage(const QString &text, const QString &size, QString *err = nullptr) const;

    void modelList(QStringList &list, QString *err = nullptr) const;

    QString queryAiModel(const QString &input, const ModelContext &modelCntx, QString *err = nullptr) const;
    void queryAiModel(const QString &input, const ModelContext &modelCntx, std::function<bool(std::string data, intptr_t ptr)> stream, intptr_t ptr) const;

    int32_t timeOutMs() const;
    void setTimeOutMs(int32_t newTimeOutMs);

private:
    liboai::OpenAI _oai;
    int32_t _timeOutMs;
};

#endif // APPCONTEXT_H
