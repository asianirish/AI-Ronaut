#include "ChatSessionItemWidget.h"
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
