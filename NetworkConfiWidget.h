#ifndef NETWORKCONFIWIDGET_H
#define NETWORKCONFIWIDGET_H

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

    void updateCntx(AppContext *cntx);

private slots:
    void on_timeOutBox_valueChanged(int timeoutSec);

    void on_applyButton_clicked();

    void on_useProxyBox_stateChanged(int isProxy);

private:
    Ui::NetworkConfiWidget *ui;
    AppContext *_cntx;
};

#endif // NETWORKCONFIWIDGET_H
