/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "plg/Info.h"

#include <oaic/Manager.h>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void onOpenImage();
    void onOpenChat();
    void onOpenDonate();
    void onOpenAbout();
    void onOpenPlot();
    void on_tabWidget_tabCloseRequested(int index);

    void onOpenPlugin(const QString &filePath, const plg::Info &plgInfo);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
