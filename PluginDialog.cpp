#include "PluginDialog.h"
#include "ui_PluginDialog.h"

#include <QFileInfo>

PluginDialog::PluginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginDialog)
{
    ui->setupUi(this);
}

PluginDialog::~PluginDialog()
{
    delete ui;
}

plg::Info PluginDialog::pluginInfo() const
{
    return _pluginInfo;
}

void PluginDialog::setPluginInfo(const plg::Info &newPluginInfo)
{
    _pluginInfo = newPluginInfo;

    ui->nameEdit->setText(_pluginInfo.name());
    ui->descTextEdit->setPlainText(_pluginInfo.desc());
    ui->authorEdit->setText(_pluginInfo.author());
    ui->versionEdit->setText(_pluginInfo.version());
}

QString PluginDialog::fileName() const
{
    return _fileName;
}

void PluginDialog::setFileName(const QString &newFileName)
{
    _fileName = newFileName;

    QFileInfo info(_fileName);

    auto absPath = info.absoluteFilePath();

    qDebug() << "PATH:" << absPath;

    ui->fileEdit->setText(absPath);
}
