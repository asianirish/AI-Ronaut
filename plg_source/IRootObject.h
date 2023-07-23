#ifndef IROOTOBJECT_H
#define IROOTOBJECT_H

#include <PageWidget.h>

#include <QObject>

class IRootObject
{
public:
    virtual void doIt() const = 0;

    virtual PageWidget *createPageWidget(QWidget *parent) const = 0;

    virtual QString author() const = 0;
};

Q_DECLARE_INTERFACE(IRootObject, "org.asianirish.IRootObject")

#endif // IROOTOBJECT_H
