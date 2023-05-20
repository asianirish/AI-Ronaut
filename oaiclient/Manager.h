#ifndef OAIC_MANAGER_H
#define OAIC_MANAGER_H

#include "Auth.h"
#include "Image.h"

namespace oaic {

class Manager
{
public:
    Manager();

    Auth &auth();

    ImagePtr image();

private:
    Auth _auth;
};

} // namespace oaic

#endif // OAIC_MANAGER_H
