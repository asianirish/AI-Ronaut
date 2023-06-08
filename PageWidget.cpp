#include "PageWidget.h"

#include <oaic/Manager.h>

#include <QMessageBox>
#include <QProcessEnvironment>

PageWidget::PageWidget(QWidget *parent)
    : QWidget{parent},
    _client(new oaic::Manager(this))
{

}

oaic::Manager *PageWidget::client() const
{
    return _client;
}

void PageWidget::initClient()
{
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    QString envKey("OPENAI_API_KEY");

    if (env.contains(envKey)) { // OPENAI_API_KEY
        bool ok = _client->auth().setKeyEnv(envKey);

        if (!ok) {
            qDebug() << "AUTH ERROR";
            QMessageBox::warning(this, "OpenAI Key", "Please set OPENAI_API_KEY as an environment variable with your OpenAI API key");
        }
    } else {
        qDebug() << "AUTH ERROR";
        QMessageBox::warning(this, "OpenAI Key", "Please set OPENAI_API_KEY as an environment variable with your OpenAI API key");
    }
    synchronizeClient(_client);
}
