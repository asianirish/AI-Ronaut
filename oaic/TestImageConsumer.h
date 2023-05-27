#ifndef OAIC_TESTIMAGECONSUMER_H
#define OAIC_TESTIMAGECONSUMER_H

#include "Manager.h"
#include "Auth.h"

#include <QObject>

namespace oaic {

class TestImageConsumer : public QObject
{
    Q_OBJECT
public:
    explicit TestImageConsumer(QObject *parent = nullptr);

    void requestImage();

private:
    Manager *_client;

signals:

public slots:
    void onUrlResponse(const QStringList &urls);

    void onNetworkError(const QString &errMsg, int errCode);
    void onResponseError(const QString &errMsg);

    void onReplyDestroyed(QObject * = nullptr);

};

} // namespace oaic

#endif // OAIC_TESTIMAGECONSUMER_H
