/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef CHAT_SYSTEMMESSAGE_H
#define CHAT_SYSTEMMESSAGE_H

#include "Message.h"

namespace chat {

class SystemMessage : public Message
{
public:
    SystemMessage();
    
    ROLE role() const override;
};

} // namespace chat

#endif // CHAT_SYSTEMMESSAGE_H
