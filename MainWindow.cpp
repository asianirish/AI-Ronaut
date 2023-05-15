#include "MainWindow.h"
#include "PageImagePage.h"
#include "PageGeneralChatPage.h"
#include "PageDonatePage.h"
#include "PageAboutPage.h"

#include "ui_MainWindow.h"

#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto mainPage = ui->tabWidget->widget(0);
    auto welcomePage = qobject_cast<PageWelcomePage *>(mainPage);
    
    connect(welcomePage, &PageWelcomePage::openImageAction, this, &MainWindow::onOpenImage);
    connect(welcomePage, &PageWelcomePage::openChatAction, this, &MainWindow::onOpenChat);
    connect(welcomePage, &PageWelcomePage::openDonateAction, this, &MainWindow::onOpenDonate);
    connect(welcomePage, &PageWelcomePage::openAboutAction, this, &MainWindow::onOpenAbout);
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

    int index = ui->tabWidget->addTab(imagePage, "Image");
    ui->tabWidget->setCurrentIndex(index);
}

void MainWindow::onOpenChat()
{
    auto mainPage = ui->tabWidget->widget(0);
    auto page = qobject_cast<PageWelcomePage *>(mainPage);

    PageWidget *specificPage = new PageGeneralChatPage(this);
    specificPage->setCntx(page->cntx());

    int index = ui->tabWidget->addTab(specificPage, "Chat");
    ui->tabWidget->setCurrentIndex(index);
}

void MainWindow::onOpenDonate()
{
    QWidget *donateWidget = new PageDonatePage(this);

    int index = ui->tabWidget->addTab(donateWidget, "Donate");
    ui->tabWidget->setCurrentIndex(index);
}

void MainWindow::onOpenAbout()
{
    QWidget *wdt = new PageAboutPage(this);

    int index = ui->tabWidget->addTab(wdt, "About");
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

