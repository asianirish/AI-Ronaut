#include "SystemMessageWidget.h"
#include "ui_SystemMessageWidget.h"

#include "chat/SessionManager.h"
#include "chat/Character.h"
#include "chat/CharacterManager.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

SystemMessageWidget::SystemMessageWidget(QWidget *parent) :
    ChatToolWidget(parent),
    ui(new Ui::SystemMessageWidget)
{
    ui->setupUi(this);

    initCharacterList();
}

SystemMessageWidget::~SystemMessageWidget()
{
    delete ui;
}

chat::Character SystemMessageWidget::character() const
{
    int index = ui->characterBox->currentIndex();
    QString message = ui->textEdit->toPlainText();

    if (index < 0) {
        QString name = ui->characterBox->currentText();

        return chat::Character(name, message);
    }

    int characterId = ui->characterBox->currentData().toInt();
    auto pCharacter = gCharacters->character(characterId);

    pCharacter->setMessage(message);

    if (pCharacter) {
        return *pCharacter;
    }

    return chat::Character();
}

void SystemMessageWidget::synchronizeCurrentSession()
{
    auto sessionId = pageContext()->currentSessionId();

    qDebug() << "SYSTEM MESSAGE SESSION ID:" << sessionId;

    auto session = gSessions->session(sessionId);
//    auto msg = session->systemMessage();
    auto character = session->character();

    qDebug() << "SYSTEM MESSAGE:" << character.fullMessage();

    ui->textEdit->setText(character.message());
    ui->characterBox->setEditText(character.name());
}

void SystemMessageWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    ui->textEdit->setFocus();
}

void SystemMessageWidget::initCharacterList(int selectCharacter)
{
    ui->characterBox->clear();
    gCharacters->select();

    auto characters = gCharacters->characters();

    ui->characterBox->blockSignals(true);
    for (auto &character : characters) {
        ui->characterBox->addItem(character->name(), character->id());
    }
    ui->characterBox->blockSignals(false);
    
    if (selectCharacter) {
        int index = ui->characterBox->findData(selectCharacter);
        ui->characterBox->setCurrentIndex(index);
    } else {
        ui->characterBox->setCurrentIndex(-1);
    }
}

void SystemMessageWidget::on_characterBox_currentIndexChanged(int index)
{
    if (index < 0) {
        return;
    }

    if (pageContext()) {

        int characterId = ui->characterBox->currentData().toInt();
        auto pCharacter = gCharacters->character(characterId);

        if (!pCharacter) {
            return;
        }

        ui->textEdit->setText(pCharacter->message());

        auto sessionId = pageContext()->currentSessionId();

        qDebug() << "CHARACTER_BOX: SESSION ID:" << sessionId;

        auto session = gSessions->session(sessionId);

        qDebug() << "CHARACTER_BOX: CHARACTER:" << pCharacter->name() << pCharacter->message();

        session->setCharacter(*pCharacter);
    }
}


void SystemMessageWidget::on_saveCharacterButton_clicked()
{
    auto character = this->character();
    character.save();
    initCharacterList(character.id());
}


void SystemMessageWidget::on_deleteCharacterButton_clicked()
{
    int characterId = ui->characterBox->currentData().toInt();

    gCharacters->deleteCharacter(characterId);
    
    ui->characterBox->setCurrentIndex(-1);
    ui->textEdit->clear();

    initCharacterList();
}


void SystemMessageWidget::on_clearButton_clicked()
{
    ui->characterBox->setCurrentIndex(-1);
    ui->characterBox->clearEditText();
    ui->textEdit->clear();
}

