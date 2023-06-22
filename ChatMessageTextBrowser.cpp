#include "ChatMessageTextBrowser.h"

ChatMessageTextBrowser::ChatMessageTextBrowser(QWidget *parent) : QTextBrowser(parent)
{

}

void ChatMessageTextBrowser::focusOutEvent(QFocusEvent *e)
{
//    Q_UNUSED(e);

    if (!this->isReadOnly()) {
        auto text = this->toPlainText();
        qDebug() << "THE TEXT IS:" << text;
        setReadOnly(true);

        if (_msgPtr) {
            _msgPtr->setText(text);
        }
    }

    QTextBrowser::focusOutEvent(e);
}

void ChatMessageTextBrowser::mouseDoubleClickEvent(QMouseEvent *e)
{
//    Q_UNUSED(e);
    setReadOnly(false);
    QTextBrowser::mouseDoubleClickEvent(e);
}

chat::MessagePtr ChatMessageTextBrowser::msgPtr() const
{
    return _msgPtr;
}

void ChatMessageTextBrowser::setMsgPtr(chat::MessagePtr newMsgPtr)
{
    _msgPtr = newMsgPtr;
}
