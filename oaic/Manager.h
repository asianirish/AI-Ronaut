/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

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

    static Auth &auth();

    Image *image();

    Chat *chat();

    Models *models();

    QNetworkAccessManager *networkAccessManager() const;

    int timeout() const;
    void setTimeout(int newTimeout);

private:
    static Auth _auth;
    Image *_image;
    Chat *_chat;
    Models *_models;

    QNetworkAccessManager *_networkAccessManager;

    int _timeout; // in ms
};

} // namespace oaic

#endif // OAIC_MANAGER_H
