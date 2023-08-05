/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

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
    connect(_pageContext, &PageContext::currentSessionChanged, this, &ChatToolWidget::onCurrentSessionChange);
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
        if (_pageContext->pageIndex() == pageIndex) {
            changeSessionId(sessionId);
            synchronizeCurrentSession();
        }
    }

    onSessionCreatedSpecific(pageIndex, sessionId);
}
