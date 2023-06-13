#ifndef SYSTEMMESSAGEWIDGET_H
#define SYSTEMMESSAGEWIDGET_H

#include "ChatToolWidget.h"

#include "SqlQueryModelExt.h"

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
    void synchronizeCurrentSession(const QString &sessionId) override;

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void on_roleBox_currentIndexChanged(int index);

    void on_saveRoleButton_clicked();

private:
    Ui::SystemMessageWidget *ui;
    SqlQueryModelExt *_model; // TODO: Custom model

    void initRoleList();
};

#endif // SYSTEMMESSAGEWIDGET_H
