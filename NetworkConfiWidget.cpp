#include "NetworkConfiWidget.h"
#include "ui_NetworkConfiWidget.h"

#include <QSettings>

NetworkConfiWidget::NetworkConfiWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetworkConfiWidget),
    _client(nullptr)
{
    ui->setupUi(this);
}

NetworkConfiWidget::~NetworkConfiWidget()
{
    delete ui;
}

void NetworkConfiWidget::updateClient(oaic::Manager *client)
{
    _client = client;
    int timeOutSec = _client->timeout() / 1000;
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

    _client->setTimeout(timeoutMs);

    QSettings settings;
    settings.setValue("oai/timeout", timeoutMs);

    ui->applyButton->setEnabled(false);
}


void NetworkConfiWidget::on_useProxyBox_stateChanged(int isProxy)
{
    if (isProxy) {
        ui->proxyFrame->setEnabled(true);
    } else {
        ui->proxyFrame->setEnabled(false);
    }
}

