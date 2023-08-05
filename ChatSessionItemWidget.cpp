/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#include "ChatSessionItemWidget.h"
#include "ChatMessageTextBrowser.h"
#include "chat/SessionManager.h"

ChatSessionItemWidget::ChatSessionItemWidget(const QString &sessionId, chat::MessagePtr msgPtr, QWidget *parent) :
    ChatItemWidget{parent},
    _msgPtr(msgPtr),
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

    auto tb = textBrowser();
    auto cmtb = qobject_cast<ChatMessageTextBrowser *>(tb);

    if (cmtb && cmtb->msgPtr().isNull()) {
        cmtb->setMsgPtr(_msgPtr);
    }
}

void ChatSessionItemWidget::refreshTextBrowser()
{
    setText(msgPtr()->text());
}

void ChatSessionItemWidget::deleteMessage()
{
    if (_msgPtr) {
        gSessions->deleteMessage(_sessionId, _msgPtr);
    }
}

void ChatSessionItemWidget::editMessage()
{
    textBrowser()->setReadOnly(false);
    textBrowser()->setFocus();
}
