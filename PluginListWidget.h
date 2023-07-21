#ifndef PLUGINLISTWIDGET_H
#define PLUGINLISTWIDGET_H

#include <QWidget>

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

private:
    Ui::PluginListWidget *ui;
};

#endif // PLUGINLISTWIDGET_H
