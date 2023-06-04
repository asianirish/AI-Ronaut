#ifndef CHATTOOLWIDGET_H
#define CHATTOOLWIDGET_H

#include <QWidget>

class ChatToolWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChatToolWidget(QWidget *parent = nullptr);

    QString currentSessionId() const;
    void setCurrentSessionId(const QString &newCurrentSessionId);

protected:
    virtual void synchronizeCurrentSession(const QString &sessionId) = 0;

private:
    QString _currentSessionId;

public slots:
    void onCurrentSessionChange(const QString &sessionId);

signals:

};

#endif // CHATTOOLWIDGET_H
