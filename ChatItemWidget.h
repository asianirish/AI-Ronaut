#ifndef CHATITEMWIDGET_H
#define CHATITEMWIDGET_H

#include <QWidget>
#include <QTextBrowser>

class ChatItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChatItemWidget(QWidget *parent = nullptr);

    void setText(const QString &text);

    int textHeight() const;

    void stylize() const;

protected:
    virtual QTextBrowser *textBrowser() const = 0;
    virtual int extraSpaceHeight() const = 0;

signals:

};

#endif // CHATITEMWIDGET_H
