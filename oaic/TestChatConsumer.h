/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

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
    QList<MsgData> _msgs;
    QString _currentAssistantMessage;

private:
    void save();
    void history();

    void setSystemMessage(const QString &content);

private slots:
    void onMessageResponse(const QStringList &messages);
    void onMessageResponseStream(const QStringList &messages);
    void onReplyDestroyed(QObject * = nullptr);
};

} // namespace oaic

#endif // OAIC_TESTCHATCONSUMER_H
