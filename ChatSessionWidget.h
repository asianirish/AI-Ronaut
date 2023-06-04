#ifndef CHATSESSIONWIDGET_H
#define CHATSESSIONWIDGET_H

#include "ChatToolWidget.h"

#include <QListWidgetItem>

namespace Ui {
class ChatSessionWidget;
}

class ChatSessionWidget : public ChatToolWidget
{
    Q_OBJECT

public:
    explicit ChatSessionWidget(QWidget *parent = nullptr);
    ~ChatSessionWidget();

protected:
    void updateCurrentSession(const QString &sessionId) override;

private slots:
    void onSessionCreated(const QString &sessionId);

    void on_sessionListWidget_itemActivated(QListWidgetItem *item);

    void on_sessionListWidget_currentTextChanged(const QString &currentText);

    void on_saveAsTextFileButton_clicked();

private:
    Ui::ChatSessionWidget *ui;
};

#endif // CHATSESSIONWIDGET_H
