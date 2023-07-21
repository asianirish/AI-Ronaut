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
