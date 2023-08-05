/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef CHAT_CHARACTERMANAGER_H
#define CHAT_CHARACTERMANAGER_H

#include "Character.h"

#include <OrderedMap.h>

namespace chat {

class CharacterManager
{
public:
    static CharacterManager *instance();

    CharacterPtr character(int id) const;

    const OrderedMap<int, CharacterPtr> &characters() const;

    void select();

    bool insertOrUpdateCharacter(Character &character); // TODO: is not called

    bool deleteCharacter(int id);

private:

    OrderedMap<int, CharacterPtr> _characters;

private:
    CharacterManager();
    static CharacterManager *_instance;

};

} // namespace chat

#define gCharacters chat::CharacterManager::instance()

#endif // CHAT_CHARACTERMANAGER_H
