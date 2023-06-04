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
    // TODO: initialize the sessino list from gSessions

    connect(gSessions, &chat::SessionManager::sessionCreated, this, &ChatSessionWidget::onSessionCreated);
}

ChatSessionWidget::~ChatSessionWidget()
{
    delete ui;
}

void ChatSessionWidget::updateCurrentSession(const QString &sessionId)
{
    Q_UNUSED(sessionId);
    qWarning() << "ChatSessionWidget::updateCurrentSession should not be called";
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

