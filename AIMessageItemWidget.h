/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

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
    explicit AIMessageItemWidget(const QString &sessionId, chat::MessagePtr msgPtr = {}, QWidget *parent = nullptr);
    ~AIMessageItemWidget();

    void appendText(const QString &deltaText);

protected:
    QTextBrowser *textBrowser() const override;
    int extraSpaceHeight() const override;

    chat::Message *createMessage() const override;

private slots:
    void on_actionCopy_triggered();

    void on_actionEdit_triggered();

    void on_textBrowser_textChanged();

    void on_actionDelete_triggered();

private:
    Ui::AIMessageItemWidget *ui;

    bool _isProgramInput;
};

#endif // AIMESSAGEITEMWIDGET_H
