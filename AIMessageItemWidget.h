#ifndef AIMESSAGEITEMWIDGET_H
#define AIMESSAGEITEMWIDGET_H

#include "ChatSessionItemWidget.h"

namespace Ui {
class AIMessageItemWidget;
}

class AIMessageItemWidget : public ChatSessionItemWidget
{
    Q_OBJECT

public:
    explicit AIMessageItemWidget(QWidget *parent = nullptr);
    ~AIMessageItemWidget();

    void appendText(const QString &deltaText);

protected:
    QTextBrowser *textBrowser() const override;
    int extraSpaceHeight() const override;

private slots:
    void on_actionCopy_triggered();

    void on_actionEdit_triggered();

private:
    Ui::AIMessageItemWidget *ui;
};

#endif // AIMESSAGEITEMWIDGET_H
