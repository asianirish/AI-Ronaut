#include "ChatSessionWidget.h"
#include "ui_ChatSessionWidget.h"

#include "chat/SessionManager.h"
#include "chat/SessionItem.h"

ChatSessionWidget::ChatSessionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatSessionWidget)
{
    ui->setupUi(this);

    ui->sessionListWidget->setSortingEnabled(true);

    auto sm = chat::SessionManager::instance();
    connect(sm, &chat::SessionManager::sessionCreated, this, &ChatSessionWidget::onSessionCreated);
}

ChatSessionWidget::~ChatSessionWidget()
{
    delete ui;
}

void ChatSessionWidget::onSessionCreated(const QString &sessionId)
{
    auto sm = chat::SessionManager::instance();
    auto session = sm->session(sessionId);

    chat::SessionItem *item = new chat::SessionItem();
    item->setSessionData(session->data());

    ui->sessionListWidget->insertItem(0, item);

    ui->sessionListWidget->sortItems(Qt::DescendingOrder);

    ui->sessionListWidget->setCurrentItem(item);
}

void ChatSessionWidget::on_sessionListWidget_itemActivated(QListWidgetItem *item)
{
    chat::SessionItem *sessionItem = dynamic_cast<chat::SessionItem *>(item);

    if (sessionItem) {

        // TODO: gSessionManager->selectSession(sessionId);
    }
}


void ChatSessionWidget::on_sessionListWidget_currentTextChanged(const QString &currentText)
{
    ui->sessionNameEdit->setText(currentText);
}

