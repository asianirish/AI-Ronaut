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
