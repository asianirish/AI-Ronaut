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
    static const QString DEFAULT_URL;

    Component() = delete;
    Component(QObject *parent) = delete;
    explicit Component(Auth *auth, Manager *parent);

    virtual ~Component() = default;
    QString apiUrl() const;
    void setApiUrl(const QString &newApiUrl);

private slots:

    void onJsonRequestFinished();
    void onJsonRequestReadyRead();

    void onNetworkError(QNetworkReply::NetworkError code);

protected:
    QNetworkReply *sendJsonRequest(const QString &endpoint, const QJsonObject &jData, bool stream) const;
    QNetworkReply *sendGetRequest(const QString &endpoint) const;

    QNetworkReply *postReply() const;

private:
    Auth *_auth;
    mutable QNetworkReply *_postReply;
    QString _apiUrl;

    QNetworkRequest request(const QString &endpoint, const QString &contentType) const;
    QNetworkRequest request(const QString &endpoint, const Headers &rawHeaders) const;
    QNetworkRequest request(const QString &endpoint) const;

    QNetworkAccessManager *networkAccessManager() const;

    Manager *parentManager() const;

signals:
    void jsonResponse(const QString &response);
    void jsonResponseStream(const QString &response);

    void responseError(const QString &desc);
    void networkError(const QString &errMsg, int errCode);

    void replyDestroyed(QObject * = nullptr);

};

} // namespace oaic

#endif // OAIC_COMPONENT_H
