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
