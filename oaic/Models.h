/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef OAIC_MODELS_H
#define OAIC_MODELS_H

#include "Component.h"

namespace oaic {

class Models : public Component
{
    Q_OBJECT
public:
    explicit Models(Auth *auth, Manager *parent = nullptr);

    void modelList() const;

private slots:
    void handleResponse(const QString &response);

signals:
    void models(const QStringList &mdls);
};

} // namespace oaic

#endif // OAIC_MODELS_H
