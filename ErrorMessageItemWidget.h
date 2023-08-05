/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

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

    void on_actionDelete_triggered();

private:
    Ui::ErrorMessageItemWidget *ui;
};

#endif // ERRORMESSAGEITEMWIDGET_H
