#include "PluginDialog.h"
#include "ui_PluginDialog.h"

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
