#include "PluginListWidget.h"
#include "ui_PluginListWidget.h"

#include <QFileDialog>

#include <QCryptographicHash>
#include <QSqlQuery>
#include <QSqlError>

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

    ui->listView->setModel(_model);
    ui->listView->setModelColumn(1);

    _model->select();

//    _model->setEditStrategy(QSqlTableModel::OnFieldChange);

//    connect(_model, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), ui->listView, SLOT(update()));
}

PluginListWidget::~PluginListWidget()
{
    delete ui;
}

void PluginListWidget::on_openPluginButton_clicked()
{
//    qDebug() << "CURRENT PATH:" << QCoreApplication::applicationDirPath();

//#ifdef Q_OS_WIN
//    QPluginLoader pluginLoader("plg/ExamplePlugin.dll");
//#elif defined(Q_OS_LINUX)
//    QPluginLoader pluginLoader("plg/ExamplePlugin.so");
//#endif

//    QObject *plugin = pluginLoader.instance();

//    IRootObject* rootObject = qobject_cast<IRootObject *>(plugin);

//    if (rootObject) {
//        rootObject->doIt();
//    }
    emit openExamplePlugin();
}


void PluginListWidget::on_registerPluginButton_clicked()
{
    QDir dir;

//    destinationPath.append(QDir::separator()).append(filename);
    QString destinationDir("plg");

    if (!dir.exists(destinationDir)) {
        dir.mkpath(destinationDir);
    }

    // TODO: .so
    auto filePath = QFileDialog::getOpenFileName(this, tr("Register a plugin file..."),
                                                QString(), tr("DLLs: (*.dll)"));

    if (filePath.isNull()) {
        return;
    }

    QFileInfo fileInfo(filePath);
    QString fileName = fileInfo.fileName();

    QByteArray hash = calculateFileHash(filePath, QCryptographicHash::Md5);
    qDebug() << "HASH:" << hash.toHex();

    QSqlQuery query;

    // TODO: insert or update
    QString queryString("INSERT OR REPLACE INTO plugins ('name', 'author', 'hash') "
                        "VALUES(:name, "
                        "'asianirish@gmail.com', " // TODO: from the resources?
                        ":hash)");

    query.prepare(queryString);

    query.bindValue(":name", fileName);
    query.bindValue(":hash", hash);

    QSqlDatabase db = QSqlDatabase::database();

    if (!query.exec()) {
        qDebug() << "error creating a plugin:" << query.lastError().text();
        return;
    }

    // and copy the file
    QString destFilePath = destinationDir + QDir::separator() + fileName;

    qDebug() << "destFilePath" << destFilePath;

    bool success = QFile::copy(filePath, destFilePath);
    if (!success)
    {
        qDebug() << "FILE COPYING ERROR";
        db.rollback();
        return;
    }

    db.commit();


    _model->select();
}

