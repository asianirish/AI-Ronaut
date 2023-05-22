#include "Manager.h"

namespace oaic {

Manager::Manager(QObject *parent) : QObject(parent),
    _image(nullptr),
    _chat(nullptr)
{
    _networkAccessManager = new QNetworkAccessManager(this);
}

Auth &Manager::auth()
{
    return _auth;
}

Image *Manager::image()
{
    if (_image) {
        return _image;
    }

    _image = new Image(&_auth, this);
    return _image;
}

Chat *Manager::chat()
{
    if (_chat) {
        return _chat;
    }

    _chat = new Chat(&_auth, this);
    return _chat;
}

QNetworkAccessManager *Manager::networkAccessManager() const
{
    return _networkAccessManager;
}

} // namespace oaic
