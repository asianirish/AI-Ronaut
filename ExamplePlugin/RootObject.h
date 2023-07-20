#ifndef ROOTOBJECT_H
#define ROOTOBJECT_H

#include <plg/IRootObject.h>
#include <QObject>

class RootObject : public QObject, public IRootObject
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.asianirish.IRootObject" FILE "ExamplePlugin.json")
    Q_INTERFACES(IRootObject)
public:
    explicit RootObject(QObject *parent = nullptr);

    void doIt() const;

signals:

};

#endif // ROOTOBJECT_H
