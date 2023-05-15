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

private:
    Ui::PageDonatePage *ui;
};

#endif // PAGEDONATEPAGE_H
