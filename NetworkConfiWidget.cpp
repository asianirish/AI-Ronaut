#include "NetworkConfiWidget.h"
#include "ui_NetworkConfiWidget.h"

#include <Component.h>

#include <QSettings>

NetworkConfiWidget::NetworkConfiWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetworkConfiWidget)
{
    ui->setupUi(this);

    on_useProxyBox_stateChanged(false);
    ui->apiUrlEdit->setText(oaic::Component::DEFAULT_URL);
}

NetworkConfiWidget::~NetworkConfiWidget()
{
    delete ui;
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

    _context.setTimeout(timeoutMs);

    QSettings settings;
    settings.setValue("oai/timeout", timeoutMs);

    ui->applyButton->setEnabled(false);
}


void NetworkConfiWidget::on_useProxyBox_stateChanged(int isProxy)
{
    ui->httpEdit->setEnabled(isProxy);
    ui->httpPortEdit->setEnabled(isProxy);
    ui->httpsEdit->setEnabled(isProxy);
    ui->httpsPortEdit->setEnabled(isProxy);

    if (isProxy) {
        ui->httpEdit->setFocus();
    }

    ui->applyButton->setEnabled(true);
}

NetworkContext NetworkConfiWidget::context() const
{
    return _context;
}

void NetworkConfiWidget::setContext(const NetworkContext &newContext)
{
    _context = newContext;
    int timeOutSec = _context.timeout() / 1000;
    ui->timeOutBox->setValue(timeOutSec);
}


void NetworkConfiWidget::on_apiUrlEdit_textEdited(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->applyButton->setEnabled(true);
}

