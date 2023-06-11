#ifndef CHATSESSIONWIDGET_H
#define CHATSESSIONWIDGET_H

#include "ChatToolWidget.h"

#include <QListWidgetItem>

namespace Ui {
class ChatSessionWidget;
}

namespace chat {
class SessionItem;
}

class ChatSessionWidget : public ChatToolWidget
{
    Q_OBJECT

public:
    explicit ChatSessionWidget(QWidget *parent = nullptr);
    ~ChatSessionWidget();

    int myPageNumber() const;

protected:
    void synchronizeCurrentSession(const QString &sessionId) override;

private:
    QModelIndexList findModelIndexesBySessionId(const QString& sessionId);

    chat::SessionItem *findItemBySessionId(const QString& sessionId);

private:
    // TODO: Implement a method to distinguish sessions created on this page or other pages
    int _myPageNumber;

private slots:
    void onSessionCreated(const QString &sessionId);

    void on_sessionListWidget_itemActivated(QListWidgetItem *item);

    void on_sessionListWidget_currentTextChanged(const QString &currentText);

    void on_saveAsTextFileButton_clicked();

public slots:
    void onRenameSession(const QString &name);

private:
    Ui::ChatSessionWidget *ui;
};

#endif // CHATSESSIONWIDGET_H
