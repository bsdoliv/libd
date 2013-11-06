#include "echod.h"

#include <TcpConnection>

#include <qt/qdebug.h>

#include <unistd.h>

#define debug() qDebug() << __FILE__ << ":" << __LINE__ << Q_FUNC_INFO

Echod::Echod() : TcpServer() { }

Echod::~Echod() { }

void 
Echod::run()
{
    debug() << "Starting...";
    debug() << "Listening on" << port();
}

void 
Echod::newConnection(TcpConnection *c)
{
    debug() << "new connection";
    QByteArray request;
    request.clear();
    c->timedRead(&request, 5000); 

    if (c->status() != TcpConnection::ReadOk) {
        debug() << "read failed";
        return cleanup(c);
    }

    debug() << "buffer" << "*** omitting data";
    debug() << "buffer size" << request.size();

    uint64_t r = c->write(request.data(), request.size());

    debug() << "write result" << r;
    return cleanup(c);
}

void
Echod::cleanup(TcpConnection *c)
{
    c->close();
    delete c;
    c = 0;
}
