#include "PageContext.h"

#include <QDebug>

PageContext::PageContext(int pageIndex, const QString &sessionId) :
    _pageIndex(pageIndex),
    _currentSessionId(sessionId)
{

}

PageContext::PageContext(int pageIndex) : PageContext(pageIndex, QString())
{

}

int PageContext::pageIndex() const
{
    return _pageIndex;
}

QString PageContext::currentSessionId() const
{
    return _currentSessionId;
}

void PageContext::setCurrentSessionId(const QString &newCurrentSessionId)
{
    // Debug
    if (_pageIndex == 1) {
        qDebug() << "...........................PAGE1 SESSION" << newCurrentSessionId;
    }
    _currentSessionId = newCurrentSessionId;
}
