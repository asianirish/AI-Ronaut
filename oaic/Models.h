#ifndef OAIC_MODELS_H
#define OAIC_MODELS_H

#include "Component.h"

namespace oaic {

class Models : public Component
{
public:
    explicit Models(Auth *auth, Manager *parent = nullptr);

    void modelList() const;

private slots:
    void handleResponse(const QString &response);
};

} // namespace oaic

#endif // OAIC_MODELS_H
