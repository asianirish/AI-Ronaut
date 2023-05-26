#ifndef OAIC_IMAGE_H
#define OAIC_IMAGE_H

#include "Component.h"

#include <QSharedPointer>

namespace oaic {

class Image : public Component
{
    Q_OBJECT
public:
    Image(Auth *auth, Manager *parent);

    void sendGenImageRequest(const QString &prompt, const QString &size) const;

private slots:
    void handleResponse(const QString &response);

signals:
    void urlResponse(const QStringList &urls);
};


} // namespace oaic

#endif // OAIC_IMAGE_H
