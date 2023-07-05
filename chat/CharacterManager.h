#ifndef CHAT_CHARACTERMANAGER_H
#define CHAT_CHARACTERMANAGER_H

#include "Character.h"

namespace chat {

class CharacterManager
{
public:
    static CharacterManager *instance();

    CharacterPtr character(int id) const;

    const OrderedMap<int, CharacterPtr> &characters() const;

    void load();

private:

    OrderedMap<int, CharacterPtr> _characters;

private:
    CharacterManager();
    static CharacterManager *_instance;

};

} // namespace chat

#define gCharacters chat::CharacterManager::instance()

#endif // CHAT_CHARACTERMANAGER_H
