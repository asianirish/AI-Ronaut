#ifndef USERMESSAGEITEMWIDGET_H
#define USERMESSAGEITEMWIDGET_H

#include "ChatSessionItemWidget.h"

#include <QTextBrowser>

namespace Ui {
class UserMessageItemWidget;
}

class UserMessageItemWidget : public ChatSessionItemWidget
{
    Q_OBJECT

public:
    explicit UserMessageItemWidget(const QString &sessionId,QWidget *parent = nullptr);
    ~UserMessageItemWidget();

protected:
    QTextBrowser *textBrowser() const override;
    int extraSpaceHeight() const override;

    chat::Message *createMessage() const override;

private slots:
    void on_actionCopy_triggered();

    void on_actionEdit_triggered();

private:
    Ui::UserMessageItemWidget *ui;

};

#endif // USERMESSAGEITEMWIDGET_H
