#ifndef AIMESSAGEITEMWIDGET_H
#define AIMESSAGEITEMWIDGET_H

#include "ChatItemWidget.h"

namespace Ui {
class AIMessageItemWidget;
}

class AIMessageItemWidget : public ChatItemWidget
{
    Q_OBJECT

public:
    explicit AIMessageItemWidget(QWidget *parent = nullptr);
    ~AIMessageItemWidget();

    void appendText(const QString &deltaText);

protected:
    QTextBrowser *textBrowser() const override;
    int extraSpaceHeight() const override;

private:
    Ui::AIMessageItemWidget *ui;
};

#endif // AIMESSAGEITEMWIDGET_H
