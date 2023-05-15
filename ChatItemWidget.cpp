#include "ChatItemWidget.h"

#include <QAbstractTextDocumentLayout>
#include <QLayout>

ChatItemWidget::ChatItemWidget(QWidget *parent)
    : QWidget{parent}
{

}

void ChatItemWidget::setText(const QString &text)
{
    textBrowser()->setText(text);
}

int ChatItemWidget::textHeight() const
{
    auto doc = textBrowser()->document();
    auto width = textBrowser()->viewport()->width();
    doc->setTextWidth(width);
    auto idealHeight = doc->documentLayout()->documentSize().height();

    return idealHeight + extraSpaceHeight(); // TODO: other controls
}

void ChatItemWidget::stylize() const
{
    QString currentStyle = textBrowser()->styleSheet();
    qDebug() << "style:" << currentStyle;
    textBrowser()->setStyleSheet(currentStyle + " border-radius: 10px;"); // border: 1px solid gray;
}
