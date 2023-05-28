#ifndef OAIC_TESTCHATCONSUMER_H
#define OAIC_TESTCHATCONSUMER_H

#include "Manager.h"

#include <QObject>

namespace oaic {

class TestChatConsumer : public QObject
{
public:
    explicit TestChatConsumer(QObject *parent = nullptr);

    void requestChat();

private:
    Manager *_client;

private slots:
    void onMessageResponse(const QStringList &messages);
    void onMessageResponseStream(const QStringList &messages);
    void onReplyDestroyed(QObject * = nullptr);
};

} // namespace oaic

#endif // OAIC_TESTCHATCONSUMER_H
