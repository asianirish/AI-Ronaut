#ifndef PLUGINLISTWIDGET_H
#define PLUGINLISTWIDGET_H

#include "plg/Info.h"

#include <QWidget>
#include <QSqlTableModel>
#include <QItemSelectionModel>

namespace Ui {
class PluginListWidget;
}

class PluginListWidget : public QWidget
{
    Q_OBJECT
public:
    const QString PLUGIN_DIR{".plg"};

    explicit PluginListWidget(QWidget *parent = nullptr);
    ~PluginListWidget();

signals:
    void openPlugin(const QString &filePath, const plg::Info &plgInfo);

private slots:
    void on_openPluginButton_clicked();

    void on_registerPluginButton_clicked();

    void on_unregisterPluginButton_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_propertiesButton_clicked();

    void on_filterEdit_textChanged(const QString &text);

private:
    Ui::PluginListWidget *ui;

    QSqlTableModel *_model;

private:
    plg::Info loadPluginInfo(const QString &filePath);
    void resizeToContent();

    QMap<QString, int> mapHeaderNames(const QAbstractItemModel *mdl) const;
    QMap<QString, QByteArray> mapPluginValues(const QItemSelectionModel *selectionModel) const;

    bool deleteFromDb(int id);

    bool checkFileHash(const QString &filePath, const QByteArray &hash);

    void displayPluginAuthenticationError();
};

#endif // PLUGINLISTWIDGET_H
