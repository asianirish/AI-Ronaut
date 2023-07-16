#include "ChatToolWidget.h"

#include "chat/SessionManager.h"

ChatToolWidget::ChatToolWidget(QWidget *parent)
    : QWidget{parent},
    _pageContext(nullptr)
{
    connect(gSessions, &chat::SessionManager::sessionCreated, this, &ChatToolWidget::onSessionCreatedGeneral);
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

    synchronizeCurrentSession();
}

void ChatToolWidget::changeSessionId(const QString &sessionId)
{
    _pageContext->setCurrentSessionId(sessionId);
}

void ChatToolWidget::onCurrentSessionChange()
{
    synchronizeCurrentSession();
}

void ChatToolWidget::onSessionCreatedGeneral(int pageIndex, const QString &sessionId)
{
    if (_pageContext) {
        changeSessionId(sessionId);
        if (_pageContext->pageIndex() == pageIndex) {
            synchronizeCurrentSession();
        }
    }

    onSessionCreatedSpecific(pageIndex, sessionId);
}
