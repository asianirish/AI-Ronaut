/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

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

    void onCurrentSessionChange();

signals:
    void sendSessionMessages(const oaic::ModelContext &modelCntx, oaic::MsgDataList &messages);

private:
    Ui::PageGeneralChatPage *ui;

    oaic::ModelContext _modelCntx;

    PageContext *_pageContext;
};

#endif // PAGEGENERALCHATPAGE_H
