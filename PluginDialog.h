#ifndef PLUGINDIALOG_H
#define PLUGINDIALOG_H

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

    QString fileName() const;
    void setFileName(const QString &newFileName);
private:
    Ui::PluginDialog *ui;
    QString _fileName;
};

#endif // PLUGINDIALOG_H
