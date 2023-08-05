/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

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
