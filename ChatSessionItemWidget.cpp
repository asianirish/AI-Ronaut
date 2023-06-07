#include "ChatSessionItemWidget.h"
#include "ChatMessageTextBrowser.h"
#include "chat/SessionManager.h"

ChatSessionItemWidget::ChatSessionItemWidget(const QString &sessionId, QWidget *parent) :
    ChatItemWidget{parent},
    _sessionId(sessionId)
{

}

chat::MessagePtr ChatSessionItemWidget::msgPtr()
{
    if (!_msgPtr) {
        _msgPtr = chat::MessagePtr(createMessage());
        gSessions->addMessage(_msgPtr, _sessionId);

        auto tb = textBrowser();
        auto cmtb = qobject_cast<ChatMessageTextBrowser *>(tb);

        if (cmtb) {
            cmtb->setMsgPtr(_msgPtr);
        }

    }

    return _msgPtr;
}

void ChatSessionItemWidget::refreshMsg()
{
    msgPtr()->setText(text());
}

void ChatSessionItemWidget::refreshTextBrowser()
{
    setText(msgPtr()->text());
}
