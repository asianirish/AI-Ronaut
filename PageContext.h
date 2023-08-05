/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

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
