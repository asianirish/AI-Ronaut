#include "MainWindow.h"
#include "PageImagePage.h"
#include "PageGeneralChatPage.h"
#include "PageDonatePage.h"
#include "PageAboutPage.h"
#include "PagePlotPage.h"

#include "NetworkConfiWidget.h"

#include "ui_MainWindow.h"

#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto mainPage = ui->tabWidget->widget(0);
    auto welcomePage = qobject_cast<PageWelcomePage *>(mainPage);

    welcomePage->setClient(&_client); // checks the env key
    
    connect(welcomePage, &PageWelcomePage::openImageAction, this, &MainWindow::onOpenImage);
    connect(welcomePage, &PageWelcomePage::openChatAction, this, &MainWindow::onOpenChat);
    connect(welcomePage, &PageWelcomePage::openDonateAction, this, &MainWindow::onOpenDonate);
    connect(welcomePage, &PageWelcomePage::openAboutAction, this, &MainWindow::onOpenAbout);
    connect(welcomePage, &PageWelcomePage::openPlotAction, this, &MainWindow::onOpenPlot);
    connect(welcomePage, &PageWelcomePage::openNetworkConfigAction, this, &MainWindow::onOpenNetworkConfig);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOpenImage()
{
    auto mainPage = ui->tabWidget->widget(0);
    auto welcomePage = qobject_cast<PageWelcomePage *>(mainPage);
    
    PageWidget *imagePage = new PageImagePage(this);
    imagePage->setCntx(welcomePage->cntx());

    int index = ui->tabWidget->addTab(imagePage, tr("Image"));
    ui->tabWidget->setCurrentIndex(index);

    // TODO: delete the code above
    imagePage->setClient(&_client); // connect the client here
}

void MainWindow::onOpenChat()
{
    auto mainPage = ui->tabWidget->widget(0);
    auto page = qobject_cast<PageWelcomePage *>(mainPage);

    PageWidget *specificPage = new PageGeneralChatPage(this);
    specificPage->setCntx(page->cntx());

    int index = ui->tabWidget->addTab(specificPage, tr("Chat"));
    ui->tabWidget->setCurrentIndex(index);
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
    auto mainPage = ui->tabWidget->widget(0);
    auto page = qobject_cast<PageWelcomePage *>(mainPage);

    PageWidget *specificPage = new PagePlotPage(this);
    specificPage->setCntx(page->cntx());

    int index = ui->tabWidget->addTab(specificPage, tr("Plot"));
    ui->tabWidget->setCurrentIndex(index);
}

void MainWindow::onOpenNetworkConfig()
{
    auto mainPage = ui->tabWidget->widget(0);
    auto page = qobject_cast<PageWelcomePage *>(mainPage);

    NetworkConfiWidget *wdt = new NetworkConfiWidget(this);
    wdt->updateCntx(page->cntx());

    int index = ui->tabWidget->addTab(wdt, tr("Network Config"));
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

