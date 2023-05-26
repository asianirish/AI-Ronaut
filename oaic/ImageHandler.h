#ifndef OAIC_IMAGEHANDLER_H
#define OAIC_IMAGEHANDLER_H

#include "Image.h"

#include <QObject>

namespace oaic {

class ImageHandler : public QObject
{
    Q_OBJECT
public:
    explicit ImageHandler(Image *image, QObject *parent = nullptr);

private:
    Image *_image;


public slots:
    void onResponse(const QString &response);

signals:
    void urlResponse(const QStringList &urls);

};

} // namespace oaic

#endif // OAIC_IMAGEHANDLER_H
