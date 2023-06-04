#ifndef SYSTEMMESSAGEWIDGET_H
#define SYSTEMMESSAGEWIDGET_H

#include "ChatToolWidget.h"

namespace Ui {
class SystemMessageWidget;
}

class SystemMessageWidget : public ChatToolWidget
{
    Q_OBJECT

public:
    explicit SystemMessageWidget(QWidget *parent = nullptr);
    ~SystemMessageWidget();

    QString systemMessage() const;

protected:
    void updateCurrentSession(const QString &sessionId) override;

protected:
    void showEvent(QShowEvent *event) override;

private:
    Ui::SystemMessageWidget *ui;
};

#endif // SYSTEMMESSAGEWIDGET_H
