#ifndef OAIC_MANAGER_H
#define OAIC_MANAGER_H

#include "Auth.h"
#include "Image.h"
#include "Chat.h"
#include "Models.h"

namespace oaic {

class Manager : public QObject
{
    Q_OBJECT
public:
    static const int DEFAULT_TIMEOUT;
    explicit Manager(QObject *parent = nullptr);

    Auth &auth();

    Image *image();

    Chat *chat();

    Models *models();


    QNetworkAccessManager *networkAccessManager() const;

    int timeout() const;
    void setTimeout(int newTimeout);

private:
    Auth _auth;
    Image *_image;
    Chat *_chat;
    Models *_models;

    QNetworkAccessManager *_networkAccessManager;

    int _timeout; // in ms
};

} // namespace oaic

#endif // OAIC_MANAGER_H
