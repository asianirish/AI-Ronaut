/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#include "PageImagePage.h"
#include "ui_PageImagePage.h"

#include "util/gfunc.h"

#include <oaic/Manager.h>
#include <oaic/Image.h>

#include <QNetworkReply>
#include <QKeyEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QClipboard>

PageImagePage::PageImagePage(QWidget *parent) :
    PageWidget(parent),
    ui(new Ui::PageImagePage)
{
    ui->setupUi(this);

    ui->imageSizeComboBox->addItem("256x256");
    ui->imageSizeComboBox->addItem("512x512");
    ui->imageSizeComboBox->addItem("1024x1024");

    _nam = new QNetworkAccessManager(this);
    connect(_nam, &QNetworkAccessManager::finished, this, &PageImagePage::onDownloadFinished);

    ui->imgLabel->addAction(ui->actionSave_Image_as_File);

    // TODO: implement these features in 1.1.0
//    ui->imgLabel->addAction(ui->actionSave_Image_to_List);
//    ui->imgLabel->addAction(ui->actionSet_as_Base_Image);
//    ui->imgLabel->addAction(ui->actionEdit_Image);

    ui->imgLabel->addAction(ui->actionCopy_to_Clipboard);

    on_requestEdit_textChanged();
    onRequestComplete(true);
}

PageImagePage::~PageImagePage()
{
    delete ui;
}

void PageImagePage::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {

        if (event->modifiers() & Qt::ControlModifier) {
            on_requestButton_clicked();
            return;
        }
    }

    QWidget::keyPressEvent(event);
}

void PageImagePage::synchronizeClient(oaic::Manager *client)
{
    connect(client->image(), &oaic::Image::urlResponse, this, &PageImagePage::onUrlResponse);
    connect(client->image(), &oaic::Component::networkError, this, &PageImagePage::onNetworkError);
    connect(client->image(), &oaic::Component::responseError, this, &PageImagePage::onResponseError);
    connect(client->image(), &oaic::Component::replyDestroyed, this, &PageImagePage::onReplyDestroyed);
}

void PageImagePage::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    ui->requestEdit->setFocus(Qt::OtherFocusReason);
}

void PageImagePage::on_requestButton_clicked()
{
    if (!_isComplete) {
        qDebug() << "prevent double request submission";
        return;
    }

    auto text = ui->requestEdit->toPlainText();

    if (text.length() <= 3) {
        QMessageBox::warning(this, "warning", tr("Your picture description is too short"));
        ui->requestEdit->setFocus(Qt::OtherFocusReason);
        return;
    }

    onRequestComplete(false);

    auto size = ui->imageSizeComboBox->currentText();

    // TODO: delete the deprecated code above
    client()->image()->sendGenImageRequest(text, size);
}

void PageImagePage::onDownloadFinished(QNetworkReply *reply)
{
    QPixmap pm;
    pm.loadFromData(reply->readAll());
    ui->imgLabel->setPixmap(pm);

    onRequestComplete(true);

    ui->imgLabel->setEnabled(true);
}


void PageImagePage::on_actionSave_Image_as_File_triggered()
{
    auto pm = ui->imgLabel->pixmap();

    if (pm.isNull()) {
        qDebug() << "nothing to save";
        return;
    }

    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("yyyyMMddhhmmss");

    auto text = ui->requestEdit->toPlainText();
    auto ftext = potato_util::phraseToCamelCase(text, 7);
    ftext = ftext.left(64) + "_" + formattedTime;
    auto fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), ftext + ".png", tr("Image Files (*.png *.jpg *.bmp)"));

    if (!fileName.contains(".png")) {
        fileName += ".png";
    }
    pm.save(fileName);
}

void PageImagePage::onUrlResponse(const QStringList &urls)
{
    auto url = urls.at(0);

    onRequestComplete(true);

    ui->imgLabel->setEnabled(true); // TODO: the image hasn't been downloaded yet!

    QNetworkRequest request(url);
    _nam->get(request);

}

void PageImagePage::onNetworkError(const QString &errMsg, int errCode)
{
    qDebug() << "NETWORK ERROR:" << errMsg << errCode;

    if (errCode != QNetworkReply::ProtocolInvalidOperationError) { // Will be shown as a response error
        QString msg(errMsg);
        msg += "\n\nError code: " + QString::number(errCode);

        QMessageBox::warning(this, tr("Network error"), msg);
    }

    onRequestComplete(true);
}

void PageImagePage::onResponseError(const QString &errMsg)
{
    qDebug() << "RESPONSE ERROR:" << errMsg;

    QMessageBox::warning(this, tr("Response error"), errMsg);

    onRequestComplete(true);
}

void PageImagePage::onReplyDestroyed(QObject *)
{
    // TODO: ?
}


void PageImagePage::on_requestEdit_textChanged()
{
    auto doc = ui->requestEdit->document();
    int newHeight = doc->size().toSize().height();
    ui->requestEdit->setFixedHeight(newHeight);

    ui->requestWidget->setFixedHeight(newHeight + MSG_WIDGET_EXTRA_HEIGHT);
}


void PageImagePage::on_actionCopy_to_Clipboard_triggered()
{
    auto pm = ui->imgLabel->pixmap();
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setPixmap(pm);
}

void PageImagePage::onRequestComplete(bool isComplete)
{
    _isComplete = isComplete;
    ui->requestButton->setEnabled(isComplete);
    ui->requestButton->setText(isComplete ? REQUST_TEXT : WAIT_TEXT);
}

