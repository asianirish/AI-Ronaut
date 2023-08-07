/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#include "PageWidget.h"

#include <oaic/Manager.h>

#include <QMessageBox>
#include <QProcessEnvironment>

PageWidget::PageWidget(QWidget *parent)
    : QWidget{parent},
    _client(new oaic::Manager(this))
{

}

oaic::Manager *PageWidget::client() const
{
    return _client;
}

void PageWidget::initClient()
{
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    QString envKey("OPENAI_API_KEY");

    if (env.contains(envKey)) { // OPENAI_API_KEY
        bool ok = _client->auth().setKeyEnv(envKey);

        if (!ok) {
            qDebug() << "AUTH ERROR";
            QMessageBox::warning(this, "OpenAI Key", "Please set OPENAI_API_KEY as an environment variable with your OpenAI API key");
        }
    } else {
        if (oaic::Manager::auth().isEmpty()) {
            qDebug() << "AUTH ERROR";
            QMessageBox::warning(this, "OpenAI Key", "Please set OPENAI_API_KEY as an environment variable with your OpenAI API key");
        }
    }
    synchronizeClient(_client);
}
