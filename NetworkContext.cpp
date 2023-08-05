/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#include "NetworkContext.h"

const int NetworkContext::DEFAULT_TIMEOUT = 30000;

NetworkContext::NetworkContext() : _timeout(DEFAULT_TIMEOUT)
{

}

int NetworkContext::timeout() const
{
    return _timeout;
}

void NetworkContext::setTimeout(int newTimeout)
{
    _timeout = newTimeout;
}
