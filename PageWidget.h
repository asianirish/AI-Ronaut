/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef PAGEWIDGET_H
#define PAGEWIDGET_H


namespace oaic {
class Manager;
}

#include <QWidget>

class PageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PageWidget(QWidget *parent = nullptr);

    oaic::Manager *client() const;
    void initClient(); // TODO: use NetworkContext * as an arg

signals:

protected:
    virtual void synchronizeClient(oaic::Manager *_client) = 0;

private:
    oaic::Manager *_client;
};

#endif // PAGEWIDGET_H
