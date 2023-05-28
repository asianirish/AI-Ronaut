#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include "ChatItemWidget.h"
#include "ModelContext.h"
#include "AppContext.h"
#include "ui_ChatWidget.h"

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

    AppContext *appCntx() const;
    void setAppCntx(AppContext *newAppCntx);

protected:
    void resizeEvent(QResizeEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

    void showEvent(QShowEvent *event) override;

private slots:
    void on_sendButton_clicked();
    void adjustLastItem();
    void queryAiModel();

    void onDeltaReady(const QString &deltaData);

    void onReplyComplete();

    void onDeltaError(const QString &deltaError);

    void on_isSessionBox_stateChanged(int isSession);

signals:
    void queryAiModelPlease(const QString &input, const QString &key, const oaic::ModelContext &modelCntx);

private:
    Ui::ChatWidget *ui;

    oaic::ModelContext *_modelCntx;
    AppContext *_appCntx;

    QThread _chatThread;

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
};

#endif // CHATWIDGET_H
