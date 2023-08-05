/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

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
