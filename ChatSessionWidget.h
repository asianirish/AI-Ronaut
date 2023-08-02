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

protected:
    void synchronizeCurrentSession() override;
    void onSessionCreatedSpecific(int pageIndex, const QString &newSessionId) override;

private:
    QModelIndexList findModelIndexesBySessionId(const QString& sessionId);

    chat::SessionItem *findItemBySessionId(const QString& sessionId);

    void enableOrDisableControls(bool isChanged);

signals:


private slots:
    void on_sessionListWidget_itemActivated(QListWidgetItem *item);

    void on_sessionListWidget_currentTextChanged(const QString &currentText);

    void on_saveAsTextFileButton_clicked();

    void on_sessionNameEdit_textEdited(const QString &arg1);

    void on_applyEditedButton_clicked();

    void on_saveButton_clicked();

    void on_deleteButton_clicked();

    void onSessionDeleted(int pageIndex, const QString sessionId);

    void on_newSessionButton_clicked();

public slots:
    void onRenameSession(const QString &name);

private:
    Ui::ChatSessionWidget *ui;
};

#endif // CHATSESSIONWIDGET_H
