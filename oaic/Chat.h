/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef OAIC_CHAT_H
#define OAIC_CHAT_H

#include "Component.h"
#include "MsgData.h"
#include "ModelContext.h"

#include "JsonExtractor.h"

#include <QList>

namespace oaic {

using MsgDataList = QList<MsgData>;

class Chat : public Component
{
    Q_OBJECT
public:
    explicit Chat(Auth *auth, Manager *parent);

    void sendSimpleChatRequest(const QString &model, const QString &content, bool stream) const;
    void sendSimpleChatRequest(const QString &model, const MsgDataList messages, bool stream) const;

    void sendChatRequest(const ModelContext &modelCntx, const QString &content, const QString &sysMsg, bool stream) const;
    void sendChatRequest(const ModelContext &modelCntx, const MsgDataList messages, bool stream) const;

    void abortCurrentResponse();

private:
    QStringList extractMessages(const QString &response, const QString &msgKey);

public slots:
    void onSingleMessageSent(const ModelContext &modelCntx, const QString &content, const QString &sysMsg);
    void onSessionMessagesSent(const ModelContext &modelCntx, const MsgDataList messages);

private slots:
    void handleResponse(const QString &response);
    void handleResponseStream(const QString &response);

signals:
    void messageResponse(const QStringList &messages);
    void messageResponseStream(const QStringList &messages);

private:
    JsonExtractor _jx;
};

} // namespace oaic

#endif // OAIC_CHAT_H
