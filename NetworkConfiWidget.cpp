#include "NetworkConfiWidget.h"
#include "ui_NetworkConfiWidget.h"

#include "AppContext.h"

#include <QSettings>

NetworkConfiWidget::NetworkConfiWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetworkConfiWidget),
    _cntx(nullptr)
{
    ui->setupUi(this);
}

NetworkConfiWidget::~NetworkConfiWidget()
{
    delete ui;
}

void NetworkConfiWidget::updateCntx(AppContext *cntx)
{
    _cntx = cntx;
    int32_t timeOutSec = _cntx->timeOutMs() / 1000;
    ui->timeOutBox->setValue(timeOutSec);
}

void NetworkConfiWidget::on_timeOutBox_valueChanged(int timeoutSec)
{
    Q_UNUSED(timeoutSec)
    ui->applyButton->setEnabled(true);
}


void NetworkConfiWidget::on_applyButton_clicked()
{
    int32_t timeoutSec = ui->timeOutBox->value();
    int32_t timeoutMs = timeoutSec * 1000;

    _cntx->setTimeOutMs(timeoutMs);

    QSettings settings;
    settings.setValue("oai/timeout", timeoutMs);

    ui->applyButton->setEnabled(false);
}

