#ifndef CHAT_CHARACTERMANAGER_H
#define CHAT_CHARACTERMANAGER_H

#include "Character.h"

namespace chat {

class CharacterManager
{
public:
    CharacterManager();

    CharacterPtr character(int id) const;

    QMap<int, CharacterPtr> characters() const;

private:

    QMap<int, CharacterPtr> _characters;

};

} // namespace chat

#endif // CHAT_CHARACTERMANAGER_H
