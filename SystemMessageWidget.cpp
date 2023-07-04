#include "SystemMessageWidget.h"
#include "ui_SystemMessageWidget.h"

#include "chat/SessionManager.h"
#include "chat/Character.h"

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

    if (index < 0) {
        QString name = ui->characterBox->currentText();
        QString message = ui->textEdit->toPlainText();

        return chat::Character(name, message);
    }

    qDebug() << "CHARACTER INDEX:" << index;
    auto character = _model->character(index);
    qDebug() << "CHARACTER:" << character.name() << character.message();
    return character;
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

void SystemMessageWidget::initCharacterList()
{
    _model = new chat::CharactersModel(this);
    
    ui->characterBox->setModel(_model);
    ui->characterBox->setModelColumn(1);
    
    ui->characterBox->setCurrentIndex(-1);

}

void SystemMessageWidget::on_characterBox_currentIndexChanged(int index)
{
    if (pageContext()) {
        auto character = _model->character(index);
        ui->textEdit->setText(character.message());

        auto sessionId = pageContext()->currentSessionId();

        qDebug() << "CHARACTER_BOX: SESSION ID:" << sessionId;

        auto session = gSessions->session(sessionId);

        qDebug() << "CHARACTER_BOX: CHARACTER:" << character.name() << character.message();

        session->setCharacter(character);
    }
}


void SystemMessageWidget::on_saveCharacterButton_clicked()
{
    QString name(ui->characterBox->currentText());
    QString message(ui->textEdit->toPlainText());

    _model->insertOrReplaceRecord(name, message); // TODO: useNameInMessage

    ui->characterBox->setCurrentText(name);
    ui->textEdit->setText(message);

    int index = ui->characterBox->findText(name);
    if (index != -1) {
        ui->characterBox->setCurrentIndex(index);
    }
}


void SystemMessageWidget::on_deleteCharacterButton_clicked()
{
    QString name(ui->characterBox->currentText());

    _model->removeRowByName(name);
    
    ui->characterBox->setCurrentIndex(-1);
    ui->textEdit->clear();
}


void SystemMessageWidget::on_clearButton_clicked()
{
    ui->characterBox->clearEditText();
    ui->textEdit->clear();
}

