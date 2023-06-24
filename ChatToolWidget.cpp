#include "ChatToolWidget.h"

ChatToolWidget::ChatToolWidget(QWidget *parent)
    : QWidget{parent},
    _pageContext(nullptr)
{

}

QString ChatToolWidget::currentSessionId() const
{
    return _pageContext->currentSessionId();
}

int ChatToolWidget::pageIndex() const
{
    return _pageContext->pageIndex();
}

PageContext *ChatToolWidget::pageContext() const
{
    return _pageContext;
}

void ChatToolWidget::setPageContext(PageContext *newPageContext)
{
    _pageContext = newPageContext;

    synchronizeCurrentSession(_pageContext->currentSessionId());
void ChatToolWidget::changeSessionId(const QString &sessionId)
{
    _pageContext->setCurrentSessionId(sessionId);
}

void ChatToolWidget::onCurrentSessionChange()
{
// TODO: syncronizePageContext(); // (virtual)
}
