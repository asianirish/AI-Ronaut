/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

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

plg::Info RootObject::pluginInfo() const
{
    plg::Info info;
    info.setName("Example Plugin");
    info.setDesc("The plugin is designed to illustrate the process of connecting to and using the plugin mechanism within the AI-ronaut software");
    info.setAuthor("asianirish@gmail.com");
    info.setVersion(plg::Version("1.0.0"));

    return info;
}

//QString RootObject::author() const
//{
//    return QString("asianirish@gmail.com");
//}
