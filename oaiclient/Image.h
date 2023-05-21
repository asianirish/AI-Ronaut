#ifndef OAIC_IMAGE_H
#define OAIC_IMAGE_H

#include "Component.h"

#include <QSharedPointer>

namespace oaic {

class Image : public Component
{
public:
    Image(Auth *auth, Manager *parent);

    void sendGenImageRequest(const QString &prompt, const QString &size) const;
};


} // namespace oaic

#endif // OAIC_IMAGE_H
