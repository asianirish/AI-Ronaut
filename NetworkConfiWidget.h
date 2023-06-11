#ifndef NETWORKCONFIWIDGET_H
#define NETWORKCONFIWIDGET_H

#include "NetworkContext.h"

#include <QWidget>

namespace Ui {
class NetworkConfiWidget;
}

class NetworkConfiWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NetworkConfiWidget(QWidget *parent = nullptr);
    ~NetworkConfiWidget();

    NetworkContext context() const;
    void setContext(const NetworkContext &newContext);

private slots:
    void on_timeOutBox_valueChanged(int timeoutSec);

    void on_applyButton_clicked();

    void on_useProxyBox_stateChanged(int isProxy);

private:
    Ui::NetworkConfiWidget *ui;

    NetworkContext _context;
};

#endif // NETWORKCONFIWIDGET_H
