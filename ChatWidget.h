/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include "ChatToolWidget.h"

#include "ChatItemWidget.h"
#include "ui_ChatWidget.h"

#include "chat/Message.h"

#include <ModelContext.h>
#include <Manager.h>

#include <QThread>

namespace Ui {
class ChatWidget;
}

class ChatWidget : public ChatToolWidget
{
    Q_OBJECT
public:
    static const int MSG_WIDGET_EXTRA_HEIGHT = 18;

    explicit ChatWidget(QWidget *parent = nullptr);
    ~ChatWidget();

    oaic::ModelContext *modelCntx() const;
    void setModelCntx(oaic::ModelContext *newModelCntx);

    oaic::Manager *client() const;
    void setClient(oaic::Manager *newClient);

protected:
    void synchronizeCurrentSession() override;
    void onSessionCreatedSpecific(int pageIndex, const QString &newSessionId) override;

protected:
    void resizeEvent(QResizeEvent *event) override;

    void showEvent(QShowEvent *event) override;

private slots:
    void on_sendButton_clicked();
    void sendAiModelRequest();

    void onDeltaError(const QString &deltaError);
    // TODO: onNetworkError connected with Component::networkError

    void onMessageResponseStream(const QStringList &deltaMessages);
    void onMessageResponseComplete(QObject *); // onReplyDestroyed instead of onReplyComplete

    void on_newSessionButton_clicked();

    void on_abortChatButton_clicked();

    void onDeleteItemRequest();

    void on_actionDelete_Item_triggered();

    void on_actionEditItem_triggered();

    void onSessionDeleted(int pageIndex, const QString sessionId);

    void on_textEdit_textChanged();

signals:
     // TODO: take a model context from the current session
    void sendCurrentSessionMessages(const oaic::ModelContext &modelCntx);
    void sessionChaged();

    void renameSession(const QString &name);

private:
    Ui::ChatWidget *ui;

    oaic::ModelContext *_modelCntx;
    oaic::Manager *_client;

private:
    void updateItemsHeight();
    void addMessageItem(ChatItemWidget *itemWidget, const QString &text);

    QWidget *lastChatItemMessageWidget() const;

    template<typename T>
    T *lastChatItemMessageWidgetByType() const {
        auto cnt = ui->listWidget->count();
        for (int i = cnt - 1; i >= 0; i--) {
            auto item = ui->listWidget->item(i);
            auto itemWidget = ui->listWidget->itemWidget(item);
            auto chatWidget = qobject_cast<T*>(itemWidget);

            if (chatWidget) {
                return chatWidget;
            }
        }

        return nullptr;
    }

    void onDeltaReady(const QString &deltaData);

    void enableOrDisableControls(bool isSending);

    void continueChat();

    template<typename T>
    T *createMessageItemWidget(const QString &text, chat::MessagePtr msgPtr = {}) {
        T *itemWidget = new T(currentSessionId(), msgPtr, this);

        connect(itemWidget, &T::deleteMe, this, &ChatWidget::onDeleteItemRequest);

        addMessageItem(itemWidget, text);

        return itemWidget;
    }
};

#endif // CHATWIDGET_H
