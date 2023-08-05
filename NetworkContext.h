/*
* Copyright (c) 2023, Asianirish, asianirish@gmail.com
* 
* This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef NETWORKCONTEXT_H
#define NETWORKCONTEXT_H


class NetworkContext
{
public:
    static const int DEFAULT_TIMEOUT;
    NetworkContext();

    int timeout() const;
    void setTimeout(int newTimeout);

private:
    int _timeout;
};

#endif // NETWORKCONTEXT_H
