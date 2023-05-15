#ifndef OPENAIAPIHANDLER_H
#define OPENAIAPIHANDLER_H

#include "ModelContext.h"

#include <QObject>

class OpenAIApiHandler : public QObject
{
    Q_OBJECT
public:
    explicit OpenAIApiHandler(QObject *parent = nullptr);

    void handle(const std::string data);

public slots:
    void queryAiModel(const QString &input, const QString &key, const ModelContext &modelCntx);


signals:
    void delta(const QString &deltaValue);

    void error(const QString &err);

    void complete();
private:


};

#endif // OPENAIAPIHANDLER_H
