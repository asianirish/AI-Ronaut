/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

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
    void onSessionCreatedSpecific(int pageIndex, const QString &newSessionId) override;

private:
    void updateElements(bool updateModelName = false);

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

    void on_saveConfigurationButton_clicked();

    void on_defaultButton_clicked();

private:
    Ui::ChatConfigWidget *ui;

    oaic::Manager *_client;
    oaic::ModelContext *_modelCntx;
};

#endif // CHATCONFIGWIDGET_H
