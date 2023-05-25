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

    QString text() const;

protected:
    virtual QTextBrowser *textBrowser() const = 0;
    virtual int extraSpaceHeight() const = 0;

protected:
    // call from parent actions:
    void onCopyAction() const;

signals:

};

#endif // CHATITEMWIDGET_H
