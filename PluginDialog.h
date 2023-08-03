#ifndef PLUGINDIALOG_H
#define PLUGINDIALOG_H

#include "plg_source/Info.h"

#include <QDialog>

namespace Ui {
class PluginDialog;
}

class PluginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PluginDialog(QWidget *parent = nullptr);
    ~PluginDialog();

    plg::Info pluginInfo() const;
    void setPluginInfo(const plg::Info &newPluginInfo);

    QString fileName() const;
    void setFileName(const QString &newFileName);

private:
    Ui::PluginDialog *ui;
    plg::Info _pluginInfo;
    QString _fileName;
};

#endif // PLUGINDIALOG_H
