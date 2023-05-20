#ifndef OAIC_COMPONENT_H
#define OAIC_COMPONENT_H

#include "Auth.h"

namespace oaic {

class Component
{
public:
    Component() = delete;
    Component(Auth &auth);

private:
    Auth *_auth;
};

} // namespace oaic

#endif // OAIC_COMPONENT_H
