/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef CHAT_USERMESSAGE_H
#define CHAT_USERMESSAGE_H

#include "Message.h"

namespace chat {

class UserMessage : public Message
{
public:
    UserMessage();
    
    ROLE role() const override;
};

} // namespace chat

#endif // CHAT_USERMESSAGE_H
