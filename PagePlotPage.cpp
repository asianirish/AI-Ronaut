#include "PagePlotPage.h"
#include "ui_PagePlotPage.h"

PagePlotPage::PagePlotPage(QWidget *parent) :
    PageWidget(parent),
    ui(new Ui::PagePlotPage)
{
    ui->setupUi(this);
}

PagePlotPage::~PagePlotPage()
{
    delete ui;
}

void PagePlotPage::updateCntx(AppContext *cntx)
{
    Q_UNUSED(cntx)
    // TODO: do nothing?
}

void PagePlotPage::updateClient(oaic::Manager *_client)
{
    Q_UNUSED(_client)
    // TODO: do nothing?
}
