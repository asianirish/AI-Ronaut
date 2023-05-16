#include "PageImagePage.h"
#include "ui_PageImagePage.h"

#include <QNetworkReply>
#include <QKeyEvent>
#include <QMessageBox>
#include <QFileDialog>

// TODO: share
QString phraseToCamelCase(const QString& s)
{
    QStringList parts = s.split(' ', Qt::SkipEmptyParts);
    for (int i=1; i<parts.size(); ++i)
        parts[i].replace(0, 1, parts[i][0].toUpper());

    return parts.join("");
}

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

void PageImagePage::updateCntx(AppContext *cntx)
{
    Q_UNUSED(cntx)
    // TODO: add your code here
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

    QString err;
    auto urlStr = this->cntx()->loadImage(text, size, &err);

    if (urlStr.isEmpty() && !err.isEmpty()) {
        QMessageBox::warning(this, "error", err);
        ui->requestButton->setEnabled(true);
        ui->imgLabel->setEnabled(true);
        return;
    }

    const QUrl url = QUrl(urlStr);
    QNetworkRequest request(url);
    _nam->get(request);
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

//    QDateTime date = QDateTime::currentDateTime();
//    QString formattedTime = date.toString("yyyyMMddhhmmss");
//    QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();
//    auto fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), formattedTimeMsg + ".png", tr("Image Files (*.png *.jpg *.bmp)"));

    auto text = ui->requestEdit->toPlainText();
    auto ftext = phraseToCamelCase(text);
    ftext = ftext.left(64);
    auto fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), ftext + ".png", tr("Image Files (*.png *.jpg *.bmp)"));

    if (!fileName.contains(".png")) {
        fileName += ".png";
    }
    pm.save(fileName);
}

