#include "ChatSessionItemWidget.h"

ChatSessionItemWidget::ChatSessionItemWidget(QWidget *parent) :
    ChatItemWidget{parent}
{

}

chat::MessagePtr ChatSessionItemWidget::msgPtr() const
{
    return _msgPtr;
}

void ChatSessionItemWidget::setMsgPtr(chat::MessagePtr newMsgPtr)
{
    _msgPtr = newMsgPtr;
}

void ChatSessionItemWidget::refreshMsg()
{
    if (_msgPtr) {
        _msgPtr->setText(text());
    }
}

void ChatSessionItemWidget::refreshTextBrowser()
{
    if (_msgPtr) {
        setText(_msgPtr->text());
    }
}
