/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

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

        if (e->reason() != Qt::PopupFocusReason) {
            setReadOnly(true);
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
