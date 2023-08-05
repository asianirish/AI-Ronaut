/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#include "MainWindow.h"
#include "PageImagePage.h"
#include "PageGeneralChatPage.h"
#include "PageDonatePage.h"
#include "PageAboutPage.h"
#include "PagePlotPage.h"

#include "NetworkConfiWidget.h"

#include "plg/IRootObject.h"

#include "ui_MainWindow.h"

#include <QMessageBox>
#include <QGenericPlugin>
#include <QPluginLoader>
#include <QDir>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto mainPage = ui->tabWidget->widget(0);
    auto welcomePage = qobject_cast<PageWelcomePage *>(mainPage);

    welcomePage->initClient(); // checks the env key
    
    connect(welcomePage, &PageWelcomePage::openImageAction, this, &MainWindow::onOpenImage);
    connect(welcomePage, &PageWelcomePage::openChatAction, this, &MainWindow::onOpenChat);
    connect(welcomePage, &PageWelcomePage::openDonateAction, this, &MainWindow::onOpenDonate);
    connect(welcomePage, &PageWelcomePage::openAboutAction, this, &MainWindow::onOpenAbout);
    connect(welcomePage, &PageWelcomePage::openPlotAction, this, &MainWindow::onOpenPlot);
//    connect(welcomePage, &PageWelcomePage::openNetworkConfigAction, this, &MainWindow::onOpenNetworkConfig);

    connect(welcomePage, &PageWelcomePage::openPluginAction, this, &MainWindow::onOpenPlugin);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOpenImage()
{ 
    PageWidget *imagePage = new PageImagePage(this);

    int index = ui->tabWidget->addTab(imagePage, tr("Image"));
    ui->tabWidget->setCurrentIndex(index);

    imagePage->initClient(); // connect the client here
}

void MainWindow::onOpenChat()
{
    PageWidget *specificPage = new PageGeneralChatPage(this);

    int index = ui->tabWidget->addTab(specificPage, tr("Chat"));
    ui->tabWidget->setCurrentIndex(index);

    specificPage->initClient(); // connect the client here
}

void MainWindow::onOpenDonate()
{
    QWidget *donateWidget = new PageDonatePage(this);

    int index = ui->tabWidget->addTab(donateWidget, tr("Donate"));
    ui->tabWidget->setCurrentIndex(index);
}

void MainWindow::onOpenAbout()
{
    QWidget *wdt = new PageAboutPage(this);

    int index = ui->tabWidget->addTab(wdt, tr("About"));
    ui->tabWidget->setCurrentIndex(index);
}

void MainWindow::onOpenPlot()
{
    PageWidget *specificPage = new PagePlotPage(this);

    int index = ui->tabWidget->addTab(specificPage, tr("Plot"));
    ui->tabWidget->setCurrentIndex(index);
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    auto wdt = ui->tabWidget->widget(index);
    auto welcomeWidget = qobject_cast<PageWelcomePage *>(wdt);

    if (welcomeWidget == nullptr) {
        ui->tabWidget->removeTab(index);
    }
}

void MainWindow::onOpenPlugin(const QString &filePath, const plg::Info &plgInfo)
{
#ifdef Q_OS_WIN
    QPluginLoader pluginLoader(filePath);
#elif defined(Q_OS_LINUX)
    QPluginLoader pluginLoader(filePath);
#endif

    QObject *plugin = pluginLoader.instance();

    IRootObject* rootObject = qobject_cast<IRootObject *>(plugin);

    if (rootObject) {
        //        rootObject->doIt();
        auto specificPage = rootObject->createPageWidget(this);
        int index = ui->tabWidget->addTab(specificPage, plgInfo.name() + " v" + plgInfo.version());
        ui->tabWidget->setCurrentIndex(index);
    }
}

