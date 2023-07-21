#include "ExamplePluginPageWidget.h"
#include "ui_ExamplePluginPageWidget.h"

ExamplePluginPageWidget::ExamplePluginPageWidget(QWidget *parent) :
    PageWidget(parent),
    ui(new Ui::ExamplePluginPageWidget)
{
    ui->setupUi(this);
}

ExamplePluginPageWidget::~ExamplePluginPageWidget()
{
    delete ui;
}

void ExamplePluginPageWidget::synchronizeClient(oaic::Manager *client)
{
    Q_UNUSED(client)
    // DO NOTHING
}
