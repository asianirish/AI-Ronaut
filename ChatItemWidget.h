#ifndef CHATITEMWIDGET_H
#define CHATITEMWIDGET_H

#include <QWidget>
#include <QTextBrowser>
#include <QListWidgetItem>

class ChatItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChatItemWidget(QWidget *parent = nullptr);
    virtual ~ChatItemWidget() = default;

    void setText(const QString &text);

    int textHeight() const;

    void stylize() const;

    QString text() const;

    QListWidgetItem *listItem() const;
    void setListItem(QListWidgetItem *newListItem);

    void callAdjustHeight();

protected:
    virtual QTextBrowser *textBrowser() const = 0;
    virtual int extraSpaceHeight() const = 0;

protected:
    // call from parent actions:
    void onCopyAction() const;

    void adjustHeight();

private:
    QListWidgetItem *_listItem;

    mutable QString _debugText;

signals:
    void deleteMe();

};

#endif // CHATITEMWIDGET_H
