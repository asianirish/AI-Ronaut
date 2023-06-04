#include "ChatToolWidget.h"

ChatToolWidget::ChatToolWidget(QWidget *parent)
    : QWidget{parent}
{

}

QString ChatToolWidget::currentSessionId() const
{
    return _currentSessionId;
}

void ChatToolWidget::setCurrentSessionId(const QString &newCurrentSessionId)
{
    _currentSessionId = newCurrentSessionId;

    synchronizeCurrentSession(_currentSessionId);
}

void ChatToolWidget::onCurrentSessionChange(const QString &sessionId)
{
    setCurrentSessionId(sessionId);
}
