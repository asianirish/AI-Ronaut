#include "Image.h"

#include <QJsonObject>

namespace oaic {

Image::Image(Auth *auth, Manager *parent) : Component(auth, parent)
{

}

void Image::sendGenImageRequest(const QString &prompt, const QString &size) const
{
    QJsonObject obj;
    obj.insert("prompt", prompt);
    obj.insert("size", size);

    auto resp = sendJsonRequest("/images/generations", obj);

    // TODO: use resp
    (void)resp;
}

} // namespace oaic
