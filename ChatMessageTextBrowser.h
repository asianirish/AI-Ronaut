/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef CHATMESSAGETEXTBROWSER_H
#define CHATMESSAGETEXTBROWSER_H

#include "chat/Message.h"

#include <QTextBrowser>
#include <QObject>

class ChatMessageTextBrowser : public QTextBrowser
{
    Q_OBJECT
public:
    ChatMessageTextBrowser(QWidget* parent = nullptr);

    chat::MessagePtr msgPtr() const;
    void setMsgPtr(chat::MessagePtr newMsgPtr);

protected:
    void focusOutEvent(QFocusEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;

    void contextMenuEvent(QContextMenuEvent *e) override;

private:
    chat::MessagePtr _msgPtr;
signals:
    void readMyTextRequest(const QString &text);

private slots:
    void onSelectionChanged();
};

#endif // CHATMESSAGETEXTBROWSER_H
