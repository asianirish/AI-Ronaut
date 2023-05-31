#include "ChatConfigWidget.h"
#include "ui_ChatConfigWidget.h"

#include <QSettings>

using namespace oaic;

ChatConfigWidget::ChatConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatConfigWidget),
    _client(nullptr),
    _modelCntx(nullptr)
{
    ui->setupUi(this);

//    ui->maxTokensLabel->setBuddy(ui->maxTokensSlider); ?
    ui->maxTokensLabel->setText(QString::number(ui->maxTokensSlider->value()));
}

ChatConfigWidget::~ChatConfigWidget()
{
    delete ui;
}

void ChatConfigWidget::updateClient(Manager *client)
{
    _client = client;

    QStringList lst;
// TODO:    _client->modelList(lst);

    ui->modelComboBox->blockSignals(true);
    ui->modelComboBox->addItems(lst); // sets current index to 0
    ui->modelComboBox->model()->sort(0);
    ui->modelComboBox->blockSignals(false);

    QSettings settings;
    auto defaultModel = settings.value("model/default").toString();

    if (defaultModel.isEmpty()) {
        ui->modelComboBox->setCurrentIndex(-1);
    } else {
        ui->modelComboBox->setCurrentText(defaultModel);
    }
}

void ChatConfigWidget::on_modelComboBox_currentTextChanged(const QString &modelName)
{
    int index = ui->modelComboBox->currentIndex();
    if (index < 0) {
        return;
    }

    if (_modelCntx) {
        _modelCntx->setModelName(modelName);
    }

    QSettings settings;
    settings.setValue("model/default", modelName);
}

ModelContext *ChatConfigWidget::modelCntx() const
{
    return _modelCntx;
}

void ChatConfigWidget::setModelCntx(ModelContext *newModelCntx)
{
    _modelCntx = newModelCntx;
}

void ChatConfigWidget::on_maxTokensSlider_sliderMoved(int position)
{
    ui->maxTokensLabel->setText(QString::number(position));
}


void ChatConfigWidget::on_maxTokensSlider_valueChanged(int value)
{
    ui->maxTokensLabel->setText(QString::number(value));
    if (_modelCntx) {
        _modelCntx->setMaxTokens(value);
        qDebug() << "max tokens" << value;
    }
}


void ChatConfigWidget::on_topPSlider_sliderMoved(int position)
{
    double fPosition = (double)position/100.;
    auto strPos = QString::number(fPosition);
    ui->topPLabel->setText(strPos);
}


void ChatConfigWidget::on_topPSlider_valueChanged(int value)
{
    double fPosition = (double)value/100.;
    ui->topPLabel->setText(QString::number(fPosition));
    if (_modelCntx) {
        _modelCntx->setTopP(fPosition);
        qDebug() << "top_p" << fPosition;
    }
}


void ChatConfigWidget::on_frequencyPenaltySlider_sliderMoved(int position)
{
    double fPosition = (double)position/100.;
    auto strPos = QString::number(fPosition);
    qDebug() << "frequency position:" << fPosition << strPos;
    ui->frequencyPenaltyLabel->setText(strPos);
}


void ChatConfigWidget::on_frequencyPenaltySlider_valueChanged(int value)
{
    double fPosition = (double)value/100.;
    ui->frequencyPenaltyLabel->setText(QString::number(fPosition));
    if (_modelCntx) {
        _modelCntx->setFrequencyPenalty(fPosition);
        qDebug() << "frequencyPenalty" << fPosition;
    }
}


void ChatConfigWidget::on_presencePenaltySlider_sliderMoved(int position)
{
    double fPosition = (double)position/100.;
    auto strPos = QString::number(fPosition);
    ui->presencePenaltyLabel->setText(strPos);
}


void ChatConfigWidget::on_presencePenaltySlider_valueChanged(int value)
{
    double fPosition = (double)value/100.;
    ui->presencePenaltyLabel->setText(QString::number(fPosition));
    if (_modelCntx) {
        _modelCntx->setPresencePenalty(fPosition);
        qDebug() << "presencePenalty" << fPosition;
    }
}


void ChatConfigWidget::on_temperatureSlider_sliderMoved(int position)
{
    double fPosition = (double)position/100.;
    auto strPos = QString::number(fPosition);
    ui->temperatureLabel->setText(strPos);
}


void ChatConfigWidget::on_temperatureSlider_valueChanged(int value)
{
    double fPosition = (double)value/100.;
    ui->temperatureLabel->setText(QString::number(fPosition));
    if (_modelCntx) {
        _modelCntx->setTemperature(fPosition);
        qDebug() << "temperature" << fPosition;
    }
}

