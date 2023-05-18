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

private:
    Ui::PageDonatePage *ui;
};

#endif // PAGEDONATEPAGE_H
