#ifndef PLUGINLISTWIDGET_H
#define PLUGINLISTWIDGET_H

#include "plg_source/Info.h"

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class PluginListWidget;
}

class PluginListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PluginListWidget(QWidget *parent = nullptr);
    ~PluginListWidget();

signals:
    void openExamplePlugin();

private slots:
    void on_openPluginButton_clicked();

    void on_registerPluginButton_clicked();

    void on_unregisterPluginButton_clicked();

private:
    Ui::PluginListWidget *ui;

    QSqlTableModel *_model;

private:
    plg::Info loadPluginInfo(const QString &filePath);
    void resizeToContent();
};

#endif // PLUGINLISTWIDGET_H
