#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include "dglobal.h"

#include <inttypes.h>

D_BEGIN_NAMESPACE

class ConnectionData;
class TcpServer;
struct TcpConnectionPrivate;
class TcpConnection
{
public:
    TcpConnection(TcpServer * parent, ConnectionData * data = 0);
    virtual ~TcpConnection();
    
    void read();
    uint64_t write(const char * data, uint64_t size);
    void close();

    QByteArray *buffer();

private:
    TcpConnectionPrivate *d;
    friend class TcpConnectionPrivate;
};

D_END_NAMESPACE

#endif //! TCPCONNECTION_H
