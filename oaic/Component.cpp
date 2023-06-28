#include "Component.h"
#include "Manager.h"

#include <QJsonObject>
#include <QJsonDocument>

namespace oaic {

const QString Component::DEFAULT_URL("https://api.openai.com/v1");

Component::Component(Auth *auth, Manager *parent): QObject(parent),
    _auth(auth),
    _postReply(nullptr),
    _apiUrl(DEFAULT_URL)
{

}

void Component::onJsonRequestFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (reply)
    {
        auto dataRead = reply->readAll();

        if (!dataRead.isEmpty()) { // it's no sence to emit empty strings
            emit jsonResponse(dataRead);
        }

        reply->deleteLater();

        if (reply == _postReply) {
            _postReply = nullptr;
        }
    }
}

void Component::onJsonRequestReadyRead()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    if (reply) {
        auto dataRead = reply->readAll();
        emit jsonResponseStream(dataRead);
    }
}

void Component::onNetworkError(QNetworkReply::NetworkError code)
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    if (reply) {
        QString msg;

        if (code == 0) {
            msg = "No Error (redirect?)";
        } else if (code < 100) {
            msg = "network layer errors";
        } else if (code < 200) {
            msg = "proxy error";
        } else if (code < 300) {
            msg = "content error";
        } else if (code < 400) {
            msg = "protocol error";
        } else {
            msg = "server side error";
        }

        emit networkError(msg, code);

        reply->deleteLater();

        if (reply == _postReply) {
            _postReply = nullptr;
        }
    }
}

QNetworkReply *Component::sendJsonRequest(const QString &endpoint, const QJsonObject &jData, bool stream) const
{
    QString contentType("application/json");
    QNetworkRequest rqst = request(endpoint, contentType);

    QByteArray data = QJsonDocument(jData).toJson();

    auto nam = networkAccessManager();

    _postReply = nam->post(rqst, data);

    connect(_postReply, &QNetworkReply::finished, this, &Component::onJsonRequestFinished);

    // connect error...
    connect(_postReply, &QNetworkReply::errorOccurred, this, &Component::onNetworkError);

    if (stream) {
        connect(_postReply, &QNetworkReply::readyRead, this, &Component::onJsonRequestReadyRead);
    }

    connect(_postReply, &QNetworkReply::destroyed, this, &Component::replyDestroyed);

    return _postReply;
}

QNetworkReply *Component::sendGetRequest(const QString &endpoint) const
{
    Headers headers;
    headers.insert("Accept", "application/json"); // always?

    QNetworkRequest rqst = request(endpoint, headers);

    auto nam = networkAccessManager();

    QNetworkReply *reply = nam->get(rqst);

    connect(reply, &QNetworkReply::finished, this, &Component::onJsonRequestFinished);

    // connect error...
    connect(reply, &QNetworkReply::errorOccurred, this, &Component::onNetworkError);

    connect(reply, &QNetworkReply::destroyed, this, &Component::replyDestroyed);

    return reply;
}

QNetworkReply *Component::postReply() const
{
    return _postReply;
}

QString Component::apiUrl() const
{
    return _apiUrl;
}

void Component::setApiUrl(const QString &newApiUrl)
{
    _apiUrl = newApiUrl;
}

QNetworkRequest Component::request(const QString &endpoint, const QString &contentType) const
{
    QNetworkRequest rqst = this->request(endpoint);

    rqst.setHeader(QNetworkRequest::ContentTypeHeader, contentType);

    return rqst;
}

QNetworkRequest Component::request(const QString &endpoint, const Headers &rawHeaders) const
{
    QNetworkRequest rqst = this->request(endpoint);

    for (auto &[key, value] : rawHeaders.toStdMap()) {
        rqst.setRawHeader(key, value);
    }

    return rqst;
}

QNetworkRequest Component::request(const QString &endpoint) const
{
    QNetworkRequest rqst;
    rqst.setUrl(QUrl(_apiUrl + endpoint));
    auto headers = _auth->headers();

    for (auto &[key, value] : headers.toStdMap()) {
        rqst.setRawHeader(key, value);
    }

    return rqst;
}

QNetworkAccessManager *Component::networkAccessManager() const
{
    auto mngr = parentManager();
    auto nam = mngr->networkAccessManager();

    // QNetworkAccessManager timeout already set in Manager

    return nam;
}

Manager *Component::parentManager() const
{
    return qobject_cast<Manager *>(parent());
}

} // namespace oaic
