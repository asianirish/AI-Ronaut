#ifndef CHATSESSIONITEMWIDGET_H
#define CHATSESSIONITEMWIDGET_H

#include "ChatItemWidget.h"
#include "chat/Message.h"

class ChatSessionItemWidget : public ChatItemWidget
{
    Q_OBJECT
public:
    explicit ChatSessionItemWidget(const QString &sessionId, QWidget *parent = nullptr);

    chat::MessagePtr msgPtr();

    void refreshMsg();
    void refreshTextBrowser();

protected:
    virtual chat::Message *createMessage() const = 0;

private:
    chat::MessagePtr _msgPtr;
    QString _sessionId;
};

#endif // CHATSESSIONITEMWIDGET_H
