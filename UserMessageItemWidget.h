#ifndef USERMESSAGEITEMWIDGET_H
#define USERMESSAGEITEMWIDGET_H

#include "ChatItemWidget.h"

#include <QTextBrowser>

namespace Ui {
class UserMessageItemWidget;
}

class UserMessageItemWidget : public ChatItemWidget
{
    Q_OBJECT

public:
    explicit UserMessageItemWidget(QWidget *parent = nullptr);
    ~UserMessageItemWidget();

protected:
    QTextBrowser *textBrowser() const override;
    int extraSpaceHeight() const override;

private slots:
    void on_actionCopy_triggered();

private:
    Ui::UserMessageItemWidget *ui;

};

#endif // USERMESSAGEITEMWIDGET_H
