#include "PageWidget.h"

#include <oaic/Manager.h>

PageWidget::PageWidget(QWidget *parent)
    : QWidget{parent},
    _client(nullptr)
{

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
