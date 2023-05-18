#ifndef ERRORMESSAGEITEMWIDGET_H
#define ERRORMESSAGEITEMWIDGET_H

#include "ChatItemWidget.h"

#include <QWidget>

namespace Ui {
class ErrorMessageItemWidget;
}

class ErrorMessageItemWidget : public ChatItemWidget
{
    Q_OBJECT

public:
    explicit ErrorMessageItemWidget(QWidget *parent = nullptr);
    ~ErrorMessageItemWidget();

protected:
    QTextBrowser *textBrowser() const override;
    int extraSpaceHeight() const override;

private slots:
    void on_actionCopy_triggered();

private:
    Ui::ErrorMessageItemWidget *ui;
};

#endif // ERRORMESSAGEITEMWIDGET_H
