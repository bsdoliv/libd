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
    TcpConnection(TcpServer * parent = 0, ConnectionData * data = 0);
    virtual ~TcpConnection();
    
    uint64_t read(char * data);
    uint64_t write(char * data, uint64_t size);
    ConnectionData *connectionData();
    void setConnectionData(ConnectionData * cdata);

#if 0
protected:
    virtual void readFinished() = 0;
    virtual void writeFinished() = 0;
#endif

private:
    TcpConnectionPrivate *d;
};

D_END_NAMESPACE

#endif //! TCPCONNECTION_H
