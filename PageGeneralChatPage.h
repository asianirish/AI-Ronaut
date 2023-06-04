#ifndef PAGEGENERALCHATPAGE_H
#define PAGEGENERALCHATPAGE_H

#include "PageWidget.h"

#include <Chat.h>

#include <ModelContext.h>

namespace Ui {
class PageGeneralChatPage;
}

class PageGeneralChatPage : public PageWidget
{
    Q_OBJECT

public:
    explicit PageGeneralChatPage(QWidget *parent = nullptr);
    ~PageGeneralChatPage();

protected:
    void updateClient(oaic::Manager *client) override;

private slots:
    void changeCurrentToolPage(int index);
    void onUserMessage(const oaic::ModelContext &modelCntx, const QString &message);

    void onCurrentSessionChange(const QString &sessionId);

signals:
    void sendSessionMessages(const oaic::ModelContext &modelCntx, oaic::MsgDataList &messages);

private:
    Ui::PageGeneralChatPage *ui;

    oaic::ModelContext _modelCntx;

    QString _currentSessionId;
};

#endif // PAGEGENERALCHATPAGE_H
