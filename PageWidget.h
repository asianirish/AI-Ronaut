#ifndef PAGEWIDGET_H
#define PAGEWIDGET_H

#include "AppContext.h"

namespace oaic {
class Manager;
}

#include <QWidget>
class PageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PageWidget(QWidget *parent = nullptr);

    AppContext *cntx() const;
    void setCntx(AppContext *newCntx);

    oaic::Manager *client() const;
    void setClient(oaic::Manager *newClient);

signals:

protected:
    virtual void updateCntx(AppContext *cntx) = 0;
    virtual void updateClient(oaic::Manager *_client) = 0;

private:

    [[deprecated("use _client instead")]]
    AppContext *_cntx;

    oaic::Manager *_client;
};

#endif // PAGEWIDGET_H
