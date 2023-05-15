#include "PageWidget.h"

PageWidget::PageWidget(QWidget *parent)
    : QWidget{parent},
    _cntx(nullptr)
{

}

AppContext *PageWidget::cntx() const
{
    return _cntx;
}

void PageWidget::setCntx(AppContext *newCntx)
{
    _cntx = newCntx;

    updateCntx(newCntx);
}
