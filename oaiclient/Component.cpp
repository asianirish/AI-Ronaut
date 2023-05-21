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

        qDebug().noquote() << "DATA READ:" << dataRead;

        reply->deleteLater();
    }
}

void Component::onJsonRequestReadyRead()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    if (reply) {
        auto dataRead = reply->readAll();

        qDebug().noquote() << "DATA READY READ:" << dataRead;
    }
}

QNetworkReply *Component::sendJsonRequest(const QString &endpoint, const QJsonObject &jData) const
{
    QString contentType("application/json");
    QNetworkRequest rqst = request(endpoint, contentType);

    QByteArray data = QJsonDocument(jData).toJson();

    auto nam = networkAccessManager();

    QNetworkReply *reply = nam->post(rqst, data);

    connect(reply, &QNetworkReply::finished, this, &Component::onJsonRequestFinished);
    connect(reply, &QNetworkReply::readyRead, this, &Component::onJsonRequestReadyRead);
    // connect error...

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
