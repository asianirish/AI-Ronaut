/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef PAGEIMAGEPAGE_H
#define PAGEIMAGEPAGE_H

#include "PageWidget.h"
#include <QNetworkAccessManager>

namespace Ui {
class PageImagePage;
}

class PageImagePage : public PageWidget
{
    Q_OBJECT
public:
    const QString REQUST_TEXT{tr("Request")};
    const QString WAIT_TEXT{tr("Wait...")};


    static const int MSG_WIDGET_EXTRA_HEIGHT = 28;

    explicit PageImagePage(QWidget *parent = nullptr);
    ~PageImagePage();

protected:
    void keyPressEvent(QKeyEvent *event) override;

    void synchronizeClient(oaic::Manager *_client) override;

    void showEvent(QShowEvent *event) override;

private slots:
    void on_requestButton_clicked();

    void onDownloadFinished(QNetworkReply *reply);

    void on_actionSave_Image_as_File_triggered();

    // oaic::Manager slots
    void onUrlResponse(const QStringList &urls);
    void onNetworkError(const QString &errMsg, int errCode);
    void onResponseError(const QString &errMsg);
    void onReplyDestroyed(QObject * = nullptr);

    void on_requestEdit_textChanged();

    void on_actionCopy_to_Clipboard_triggered();

private:
    Ui::PageImagePage *ui;
    QNetworkAccessManager *_nam;
    bool _isComplete = true;

    void onRequestComplete(bool isComplete);
};

#endif // PAGEIMAGEPAGE_H
