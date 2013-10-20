#ifndef TCPD_H
#define TCPD_H

#include <TcpServer>

class Tcpd : public TcpServer
{
public:
    Tcpd();
    virtual ~Tcpd();
    void run();
    void newConnection();
//    void handleRequest(const std::string &request, std::string *reply);
};

#endif // !TCPD_H
