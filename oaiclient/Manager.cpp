#include "Manager.h"

namespace oaic {

Manager::Manager()
{

}

Auth &Manager::auth()
{
    return _auth;
}

ImagePtr Manager::image()
{
    return ImagePtr(new Image(_auth));
}

} // namespace oaic
