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

    gSessions->select();
    auto lst = gSessions->sessions();

    for (auto &session : lst) {
        chat::SessionItem *item = new chat::SessionItem();
        item->setSessionId(session->id());
        ui->sessionListWidget->addItem(item);
    }

    ui->sessionListWidget->sortItems(Qt::DescendingOrder);

    connect(gSessions, &chat::SessionManager::sessionCreated, this, &ChatSessionWidget::onSessionCreated);
    connect(gSessions, &chat::SessionManager::sessionDeleted, this, &ChatSessionWidget::onSessionDeleted);
}

ChatSessionWidget::~ChatSessionWidget()
{
    delete ui;
}

void ChatSessionWidget::synchronizeCurrentSession()
{
    qDebug() << "CHAT SESSION SESSION ID:" << pageContext()->currentSessionId();
    qWarning() << "ChatSessionWidget::synchronize should not be called (?)";
}

QModelIndexList ChatSessionWidget::findModelIndexesBySessionId(const QString &sessionId)
{
    QModelIndex start = ui->sessionListWidget->model()->index(0, 0);
    return ui->sessionListWidget->model()->match(start, chat::SessionItem::SessionIdRole, sessionId, 1, Qt::MatchExactly);
}

chat::SessionItem* ChatSessionWidget::findItemBySessionId(const QString &sessionId)
{
    QModelIndexList indexes = findModelIndexesBySessionId(sessionId);
    if (!indexes.isEmpty()) {
        return static_cast<chat::SessionItem*>(ui->sessionListWidget->itemFromIndex(indexes.first()));
    }
    return nullptr;
}

void ChatSessionWidget::onSessionCreated(int pageIndex, const QString &sessionId)
{
    // TODO: NOT every session creation should cause this page current session changing!
    auto session = gSessions->session(sessionId);

    chat::SessionItem *item = new chat::SessionItem();
    item->setSessionId(session->id());

    if (pageContext() && pageContext()->pageIndex() != pageIndex) {
        ui->sessionListWidget->addItem(item);
        ui->sessionListWidget->sortItems(Qt::DescendingOrder);
    } else {
        ui->sessionListWidget->insertItem(0, item);
        ui->sessionListWidget->sortItems(Qt::DescendingOrder);
        ui->sessionListWidget->setCurrentItem(item);
    }
}

void ChatSessionWidget::on_sessionListWidget_itemActivated(QListWidgetItem *item)
{
    chat::SessionItem *sessionItem = dynamic_cast<chat::SessionItem *>(item);

    if (sessionItem) {
        auto sessionId = sessionItem->sessionId();
        qDebug() << "SESSION NAME:" << sessionItem->name() << sessionId;
        changeSessionId(sessionId);
        emit currentSessionChanged();
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

    auto item = findItemBySessionId(currentSessionId());

    auto sessionItem = dynamic_cast<chat::SessionItem *>(item);

    if (sessionItem) {
        sessionItem->setSessionId(currentSessionId());

        // changes the list item's text
        sessionItem->setText(name);
    }
}


void ChatSessionWidget::on_sessionNameEdit_textEdited(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->applyEditedButton->setEnabled(true);
}


void ChatSessionWidget::on_applyEditedButton_clicked()
{
    auto name = ui->sessionNameEdit->text();
    onRenameSession(name);
    ui->applyEditedButton->setEnabled(false);
}


void ChatSessionWidget::on_saveButton_clicked()
{
    gSessions->save(currentSessionId());
}


void ChatSessionWidget::on_deleteButton_clicked()
{
    // TODO: do not delete the current session (double clicked)
    // TODO: emit to other tabs
    auto item = ui->sessionListWidget->currentItem();
    auto sessionItem = dynamic_cast<chat::SessionItem *>(item);
    bool deletePermanently = ui->deletePermanentlyBox->isChecked();

    if (!sessionItem) {
        return;
    }

    auto sessionId = sessionItem->sessionId();

    qDebug() << "DELETING SESSION" << sessionId;
    gSessions->deleteSession(pageContext()->pageIndex(), sessionId, deletePermanently); 
}

void ChatSessionWidget::onSessionDeleted(int pageIndex, const QString sessionId)
{
    auto item = findItemBySessionId(sessionId);

    ui->sessionListWidget->removeItemWidget(item);
    delete item;

    if (pageContext() &&
        pageIndex == pageContext()->pageIndex() &&
        sessionId == pageContext()->currentSessionId()) {

        on_newSessionButton_clicked();
    }
}


void ChatSessionWidget::on_newSessionButton_clicked()
{
    QString sessionId = gSessions->createSession(pageContext()->pageIndex());

    pageContext()->setCurrentSessionId(sessionId);
// TODO:    emit sessionChaged();
}

