#include "PageWelcomePage.h"
#include "ui_PageWelcomePage.h"

#include <oaic/Manager.h>

#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QProcessEnvironment>

const QString PageWelcomePage::IMAGE_ACTION("image");
const QString PageWelcomePage::CHAT_ACTION("chat");
const QString PageWelcomePage::PLOT_ACTION("plot");

const QString PageWelcomePage::NETWORK_CONFIG_ACTION("network");
const QString PageWelcomePage::DONATE_ACTION("donate");
const QString PageWelcomePage::ABOUT_ACTION("about");

PageWelcomePage::PageWelcomePage(QWidget *parent) :
    PageWidget(parent),
    ui(new Ui::PageWelcomePage)
{
    ui->setupUi(this);

    ui->activityComboBox->addItem(tr("General сhat сonversation"), CHAT_ACTION);
    ui->activityComboBox->addItem(tr("Image generation"), IMAGE_ACTION);
//    ui->activityComboBox->addItem(tr("Educational Chat Conversation")); // TODO: second arg
    ui->activityComboBox->addItem(tr("Writing a plot"), PLOT_ACTION);

    ui->activityComboBox->addItem(tr("Network Configuration"), NETWORK_CONFIG_ACTION);
    ui->activityComboBox->addItem(tr("Donate"), DONATE_ACTION);
    ui->activityComboBox->addItem(tr("About"), ABOUT_ACTION);

    ui->activityComboBox->setCurrentIndex(-1);

    displayWait();
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

    qDebug() << "FILE_NAME:" << fileName;

    bool ok = client()->auth().setKeyFile(fileName); // _appContext.openKeyFile(fileName, key, &err);

    // TODO: error and check if the file is correct

    if (!ok) {
        QMessageBox::warning(this, "error", "Unable to read the key file");
        displayError();
        return;
    }

    onKeySuccess();

    // do not put into the settings
//    QSettings settings;

//    // TODO: crypt the key
//    settings.setValue("oai/key", key);

}


void PageWelcomePage::on_openActivityButton_clicked()
{
    QString actionData = ui->activityComboBox->currentData().toString();
    openAction(actionData);
}

void PageWelcomePage::displaySuccess()
{
    ui->keyFileLabel->setText(tr("OpenAI API key loaded successfully"));
    ui->keyFileLabel->setStyleSheet("QLabel { color : green; }");
    ui->activityFrame->setEnabled(true);
    ui->activityFrame->setVisible(true);

    ui->browseKeyButton->setVisible(false);
    ui->setTheKeyEnvText->setVisible(false);
}

void PageWelcomePage::displayError()
{
    ui->keyFileLabel->setText(tr("Error: Failed to load OpenAI API key"));
    ui->keyFileLabel->setStyleSheet("QLabel { color : red; }");
    ui->activityFrame->setEnabled(false);
    ui->activityFrame->setVisible(false);

    ui->browseKeyButton->setVisible(true);
    ui->setTheKeyEnvText->setVisible(true);
}

void PageWelcomePage::displayWait()
{
    ui->keyFileLabel->setText(tr("Waiting for OpenAI API key to load..."));
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
    } else if (actionData == PLOT_ACTION) {
        emit openPlotAction();
    } else if (actionData == NETWORK_CONFIG_ACTION) {
        emit openNetworkConfigAction();
    }
}

void PageWelcomePage::onKeySuccess()
{
    // read other app context settings here
    QSettings settings;
    int32_t timeout = settings.value("oai/timeout", 30000).toInt(); // TODO: oaic::Manager::DEFAULT_TIMEOUT_MS

    (void)timeout; // TODO: _client->setTimeout(timeout);

    displaySuccess();
}

void PageWelcomePage::on_activityComboBox_currentIndexChanged(int index)
{
    Q_UNUSED(index)
    on_openActivityButton_clicked();
}

void PageWelcomePage::updateClient(oaic::Manager *client)
{
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    QString envKey("OPENAI_API_KEY");

    if (env.contains(envKey)) { // OPENAI_API_KEY
        bool ok = client->auth().setKeyEnv(envKey);

        if (ok) {
            onKeySuccess();
        } else {
            qDebug() << "AUTH ERROR";
            QMessageBox::warning(this, "OpenAI Key", "Please set OPENAI_API_KEY as an environment variable with your OpenAI API key");
        }
    } else {
        qDebug() << "AUTH ERROR";
        QMessageBox::warning(this, "OpenAI Key", "Please set OPENAI_API_KEY as an environment variable with your OpenAI API key");
    }
}

