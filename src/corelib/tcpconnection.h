#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include "dglobal.h"
#include "ioobject.h"

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
    
    void read(QByteArray *buffer);
    bool timedRead(QByteArray *buffer, int timeout = 0);
    uint64_t write(const char * data, uint64_t size);
    void close();

    int status();

    enum Status {
        ReadOk = 0,
        ReadFail
    };

private:
    TcpConnectionPrivate *d;
    friend class TcpConnectionPrivate;
};

D_END_NAMESPACE

#endif //! TCPCONNECTION_H
