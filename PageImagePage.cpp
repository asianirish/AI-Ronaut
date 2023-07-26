#include "PageImagePage.h"
#include "ui_PageImagePage.h"

#include "util/gfunc.h"

#include <oaic/Manager.h>
#include <oaic/Image.h>

#include <QNetworkReply>
#include <QKeyEvent>
#include <QMessageBox>
#include <QFileDialog>

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
    ui->imgLabel->addAction(ui->actionSave_Image_to_List);
    ui->imgLabel->addAction(ui->actionSet_as_Base_Image);
    ui->imgLabel->addAction(ui->actionEdit_Image);
    ui->imgLabel->addAction(ui->actionCopy_to_Clipboard);

    on_requestEdit_textChanged();
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
    auto text = ui->requestEdit->toPlainText();

    if (text.length() <= 3) {
        QMessageBox::warning(this, "warning", tr("Your picture description is too short"));
        ui->requestEdit->setFocus(Qt::OtherFocusReason);
        return;
    }

    ui->requestButton->setEnabled(false);

    auto size = ui->imageSizeComboBox->currentText();

    // TODO: delete the deprecated code above
    client()->image()->sendGenImageRequest(text, size);
}

void PageImagePage::onDownloadFinished(QNetworkReply *reply)
{
    QPixmap pm;
    pm.loadFromData(reply->readAll());
    ui->imgLabel->setPixmap(pm);
    ui->requestButton->setEnabled(true);
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

    ui->requestButton->setEnabled(true);
    ui->imgLabel->setEnabled(true);

    QNetworkRequest request(url);
    _nam->get(request);

}

void PageImagePage::onNetworkError(const QString &errMsg, int errCode)
{
    qDebug() << "NETWORK ERROR:" << errMsg << errCode;
}

void PageImagePage::onResponseError(const QString &errMsg)
{
    qDebug() << "RESPONSE ERROR:" << errMsg;
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

