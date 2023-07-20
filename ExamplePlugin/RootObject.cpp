#include "RootObject.h"
#include <QMessageBox>

RootObject::RootObject(QObject *parent)
    : QObject{parent}
{

}

void RootObject::doIt() const
{
    QMessageBox::information(nullptr, "Message", "greetings from a DLL!");
}
