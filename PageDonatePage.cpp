#include "PageDonatePage.h"
#include "ui_PageDonatePage.h"

#include <QClipboard>
#include <QGuiApplication>

PageDonatePage::PageDonatePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageDonatePage)
{
    ui->setupUi(this);

    ui->clipComboBox->addItem(tr("EUR IBAN"), QString("PL 15 1050 1793 1000 0097 4489 2788"));
    ui->clipComboBox->addItem(tr("USD IBAN"), QString("PL 47 1050 1793 1000 0097 5843 2927"));
    ui->clipComboBox->addItem(tr("PLN IBAN"), QString("PL 36 1050 1793 1000 0091 3841 5139"));
    ui->clipComboBox->addItem(tr("PLN Bank Account (from Poland)"), QString("36 1050 1793 1000 0091 3841 5139"));

    ui->clipComboBox->addItem(tr("BIC SWIFT"), QString("INGBPLPW"));
    ui->clipComboBox->addItem(tr("Authorised Person"), QString("RISHAT BEKMUKHAMEDOV"));

    ui->clipComboBox->addItem(tr("ETH Wallet"), QString("0xC318401Feb332A2d906e19Bc2E20A0d3661c5250"));
    ui->clipComboBox->addItem(tr("BTC Wallet"), QString("bc1ql9f70c5ujukus24nzfrvpy29lz67urc80m7fp4"));
    ui->clipComboBox->addItem(tr("XX Wallet"), QString("6WaZ4Mt7gVj5MxQ9gZEHDpyJ5Yp11SUWhHt77T3YuF8vbZyy"));
    ui->clipComboBox->addItem(tr("QRL Wallet"), QString("Q0105006c4cf1793f416e1858d607bcfb28b8b161b46d08da94c4d1eb3d151d3ddd5a8a13909d87"));

}

PageDonatePage::~PageDonatePage()
{
    delete ui;
}

void PageDonatePage::on_copyButton_clicked()
{
    QString data = ui->clipComboBox->currentData().toString();
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(data);
}


void PageDonatePage::on_clipComboBox_currentIndexChanged(int index)
{
    Q_UNUSED(index)
    on_copyButton_clicked();
}

