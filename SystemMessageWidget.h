#ifndef SYSTEMMESSAGEWIDGET_H
#define SYSTEMMESSAGEWIDGET_H

#include <QWidget>

namespace Ui {
class SystemMessageWidget;
}

class SystemMessageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SystemMessageWidget(QWidget *parent = nullptr);
    ~SystemMessageWidget();

protected:
    void showEvent(QShowEvent *event) override;

private:
    Ui::SystemMessageWidget *ui;
};

#endif // SYSTEMMESSAGEWIDGET_H
