#include "PageWidget.h"

#include <oaic/Manager.h>

PageWidget::PageWidget(QWidget *parent)
    : QWidget{parent},
    _cntx(nullptr),
    _client(nullptr)
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

oaic::Manager *PageWidget::client() const
{
    return _client;
}

void PageWidget::setClient(oaic::Manager *newClient)
{
    _client = newClient;

   updateClient(newClient);
}
