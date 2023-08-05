/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef IROOTOBJECT_H
#define IROOTOBJECT_H

#include "Info.h"

#include <PageWidget.h>

#include <QObject>

class IRootObject
{
public:
    virtual void doIt() const = 0;

    virtual PageWidget *createPageWidget(QWidget *parent) const = 0;

    virtual plg::Info pluginInfo() const = 0;
};

Q_DECLARE_INTERFACE(IRootObject, "org.asianirish.IRootObject")

#endif // IROOTOBJECT_H
