#include "Models.h"

namespace oaic {

Models::Models(Auth *auth, Manager *parent)
    : Component{auth, parent}
{
    connect(this, &Component::jsonResponse, this, &Models::handleResponse);
}

void Models::modelList() const
{
    auto resp = sendGetRequest("/models");

    // TODO: use resp
    (void)resp;
}

void Models::handleResponse(const QString &response)
{
    qDebug().noquote() << "MODELS RESPONSE:" << response;
    // TODO: parse response
}

} // namespace oaic
