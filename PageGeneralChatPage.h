#ifndef PAGEGENERALCHATPAGE_H
#define PAGEGENERALCHATPAGE_H

#include "PageWidget.h"

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
    void updateCntx(AppContext *cntx) override;

private slots:
    void changeCurrentToolPage(int index);

private:
    Ui::PageGeneralChatPage *ui;

    oaic::ModelContext _modelCntx;
};

#endif // PAGEGENERALCHATPAGE_H
