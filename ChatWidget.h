#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include "ChatItemWidget.h"
#include "ui_ChatWidget.h"

#include <ModelContext.h>
#include <Manager.h>

#include <QWidget>
#include <QThread>

namespace Ui {
class ChatWidget;
}

class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWidget(QWidget *parent = nullptr);
    ~ChatWidget();

    oaic::ModelContext *modelCntx() const;
    void setModelCntx(oaic::ModelContext *newModelCntx);

    oaic::Manager *client() const;
    void setClient(oaic::Manager *newClient);

protected:
    void resizeEvent(QResizeEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

    void showEvent(QShowEvent *event) override;

private slots:
    void on_sendButton_clicked();
    void adjustLastItem();
    void queryAiModel();

    void onDeltaError(const QString &deltaError);
    // TODO: onNetworkError connected with Component::networkError

    void on_isSessionBox_stateChanged(int isSession);

    void onMessageResponseStream(const QStringList &deltaMessages);
    void onMessageResponseComplete(QObject *); // onReplyDestroyed instead of onReplyComplete

signals:
    void sendMessage(const oaic::ModelContext &modelCntx, const QString &input);

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
};

#endif // CHATWIDGET_H
