#ifndef PAGECONTEXT_H
#define PAGECONTEXT_H

#include <QString>


class PageContext
{
public:
    PageContext() = delete;
    PageContext(const PageContext &) = delete;

    PageContext(int pageIndex, const QString &sessionId);

    int pageIndex() const;

    QString currentSessionId() const;
    void setCurrentSessionId(const QString &newCurrentSessionId);

private:
    int _pageIndex;
    QString _currentSessionId;
};

#endif // PAGECONTEXT_H
