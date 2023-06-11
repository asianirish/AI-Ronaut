#ifndef PAGEGENERALCHATPAGE_H
#define PAGEGENERALCHATPAGE_H

#include "PageWidget.h"
#include "PageContext.h"

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
    void synchronizeClient(oaic::Manager *client) override;

private slots:
    void changeCurrentToolPage(int index);

    // TODO: take a model context from the current session
    void onUserMessage(const oaic::ModelContext &modelCntx);

    void onCurrentSessionChange(const QString &sessionId);

signals:
    void sendSessionMessages(const oaic::ModelContext &modelCntx, oaic::MsgDataList &messages);

private:
    Ui::PageGeneralChatPage *ui;

    oaic::ModelContext _modelCntx;

    QString _currentSessionId;

    PageContext *_pageContext;
};

#endif // PAGEGENERALCHATPAGE_H
