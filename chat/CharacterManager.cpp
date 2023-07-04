#include "CharacterManager.h"

#include <QSqlQuery>

namespace chat {

CharacterManager::CharacterManager()
{

}

CharacterPtr CharacterManager::character(int id) const
{
    return _characters.value(id);
}

QMap<int, CharacterPtr> CharacterManager::characters() const
{
    return _characters;
}

void CharacterManager::load()
{
    QSqlQuery query("SELECT id, name, message, useNameInMessage FROM characters ORDER BY name");

    while (query.next()) { // TODO: error?
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString message = query.value(2).toString();
        bool useNameInMessage = query.value(3).toBool();

        // TODO: create and add in a seperate function
        CharacterPtr character = CharacterPtr(new Character(name, message, useNameInMessage));
        character->setId(id); // TODO: in a constructor

        _characters.insert(id, character);
    }
}

} // namespace chat
