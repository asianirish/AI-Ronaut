#include "ChatItemWidget.h"

#include <QAbstractTextDocumentLayout>
#include <QLayout>
#include <QClipboard>
#include <QGuiApplication>

ChatItemWidget::ChatItemWidget(QWidget *parent)
    : QWidget{parent},
    _listItem(nullptr)
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
    textBrowser()->setStyleSheet(currentStyle + " border-radius: 10px;"); // border: 1px solid gray;
}

QString ChatItemWidget::text() const
{
    return textBrowser()->toPlainText();
}

void ChatItemWidget::onCopyAction() const
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    auto text = textBrowser()->toPlainText();
    clipboard->setText(text);
}

void ChatItemWidget::adjustHeight()
{
    if (_listItem) {
        int idealHeight = textHeight();
        _listItem->setSizeHint({sizeHint().width(), int(idealHeight)});
    }
}

QListWidgetItem *ChatItemWidget::listItem() const
{
    return _listItem;
}

void ChatItemWidget::setListItem(QListWidgetItem *newListItem)
{
    _listItem = newListItem;
}
