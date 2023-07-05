#include "CharacterManager.h"

#include <QSqlQuery>
#include <QSqlError>

namespace chat {

CharacterManager *CharacterManager::_instance = nullptr;

CharacterManager *CharacterManager::instance()
{
    if (_instance == nullptr) {
        _instance = new CharacterManager();
    }

    return _instance;
}

CharacterPtr CharacterManager::character(int id) const
{
    return _characters.value(id);
}

const OrderedMap<int, CharacterPtr> &CharacterManager::characters() const
{
    return _characters;
}

void CharacterManager::select()
{
    _characters.clear();

    QSqlQuery query("SELECT id, name, message, useNameInMessage FROM characters ORDER BY name");

    while (query.next()) { // TODO: error?
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString message = query.value(2).toString();
        bool useNameInMessage = query.value(3).toBool();

        // TODO: create and add in a seperate function
        CharacterPtr character = CharacterPtr(new Character(name, message, useNameInMessage));
        character->setId(id); // TODO: in a constructor

        qDebug() << "CHARACTER:" << character->id() << character->name() << character->message() << character->useNameInMessage();

        _characters.insert(id, character);
    }
}

bool CharacterManager::insertOrUpdateCharacter(Character &character)
{
    auto ret = character.save();
    select();
    return ret;
}

bool CharacterManager::deleteCharacter(int id)
{
    QSqlQuery query(QSqlDatabase::database());
    query.prepare("DELETE FROM characters WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error deleting row by name:" << query.lastError();
        return false;
    }

    select();
    return true;
}


CharacterManager::CharacterManager()
{

}

} // namespace chat
