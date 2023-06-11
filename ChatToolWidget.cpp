#include "ChatToolWidget.h"

ChatToolWidget::ChatToolWidget(QWidget *parent)
    : QWidget{parent},
    _pageContext(nullptr)
{

}

QString ChatToolWidget::currentSessionId() const
{
    return _currentSessionId;
}

void ChatToolWidget::setCurrentSessionId(const QString &newCurrentSessionId)
{
    _currentSessionId = newCurrentSessionId;

    synchronizeCurrentSession(_currentSessionId);
}

PageContext *ChatToolWidget::pageContext() const
{
    return _pageContext;
}

void ChatToolWidget::setPageContext(PageContext *newPageContext)
{
    _pageContext = newPageContext;
}

void ChatToolWidget::onCurrentSessionChange(const QString &sessionId)
{
    setCurrentSessionId(sessionId);
}
