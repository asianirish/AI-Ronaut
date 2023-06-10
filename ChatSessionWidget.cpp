#include "ChatSessionWidget.h"
#include "ui_ChatSessionWidget.h"

#include "chat/SessionManager.h"
#include "chat/SessionItem.h"

ChatSessionWidget::ChatSessionWidget(QWidget *parent) :
    ChatToolWidget(parent),
    ui(new Ui::ChatSessionWidget)
{
    ui->setupUi(this);

    ui->sessionListWidget->setSortingEnabled(true);

    auto lst = gSessions->sessions();

    for (auto session : lst) {
        chat::SessionItem *item = new chat::SessionItem();
        item->setSessionData(session->data());
        ui->sessionListWidget->addItem(item);
    }

    ui->sessionListWidget->sortItems(Qt::DescendingOrder);

    connect(gSessions, &chat::SessionManager::sessionCreated, this, &ChatSessionWidget::onSessionCreated);
}

ChatSessionWidget::~ChatSessionWidget()
{
    delete ui;
}

void ChatSessionWidget::synchronizeCurrentSession(const QString &sessionId)
{
    Q_UNUSED(sessionId);
    qWarning() << "ChatSessionWidget::synchronize should not be called";
}

void ChatSessionWidget::onSessionCreated(const QString &sessionId)
{
    // TODO: NOT every session creation should cause this page current session changing!
    auto session = gSessions->session(sessionId);

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


void ChatSessionWidget::on_saveAsTextFileButton_clicked()
{
    gSessions->saveAsTextFile(currentSessionId());
}

void ChatSessionWidget::onRenameSession(const QString &name)
{
    auto session = gSessions->session(currentSessionId());

    session->setName(name);
    ui->sessionNameEdit->setText(session->name());

    auto item = ui->sessionListWidget->currentItem();
    auto sessionItem = dynamic_cast<chat::SessionItem *>(item);

    if (sessionItem) {
        auto sd = sessionItem->sessionData();
        sd.name = name;
        sessionItem->setSessionData(sd);

        // changes the list item's text
        sessionItem->setText(name);
    }
}

