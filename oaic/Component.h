#ifndef OAIC_COMPONENT_H
#define OAIC_COMPONENT_H

#include "Auth.h"

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace oaic {

class Manager;

class Component : public QObject
{
    Q_OBJECT
public:
    static const QString THE_URL;

    Component() = delete;
    Component(QObject *parent) = delete;
    explicit Component(Auth *auth, Manager *parent);

    virtual ~Component() = default;

private slots:

    void onJsonRequestFinished();
    void onJsonRequestReadyRead();

protected:
    QNetworkReply *sendJsonRequest(const QString &endpoint, const QJsonObject &jData, bool stream) const;

private:
    Auth *_auth;

    QNetworkRequest request(const QString &endpoint, const QString &contentType) const;

    QNetworkAccessManager *networkAccessManager() const;

    Manager *parentManager() const;

signals:
    void jsonResponse(const QString &response);
    void jsonResponseStream(const QString &response);

};

} // namespace oaic

#endif // OAIC_COMPONENT_H
