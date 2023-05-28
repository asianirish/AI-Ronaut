#include "Component.h"
#include "Manager.h"

#include <QJsonObject>
#include <QJsonDocument>

namespace oaic {

const QString Component::THE_URL("https://api.openai.com/v1");

Component::Component(Auth *auth, Manager *parent): QObject(parent),
    _auth(auth)
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
    }
}

QNetworkReply *Component::sendJsonRequest(const QString &endpoint, const QJsonObject &jData, bool stream) const
{
    QString contentType("application/json");
    QNetworkRequest rqst = request(endpoint, contentType);

    QByteArray data = QJsonDocument(jData).toJson();

    auto nam = networkAccessManager();

    QNetworkReply *reply = nam->post(rqst, data);

    connect(reply, &QNetworkReply::finished, this, &Component::onJsonRequestFinished);

    // connect error...
    connect(reply, &QNetworkReply::errorOccurred, this, &Component::onNetworkError);

    if (stream) {
        connect(reply, &QNetworkReply::readyRead, this, &Component::onJsonRequestReadyRead);
    }

    connect(reply, &QNetworkReply::destroyed, this, &Component::replyDestroyed);

    return reply;
}

QNetworkRequest Component::request(const QString &endpoint, const QString &contentType) const
{
    QNetworkRequest rqst;
    rqst.setUrl(QUrl(THE_URL + endpoint));
    rqst.setHeader(QNetworkRequest::ContentTypeHeader, contentType);

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

    // refresh timeout every time before using
    nam->setTransferTimeout(_auth->timeout());

    // TODO: set other settings from _auth

    return nam;
}

Manager *Component::parentManager() const
{
    return qobject_cast<Manager *>(parent());
}

} // namespace oaic
