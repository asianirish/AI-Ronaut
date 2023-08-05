/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef PAGEABOUTPAGE_H
#define PAGEABOUTPAGE_H

#include <QWidget>

namespace Ui {
class PageAboutPage;
}

class PageAboutPage : public QWidget
{
    Q_OBJECT

public:
    explicit PageAboutPage(QWidget *parent = nullptr);
    ~PageAboutPage();

private slots:
    void on_commandLinkButton_clicked();

private:
    Ui::PageAboutPage *ui;
};

#endif // PAGEABOUTPAGE_H
