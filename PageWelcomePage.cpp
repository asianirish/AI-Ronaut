#include "PageWelcomePage.h"
#include "ui_PageWelcomePage.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>

using namespace liboai;

const QString PageWelcomePage::IMAGE_ACTION("image");
const QString PageWelcomePage::CHAT_ACTION("chat");
const QString PageWelcomePage::DONATE_ACTION("donate");
const QString PageWelcomePage::ABOUT_ACTION("about");

PageWelcomePage::PageWelcomePage(QWidget *parent) :
    PageWidget(parent),
    ui(new Ui::PageWelcomePage)
{
    ui->setupUi(this);

    ui->activityComboBox->addItem(tr("General сhat сonversation"), CHAT_ACTION);
    ui->activityComboBox->addItem(tr("Image generation"), IMAGE_ACTION);
    ui->activityComboBox->addItem(tr("Educational Chat Conversation")); // TODO: second arg
//    ui->activityComboBox->addItem(tr("Writing a plot")); // TODO: second arg

    ui->activityComboBox->addItem(tr("Donate"), DONATE_ACTION);
    ui->activityComboBox->addItem(tr("About"), ABOUT_ACTION);

    ui->activityComboBox->setCurrentIndex(-1);

    displayWait();
    checkKeyFromSettings();
}

PageWelcomePage::~PageWelcomePage()
{
    delete ui;
}

void PageWelcomePage::on_browseKeyButton_clicked()
{
    auto fileName = QFileDialog::getOpenFileName(this, tr("Open OAI Key"));

    if (fileName.isNull()) {
        return;
    }

    displayWait();

    QString key;
    QString err;
    bool ok = _appContext.openKeyFile(fileName, key, &err);

    if (!ok) {
        QMessageBox::warning(this, "error", err);
        displayError();
        return;
    }

    onKeySuccess();

    QSettings settings;

    // TODO: crypt the key
    settings.setValue("oai/key", key);
}


void PageWelcomePage::on_openActivityButton_clicked()
{
    QString actionData = ui->activityComboBox->currentData().toString();
    openAction(actionData);
}

void PageWelcomePage::displaySuccess()
{
    ui->keyFileLabel->setText(tr("OpenAI API file loaded successfully"));
    ui->keyFileLabel->setStyleSheet("QLabel { color : green; }");
    ui->activityFrame->setEnabled(true);
    ui->activityFrame->setVisible(true);
}

void PageWelcomePage::displayError()
{
    ui->keyFileLabel->setText(tr("Error: Failed to load OpenAI API file"));
    ui->keyFileLabel->setStyleSheet("QLabel { color : red; }");
    ui->activityFrame->setEnabled(false);
    ui->activityFrame->setVisible(false);
}

void PageWelcomePage::displayWait()
{
    ui->keyFileLabel->setText(tr("Waiting for OpenAI API file to load..."));
    ui->keyFileLabel->setStyleSheet("QLabel { color : red; }");
    ui->activityFrame->setEnabled(false);
    ui->activityFrame->setVisible(false);
}

void PageWelcomePage::openAction(const QString &actionData)
{
    if (actionData == IMAGE_ACTION) {
        emit openImageAction();
    } else if (actionData == CHAT_ACTION) {
        emit openChatAction();
    } else if (actionData == DONATE_ACTION) {
        emit openDonateAction();
    } else if (actionData == ABOUT_ACTION) {
        emit openAboutAction();
    }
}

void PageWelcomePage::checkKeyFromSettings()
{
    QSettings settings;
    auto key = settings.value("oai/key").toString();

    if (!key.isEmpty()) {
        QString err;

        bool ok = _appContext.setKey(key, &err);

        if (ok) {
            onKeySuccess();
        }
    }
}

void PageWelcomePage::onKeySuccess()
{
    // read other app context settings here
    QSettings settings;
    int32_t timeout = settings.value("oai/timeout", AppContext::DEFAULT_TIMEOUT_MS).toInt();

    _appContext.setTimeOutMs(timeout);

    setCntx(&_appContext);
    displaySuccess();
}

void PageWelcomePage::on_activityComboBox_currentIndexChanged(int index)
{
    Q_UNUSED(index)
    on_openActivityButton_clicked();
}

void PageWelcomePage::updateCntx(AppContext *cntx)
{
    Q_UNUSED(cntx); // nothing to do
}

