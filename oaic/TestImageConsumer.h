/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef OAIC_TESTIMAGECONSUMER_H
#define OAIC_TESTIMAGECONSUMER_H

#include "Manager.h"
#include "Auth.h"

#include <QObject>

namespace oaic {

class TestImageConsumer : public QObject
{
    Q_OBJECT
public:
    explicit TestImageConsumer(QObject *parent = nullptr);

    void requestImage();

private:
    Manager *_client;

signals:

public slots:
    void onUrlResponse(const QStringList &urls);

    void onNetworkError(const QString &errMsg, int errCode);
    void onResponseError(const QString &errMsg);

    void onReplyDestroyed(QObject * = nullptr);

};

} // namespace oaic

#endif // OAIC_TESTIMAGECONSUMER_H
