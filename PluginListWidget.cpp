#include "PluginListWidget.h"
#include "ui_PluginListWidget.h"

PluginListWidget::PluginListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PluginListWidget)
{
    ui->setupUi(this);
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

