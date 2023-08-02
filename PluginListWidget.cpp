#include "PluginListWidget.h"
#include "ui_PluginListWidget.h"

#include "plg_source/IRootObject.h"

#include "PluginDialog.h"

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
        QMap<QString, QString> mp = mapPluginValues(selectionModel);

        QString destinationDir("plg");
        QString filePath = destinationDir + QDir::separator() + mp.value("file");

        plg::Info plgInfo;
        plgInfo.setName(mp.value("name"));
        plgInfo.setDesc(mp.value("desc"));
        plgInfo.setAuthor(mp.value("author"));
        plgInfo.setVersion(plg::Version(mp.value("version")));

        qDebug() << "Plugin:" << filePath << mp.value("name") << mp.value("desc") << mp.value("author") << mp.value("version");

        emit openPlugin(filePath, plgInfo);

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
        plg::Info info = rootObject->pluginInfo();
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

QMap<QString, int> PluginListWidget::mapHeaderNames(const QAbstractItemModel *mdl) const
{
    QMap<QString, int> mp;
    int count = mdl->columnCount();

    for (int i = 0; i < count; i++) {
        QString hdr = mdl->headerData(i, Qt::Horizontal).toString();
        mp.insert(hdr, i);
    }

    return mp;
}

QMap<QString, QString> PluginListWidget::mapPluginValues(const QItemSelectionModel *selectionModel) const
{
    QMap<QString, QString> retMap;

    auto mdl = selectionModel->model();
    QMap<QString, int> mp = mapHeaderNames(mdl);

    auto headerNames = mp.keys();

    for (auto &key : headerNames) {
        auto valueList = selectionModel->selectedRows(mp.value(key));
        auto value = valueList.first().data().toString();

        retMap.insert(key, value);
    }

    return retMap;
}

void PluginListWidget::on_tableView_doubleClicked(const QModelIndex &index)
{
    auto model = index.model();


    QMap<QString, int> mp = mapHeaderNames(model);

    QModelIndex fileIndex = model->index(index.row(), mp.value("file"));
    auto file = model->data(fileIndex).toString();

    QModelIndex nameIndex = model->index(index.row(), mp.value("name"));
    auto name = model->data(nameIndex).toString();

    QModelIndex descIndex = model->index(index.row(), mp.value("desc"));
    auto desc = model->data(descIndex).toString();

    QModelIndex authorIndex = model->index(index.row(), mp.value("author"));
    auto author = model->data(authorIndex).toString();

    QModelIndex versionIndex = model->index(index.row(), mp.value("version"));
    auto version = model->data(versionIndex).toString();

    QString destinationDir("plg");
    QString filePath = destinationDir + QDir::separator() + file;

    PluginDialog dlg;

    dlg.setFileName(filePath);

    // TODO: set plg::Info

    dlg.exec(); // TODO: if
}

