#ifndef PAGECONTEXT_H
#define PAGECONTEXT_H

#include <QString>

// TODO: Make the following class inherit from QObject and emit a signal on session change
class PageContext
{
public:
    PageContext() = delete;
    PageContext(const PageContext &) = delete;

    PageContext(int pageIndex, const QString &sessionId);
    PageContext(int pageIndex);

    int pageIndex() const;

    QString currentSessionId() const;
    void setCurrentSessionId(const QString &newCurrentSessionId);

private:
    int _pageIndex;
    QString _currentSessionId;
};

#endif // PAGECONTEXT_H
