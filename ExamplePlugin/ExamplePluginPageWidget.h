/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef EXAMPLEPLUGINPAGEWIDGET_H
#define EXAMPLEPLUGINPAGEWIDGET_H

#include <PageWidget.h>

namespace Ui {
class ExamplePluginPageWidget;
}

class ExamplePluginPageWidget : public PageWidget
{
    Q_OBJECT

public:
    explicit ExamplePluginPageWidget(QWidget *parent = nullptr);
    ~ExamplePluginPageWidget();

protected:
    void synchronizeClient(oaic::Manager *client) override;

private:
    Ui::ExamplePluginPageWidget *ui;
};

#endif // EXAMPLEPLUGINPAGEWIDGET_H
