/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef PAGEDONATEPAGE_H
#define PAGEDONATEPAGE_H

#include <QWidget>

namespace Ui {
class PageDonatePage;
}

class PageDonatePage : public QWidget
{
    Q_OBJECT

public:
    explicit PageDonatePage(QWidget *parent = nullptr);
    ~PageDonatePage();

private slots:
    void on_copyButton_clicked();

    void on_clipComboBox_currentIndexChanged(int index);

    void on_copyAllTextButton_clicked();

private:
    Ui::PageDonatePage *ui;
};

#endif // PAGEDONATEPAGE_H
