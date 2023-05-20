#ifndef OAIC_IMAGE_H
#define OAIC_IMAGE_H

#include "Component.h"

#include <QSharedPointer>

namespace oaic {

class Image : public Component
{
public:
    Image(Auth &auth);
};

using ImagePtr = QSharedPointer<Image>;

} // namespace oaic

#endif // OAIC_IMAGE_H
