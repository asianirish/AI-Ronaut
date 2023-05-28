#ifndef OAIC_CHAT_H
#define OAIC_CHAT_H

#include "Component.h"
#include "MsgData.h"

#include <QList>

namespace oaic {

class Chat : public Component
{
    Q_OBJECT
public:
    explicit Chat(Auth *auth, Manager *parent);

    void sendSimpleChatRequest(const QString &model, const QString &content, bool stream) const;

    void sendSimpleChatRequest(const QString &model, const QList<MsgData> messages, bool stream) const;

private:
    QStringList extractMessages(const QString &response, const QString &msgKey);

private slots:
    void handleResponse(const QString &response);
    void handleResponseStream(const QString &response);

signals:
    void messageResponse(const QStringList &messages);
    void messageResponseStream(const QStringList &messages);
};

} // namespace oaic

#endif // OAIC_CHAT_H
