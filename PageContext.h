#ifndef PAGECONTEXT_H
#define PAGECONTEXT_H

#include <QObject>
#include <QString>


class PageContext : public QObject
{
    Q_OBJECT
public:
    PageContext() = delete;
    PageContext(const PageContext &) = delete;

    PageContext(int pageIndex);

    int pageIndex() const;

    QString currentSessionId() const;
    void setCurrentSessionId(const QString &newCurrentSessionId);

private:
    int _pageIndex;
    QString _currentSessionId;

signals:
    void currentSessionChanged();
};

#endif // PAGECONTEXT_H
