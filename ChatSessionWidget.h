#ifndef CHATSESSIONWIDGET_H
#define CHATSESSIONWIDGET_H

#include <QWidget>

namespace Ui {
class ChatSessionWidget;
}

class ChatSessionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChatSessionWidget(QWidget *parent = nullptr);
    ~ChatSessionWidget();

private:
    Ui::ChatSessionWidget *ui;
};

#endif // CHATSESSIONWIDGET_H
