#ifndef ECHOD_H
#define ECHOD_H

#include <TcpServer>
#include <TcpConnection>

class Echod : public TcpServer
{
public:
    Echod();
    virtual ~Echod();

    void run();
    void newConnection(TcpConnection *c);
};

#endif // !ECHOD_H
