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

private:
    Ui::PageImagePage *ui;
    QNetworkAccessManager *_nam;
};

#endif // PAGEIMAGEPAGE_H
