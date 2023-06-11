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
