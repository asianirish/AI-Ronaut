/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

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
