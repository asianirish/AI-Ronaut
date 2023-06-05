#ifndef CHATSESSIONITEMWIDGET_H
#define CHATSESSIONITEMWIDGET_H

#include "ChatItemWidget.h"
#include "chat/Message.h"

class ChatSessionItemWidget : public ChatItemWidget
{
    Q_OBJECT
public:
    explicit ChatSessionItemWidget(QWidget *parent = nullptr);

    chat::MessagePtr msgPtr() const;
    void setMsgPtr(chat::MessagePtr newMsgPtr);

    void refreshMsg();
    void refreshTextBrowser();

private:
    chat::MessagePtr _msgPtr;
};

#endif // CHATSESSIONITEMWIDGET_H
