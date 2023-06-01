#include "Manager.h"

namespace oaic {

const int Manager::DEFAULT_TIMEOUT = 30000;

Manager::Manager(QObject *parent) : QObject(parent),
    _image(nullptr),
    _chat(nullptr),
    _models(nullptr),
    _timeout(Manager::DEFAULT_TIMEOUT)
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

Models *Manager::models()
{
    if (_models) {
        return _models;
    }

    _models = new Models(&_auth, this);
    return _models;
}

QNetworkAccessManager *Manager::networkAccessManager() const
{
    return _networkAccessManager;
}

int Manager::timeout() const
{
    return _timeout;
}

void Manager::setTimeout(int newTimeout)
{
    _timeout = newTimeout;

    // just set the transfer timeout here
    _networkAccessManager->setTransferTimeout(_timeout);
}

} // namespace oaic
