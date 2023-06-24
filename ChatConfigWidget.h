#ifndef CHATCONFIGWIDGET_H
#define CHATCONFIGWIDGET_H

#include "ChatToolWidget.h"
#include "Manager.h"

#include <ModelContext.h>

namespace Ui {
class ChatConfigWidget;
}

class ChatConfigWidget : public ChatToolWidget
{
    Q_OBJECT

public:
    explicit ChatConfigWidget(QWidget *parent = nullptr);
    ~ChatConfigWidget();

    void synchronizeClient(oaic::Manager *client);

    oaic::ModelContext *modelCntx() const;
    void setModelCntx(oaic::ModelContext *newModelCntx);

protected:
    void synchronizeCurrentSession() override;

private slots:
    void on_modelComboBox_currentTextChanged(const QString &modelName);

    void on_maxTokensSlider_sliderMoved(int position);

    void on_maxTokensSlider_valueChanged(int value);

    void on_topPSlider_sliderMoved(int position);

    void on_topPSlider_valueChanged(int value);

    void on_frequencyPenaltySlider_sliderMoved(int position);

    void on_frequencyPenaltySlider_valueChanged(int value);

    void on_presencePenaltySlider_sliderMoved(int position);

    void on_presencePenaltySlider_valueChanged(int value);

    void on_temperatureSlider_sliderMoved(int position);

    void on_temperatureSlider_valueChanged(int value);

    void onModels(const QStringList &mdls);

private:
    Ui::ChatConfigWidget *ui;

    oaic::Manager *_client;
    oaic::ModelContext *_modelCntx;
};

#endif // CHATCONFIGWIDGET_H
