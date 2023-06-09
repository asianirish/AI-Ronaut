#ifndef PAGEPLOTPAGE_H
#define PAGEPLOTPAGE_H

#include "PageWidget.h"


namespace Ui {
class PagePlotPage;
}

class PagePlotPage : public PageWidget
{
    Q_OBJECT

public:
    explicit PagePlotPage(QWidget *parent = nullptr);
    ~PagePlotPage();

protected:
    void synchronizeClient(oaic::Manager *_client) override;

private:
    Ui::PagePlotPage *ui;
};

#endif // PAGEPLOTPAGE_H
