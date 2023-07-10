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
