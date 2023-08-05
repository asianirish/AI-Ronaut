/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

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

    void on_apiUrlEdit_textEdited(const QString &arg1);

private:
    Ui::NetworkConfiWidget *ui;

    NetworkContext _context;
};

#endif // NETWORKCONFIWIDGET_H
