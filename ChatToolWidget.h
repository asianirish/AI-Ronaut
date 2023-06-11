#ifndef CHATTOOLWIDGET_H
#define CHATTOOLWIDGET_H

#include "PageContext.h"

#include <QWidget>

class ChatToolWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChatToolWidget(QWidget *parent = nullptr);

    QString currentSessionId() const;
    void setCurrentSessionId(const QString &newCurrentSessionId);

    PageContext *pageContext() const;
    void setPageContext(PageContext *newPageContext);

protected:
    virtual void synchronizeCurrentSession(const QString &sessionId) = 0;

private:
    QString _currentSessionId;
    PageContext *_pageContext;

public slots:
    void onCurrentSessionChange(const QString &sessionId);

signals:

};

#endif // CHATTOOLWIDGET_H
