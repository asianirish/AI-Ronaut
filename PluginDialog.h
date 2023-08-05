/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef PLUGINDIALOG_H
#define PLUGINDIALOG_H

#include "plg/Info.h"

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
