#include "PluginListWidget.h"
#include "ui_PluginListWidget.h"

#include "plg_source/IRootObject.h"

#include <QFileDialog>

#include <QCryptographicHash>
#include <QSqlQuery>
#include <QSqlError>

#include <QMessageBox>

#include <QPluginLoader>

QByteArray calculateFileHash(const QString& filePath, QCryptographicHash::Algorithm hashAlgorithm)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to open file" << filePath;
        return QByteArray();
    }

    QCryptographicHash hash(hashAlgorithm);
    if (hash.addData(&file))
    {
        return hash.result();
    }
    else
    {
        qDebug() << "Failed to calculate hash";
        return QByteArray();
    }
}

PluginListWidget::PluginListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PluginListWidget)
{
    ui->setupUi(this);

    _model = new QSqlTableModel(this);
    _model->setTable("plugins");

    ui->tableView->setModel(_model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setColumnHidden(6, true);

    _model->select();
    resizeToContent();

//    _model->setEditStrategy(QSqlTableModel::OnFieldChange);

//    connect(_model, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), ui->listView, SLOT(update()));
}

PluginListWidget::~PluginListWidget()
{
    delete ui;
}

void PluginListWidget::on_openPluginButton_clicked()
{
    auto selectionModel = ui->tableView->selectionModel();

    if (selectionModel->hasSelection()) {
        auto rowList = selectionModel->selectedRows(1);

        auto firstIndex = rowList.first();

        auto pluginName = firstIndex.data().toString();

        qDebug() << "Plugin name:" << pluginName;

        // TODO: emit openPluginName(pluginName);
        emit openExamplePlugin();
    } else {
        QMessageBox::information(this, tr("Plugins"), tr("Please, select a plugin"));
    }




}


void PluginListWidget::on_registerPluginButton_clicked()
{
    QDir dir;

//    destinationPath.append(QDir::separator()).append(filename);
    QString destinationDir("plg");

    if (!dir.exists(destinationDir)) {
        dir.mkpath(destinationDir);
    }

#ifdef Q_OS_WIN
    auto filePath = QFileDialog::getOpenFileName(this, tr("Register a plugin file..."),
                                                QString(), tr("DLLs: (*.dll)"));
#elif defined(Q_OS_LINUX)
    auto filePath = QFileDialog::getOpenFileName(this, tr("Register a plugin file..."),
                                                 QString(), tr("DLLs: (*.so)"));
#endif

    if (filePath.isNull()) {
        return;
    }

    QFileInfo fileInfo(filePath);
    QString fileName = fileInfo.fileName();

    QByteArray hash = calculateFileHash(filePath, QCryptographicHash::Md5);
    qDebug() << "HASH:" << hash.toHex();

    // TODO: check online
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, tr("Plugin"),
                                  tr("Registering this plugin can be potentially dangerouss.\n\n"
                                    "Ensure that you have received the file from a reliable source "
                                    "or compiled it from verified source codes.\n\n"
                                    "Continue?"),
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply != QMessageBox::Yes) {
        return;
    }

    auto info = loadPluginInfo(filePath);

    QSqlQuery query;

    // TODO: insert or update
    QString queryString("INSERT OR REPLACE INTO plugins ('file', 'name', 'desc', 'author', 'version', 'hash') "
                        "VALUES(:file, "
                        ":name, "
                        ":desc, "
                        ":author, "
                        ":version, "
                        ":hash)");

    query.prepare(queryString);

    query.bindValue(":file", fileName);

    query.bindValue(":name", info.name());
    query.bindValue(":desc", info.desc());
    query.bindValue(":author", info.author());
    query.bindValue(":version", info.version().toString());

    query.bindValue(":hash", hash);

    // TODO: read the author

    QSqlDatabase db = QSqlDatabase::database();

    if (!query.exec()) {
        qDebug() << "error creating a plugin:" << query.lastError().text();
        return;
    }

    // and copy the file
    QString destFilePath = destinationDir + QDir::separator() + fileName;

    qDebug() << "destFilePath" << destFilePath;

    if (QFile::exists(destFilePath)) {
        if (!QFile::remove(destFilePath)) {
            qDebug() << "FILE REMOVING ERROR";
            db.rollback();
            return;
        }
    }

    bool success = QFile::copy(filePath, destFilePath);
    if (!success)
    {
        qDebug() << "FILE COPYING ERROR";
        db.rollback();
        return;
    }

    db.commit();

    _model->select();
    resizeToContent();
}


void PluginListWidget::on_unregisterPluginButton_clicked()
{
    // TODO: implement
}

plg::Info PluginListWidget::loadPluginInfo(const QString &filePath)
{
#ifdef Q_OS_WIN
    QPluginLoader pluginLoader(filePath);
#elif defined(Q_OS_LINUX)
    QPluginLoader pluginLoader(filePath);
#endif

    QObject *plugin = pluginLoader.instance();

    IRootObject* rootObject = qobject_cast<IRootObject *>(plugin);

    if (rootObject) {
        auto info = rootObject->pluginInfo();
        qDebug() << "INFO:" << info.name() << info.desc() << info.author() << info.version();
        return info;
    }

    return plg::Info();
}

void PluginListWidget::resizeToContent()
{
    ui->tableView->resizeColumnToContents(1);
    ui->tableView->resizeColumnToContents(2);
    ui->tableView->resizeColumnToContents(4);
    ui->tableView->resizeColumnToContents(5);
}

