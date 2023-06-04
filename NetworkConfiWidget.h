#ifndef NETWORKCONFIWIDGET_H
#define NETWORKCONFIWIDGET_H

#include <Manager.h>

#include <QWidget>

namespace Ui {
class NetworkConfiWidget;
}

class AppContext;


// TODO: rename to page and inherit from PageWidget
class NetworkConfiWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NetworkConfiWidget(QWidget *parent = nullptr);
    ~NetworkConfiWidget();

    void synchronizeClient(oaic::Manager *client);

private slots:
    void on_timeOutBox_valueChanged(int timeoutSec);

    void on_applyButton_clicked();

    void on_useProxyBox_stateChanged(int isProxy);

private:
    Ui::NetworkConfiWidget *ui;
    oaic::Manager *_client;
};

#endif // NETWORKCONFIWIDGET_H
