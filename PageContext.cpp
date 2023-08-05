/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

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
