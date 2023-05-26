#ifndef OAIC_TESTIMAGECONSUMER_H
#define OAIC_TESTIMAGECONSUMER_H

#include "Manager.h"
#include "Auth.h"
#include "ImageHandler.h"

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
    ImageHandler *_imageHandler;

signals:

public slots:
    void onUrlResponse(const QStringList &urls);

};

} // namespace oaic

#endif // OAIC_TESTIMAGECONSUMER_H
