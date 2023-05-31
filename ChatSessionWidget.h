#ifndef CHATSESSIONWIDGET_H
#define CHATSESSIONWIDGET_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class ChatSessionWidget;
}

class ChatSessionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChatSessionWidget(QWidget *parent = nullptr);
    ~ChatSessionWidget();

private slots:
    void onSessionCreated(const QString &sessionId);

    void on_sessionListWidget_itemActivated(QListWidgetItem *item);

    void on_sessionListWidget_currentTextChanged(const QString &currentText);

private:
    Ui::ChatSessionWidget *ui;
};

#endif // CHATSESSIONWIDGET_H
