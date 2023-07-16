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
    int pageIndex() const;

    PageContext *pageContext() const;
    void setPageContext(PageContext *newPageContext);
    void changeSessionId(const QString &sessionId);

protected:
    virtual void synchronizeCurrentSession() = 0; // TODO: rename to onPageSessionSelected
    virtual void onSessionCreatedSpecific(int pageIndex, const QString &newSessionId) = 0;

private:
    PageContext *_pageContext;

public slots:
    void onCurrentSessionChange();
    void onSessionCreatedGeneral(int pageIndex, const QString &sessionId); // TODO: rename

signals:

};

#endif // CHATTOOLWIDGET_H
