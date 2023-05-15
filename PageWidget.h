#ifndef PAGEWIDGET_H
#define PAGEWIDGET_H

#include "AppContext.h"

#include <QWidget>
class PageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PageWidget(QWidget *parent = nullptr);

    AppContext *cntx() const;
    void setCntx(AppContext *newCntx);

signals:

protected:
    virtual void updateCntx(AppContext *cntx) = 0;

private:
    AppContext *_cntx;
};

#endif // PAGEWIDGET_H
