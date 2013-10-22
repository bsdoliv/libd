#ifndef TCPD_H
#define TCPD_H

#include <TcpServer>

class Tcpd : public TcpServer
{
public:
    Tcpd();
    virtual ~Tcpd();
    void run();
    void newConnection(TcpConnection *c);
};

#endif // !TCPD_H
