#include "CharacterManager.h"

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

} // namespace chat
