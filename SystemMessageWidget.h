/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef SYSTEMMESSAGEWIDGET_H
#define SYSTEMMESSAGEWIDGET_H

#include "ChatToolWidget.h"

#include "chat/Character.h"

namespace Ui {
class SystemMessageWidget;
}

class SystemMessageWidget : public ChatToolWidget
{
    Q_OBJECT

public:
    explicit SystemMessageWidget(QWidget *parent = nullptr);
    ~SystemMessageWidget();
    
    chat::Character character() const;

protected:
    void synchronizeCurrentSession() override;
    void onSessionCreatedSpecific(int pageIndex, const QString &newSessionId) override;

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void on_characterBox_currentIndexChanged(int index);

    void on_saveCharacterButton_clicked();

    void on_deleteCharacterButton_clicked();

    void on_clearButton_clicked();

private:
    Ui::SystemMessageWidget *ui;

    void initCharacterList(int selectCharacter = 0);
};

#endif // SYSTEMMESSAGEWIDGET_H
