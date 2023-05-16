#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
