#ifndef OAIC_MANAGER_H
#define OAIC_MANAGER_H

#include "Auth.h"
#include "Image.h"
#include "Chat.h"

namespace oaic {

class Manager : public QObject
{
    Q_OBJECT
public:
    explicit Manager(QObject *parent = nullptr);

    Auth &auth();

    Image *image();

    Chat *chat();


    QNetworkAccessManager *networkAccessManager() const;

private:
    Auth _auth;
    Image *_image;
    Chat *_chat;


    QNetworkAccessManager *_networkAccessManager;
};

} // namespace oaic

#endif // OAIC_MANAGER_H
