#include "PageContext.h"

#include <QDebug>


PageContext::PageContext(int pageIndex) : _pageIndex(pageIndex)
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
    if (_currentSessionId != newCurrentSessionId) {
        _currentSessionId = newCurrentSessionId;
        emit currentSessionChanged();
    }
}
