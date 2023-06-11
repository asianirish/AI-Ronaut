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
