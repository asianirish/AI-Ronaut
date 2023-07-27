#include "ChatConfigWidget.h"
#include "ui_ChatConfigWidget.h"

#include <Models.h>

#include <QSettings>

using namespace oaic;

ChatConfigWidget::ChatConfigWidget(QWidget *parent) :
    ChatToolWidget(parent),
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

void ChatConfigWidget::synchronizeClient(Manager *client)
{
    _client = client;

    connect(_client->models(), &oaic::Models::models, this, &ChatConfigWidget::onModels);
    _client->models()->modelList();
}

void ChatConfigWidget::on_modelComboBox_currentTextChanged(const QString &modelName)
{
    int index = ui->modelComboBox->currentIndex();
    if (index < 0) {
        return;
    }

    if (_modelCntx) {
        if (_modelCntx->modelName() != modelName) {
            qDebug() << "MODEL NAME:" << modelName;
            _modelCntx->setModelName(modelName);
            ui->saveConfigurationButton->setEnabled(true);
        }
    }
}

ModelContext *ChatConfigWidget::modelCntx() const
{
    return _modelCntx;
}

void ChatConfigWidget::setModelCntx(ModelContext *newModelCntx)
{
    _modelCntx = newModelCntx;

    updateElements(false);
}

void ChatConfigWidget::synchronizeCurrentSession()
{
    qDebug() << "CHAT CONFIG SESSION ID:" << pageContext()->currentSessionId();
    // TODO: copy the model context data from the given session's ModelContext (if _modelCntx exist)
}

void ChatConfigWidget::onSessionCreatedSpecific(int pageIndex, const QString &newSessionId)
{
    // TODO: implement in case of model per session
    qDebug() << "ChatConfigWidget CREATE SESSION ON PAGE:" << pageIndex << "NEW SESSION:" << newSessionId;
}

void ChatConfigWidget::updateElements(bool updateModelName)
{
    if (updateModelName) {
        auto modelName = _modelCntx->modelName();
        ui->modelComboBox->setCurrentText(modelName);
    }

    int temperatureInt = _modelCntx->temperature() * 100;
    ui->temperatureSlider->setValue(temperatureInt);
    on_temperatureSlider_valueChanged(temperatureInt); // call directly because the value can be the same

    int maxTokens = _modelCntx->maxTokens();
    ui->maxTokensSlider->setValue(maxTokens);
    on_maxTokensSlider_valueChanged(maxTokens);

    int topPInt = _modelCntx->topP() * 100;
    ui->topPSlider->setValue(topPInt);
    on_topPSlider_valueChanged(topPInt);

    int frequencyInt = _modelCntx->frequencyPenalty() * 100;
    ui->frequencyPenaltySlider->setValue(frequencyInt);
    on_frequencyPenaltySlider_valueChanged(frequencyInt);

    int presenceInt = _modelCntx->presencePenalty() * 100;
    ui->presencePenaltySlider->setValue(presenceInt);
    on_presencePenaltySlider_valueChanged(presenceInt);

    ui->saveConfigurationButton->setEnabled(updateModelName);
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
        ui->saveConfigurationButton->setEnabled(true);
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
        ui->saveConfigurationButton->setEnabled(true);
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
        ui->saveConfigurationButton->setEnabled(true);
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
        ui->saveConfigurationButton->setEnabled(true);
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
        ui->saveConfigurationButton->setEnabled(true);
    }
}

void ChatConfigWidget::onModels(const QStringList &mdls)
{
    ui->modelComboBox->blockSignals(true);
    ui->modelComboBox->addItems(mdls); // sets current index to 0
    ui->modelComboBox->model()->sort(0);
    ui->modelComboBox->blockSignals(false);

    QSettings settings;
    auto defaultModel = settings.value("model/name").toString();

    if (defaultModel.isEmpty()) {
        auto modelName = _modelCntx->modelName();
        qDebug() << "MODEL NAME:" << modelName;
        ui->modelComboBox->setCurrentText(modelName);
    } else {
        ui->modelComboBox->setCurrentText(defaultModel);
    }
}


void ChatConfigWidget::on_saveConfigurationButton_clicked()
{
    QSettings settings;

    auto modelName = _modelCntx->modelName();
    settings.setValue("model/name", modelName);

    auto temperature = _modelCntx->temperature();
    settings.setValue("model/temperature", temperature);

    auto maxTokens = _modelCntx->maxTokens();
    settings.setValue("model/maxTokens", maxTokens);

    auto topP = _modelCntx->topP();
    settings.setValue("model/topP", topP);

    auto frequencyPenalty = _modelCntx->frequencyPenalty();
    settings.setValue("model/frequencyPenalty", frequencyPenalty);

    auto presencePenalty = _modelCntx->presencePenalty();
    settings.setValue("model/presencePenalty", presencePenalty);

    ui->saveConfigurationButton->setEnabled(false);
}


void ChatConfigWidget::on_defaultButton_clicked()
{
    _modelCntx->setDefault();

    updateElements(true);
}

