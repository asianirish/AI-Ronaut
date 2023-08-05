/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef CHATSESSIONITEMWIDGET_H
#define CHATSESSIONITEMWIDGET_H

#include "ChatItemWidget.h"
#include "chat/Message.h"

class ChatSessionItemWidget : public ChatItemWidget
{
    Q_OBJECT
public:
    explicit ChatSessionItemWidget(const QString &sessionId, chat::MessagePtr msgPtr = {}, QWidget *parent = nullptr);

    chat::MessagePtr msgPtr();

    void refreshMsg();
    void refreshTextBrowser(); // TODO: delete?

    void deleteMessage();

    void editMessage();

protected:
    virtual chat::Message *createMessage() const = 0;

private:
    chat::MessagePtr _msgPtr;
    QString _sessionId;
};

#endif // CHATSESSIONITEMWIDGET_H
