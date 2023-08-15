/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

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

    static int parentHeight();
    static void setParentHeight(int newParentHeight);

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

    static int _parentHeight;

signals:
    void deleteMe();

};

#endif // CHATITEMWIDGET_H
