#include "ChatMessageTextBrowser.h"

#include <QFocusEvent>

ChatMessageTextBrowser::ChatMessageTextBrowser(QWidget *parent) : QTextBrowser(parent)
{
    connect(this, &QTextEdit::selectionChanged, this, &ChatMessageTextBrowser::onSelectionChanged);
}

void ChatMessageTextBrowser::focusOutEvent(QFocusEvent *e)
{
    if (!this->isReadOnly()) {

        auto text = this->toPlainText();
        qDebug() << "THE TEXT IS:" << text;

        if (e->reason() != Qt::PopupFocusReason) {
            setReadOnly(true);
            qDebug() << "SET READONLY" << e->reason();
        }

        if (_msgPtr) {
            _msgPtr->setText(text);
        }
    }

    QTextBrowser::focusOutEvent(e);
}

void ChatMessageTextBrowser::mouseDoubleClickEvent(QMouseEvent *e)
{
    setReadOnly(false);
    QTextBrowser::mouseDoubleClickEvent(e);
}

void ChatMessageTextBrowser::contextMenuEvent(QContextMenuEvent *e)
{
    if (textCursor().hasSelection() || !this->isReadOnly())
    {
        QTextBrowser::contextMenuEvent(e);
    }
    else
    {
        e->ignore();
    }
}

void ChatMessageTextBrowser::onSelectionChanged()
{
    setReadOnly(false);
}

chat::MessagePtr ChatMessageTextBrowser::msgPtr() const
{
    return _msgPtr;
}

void ChatMessageTextBrowser::setMsgPtr(chat::MessagePtr newMsgPtr)
{
    _msgPtr = newMsgPtr;
}
