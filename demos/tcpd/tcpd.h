#ifndef TCPD_H
#define TCPD_H

#include <TcpServer>
#include <TcpConnection>

class Tcpd : public TcpServer
{
public:
    Tcpd();
    virtual ~Tcpd();

    class Connection : public TcpConnection
    {
    public:
        Connection(TcpConnection *c) : TcpConnection(c) 
        {
            this = c;
        }
        void readFinished(TcpConnection *c);
        void writeFinished(TcpConnection *c);
    };
    void run();
    void newConnection(TcpConnection *c);
};

#endif // !TCPD_H
