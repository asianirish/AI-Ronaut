#ifndef CHATCONFIGWIDGET_H
#define CHATCONFIGWIDGET_H

#include "AppContext.h"
#include "ModelContext.h"

#include <QWidget>

namespace Ui {
class ChatConfigWidget;
}

class ChatConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChatConfigWidget(QWidget *parent = nullptr);
    ~ChatConfigWidget();

    void updateCntx(AppContext *cntx);

    ModelContext *modelCntx() const;
    void setModelCntx(ModelContext *newModelCntx);

private slots:
    void on_modelComboBox_currentTextChanged(const QString &modelName);

    void on_temperatureSpinBox_valueChanged(double t);

    void on_maxTokensSlider_sliderMoved(int position);

    void on_maxTokensSlider_valueChanged(int value);

    void on_topPSlider_sliderMoved(int position);

    void on_topPSlider_valueChanged(int value);

    void on_frequencyPenaltySlider_sliderMoved(int position);

    void on_frequencyPenaltySlider_valueChanged(int value);

    void on_presencePenaltySlider_sliderMoved(int position);

    void on_presencePenaltySlider_valueChanged(int value);

private:
    Ui::ChatConfigWidget *ui;

    AppContext *_cntx;
    ModelContext *_modelCntx;
};

#endif // CHATCONFIGWIDGET_H
