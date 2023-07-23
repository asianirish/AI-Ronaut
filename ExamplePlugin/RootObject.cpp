#include "RootObject.h"
#include <QMessageBox>

#include <ExamplePluginPageWidget.h>

RootObject::RootObject(QObject *parent)
    : QObject{parent}
{

}

void RootObject::doIt() const
{
    QMessageBox::information(nullptr, "Message", "greetings from a DLL!");
}

PageWidget *RootObject::createPageWidget(QWidget *parent) const
{
    return new ExamplePluginPageWidget(parent);
}

QString RootObject::author() const
{
    return QString("asianirish@gmail.com")
}
