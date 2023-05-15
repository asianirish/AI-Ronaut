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

private:
    Ui::PageAboutPage *ui;
};

#endif // PAGEABOUTPAGE_H
