#include "tcpd.h"

#include <TcpConnection>

#include <qt/qdebug.h>

#define debug() qDebug() << Q_FUNC_INFO

Tcpd::Tcpd() : TcpServer() { }

Tcpd::~Tcpd() { }

void 
Tcpd::run()
{
    debug() << "Starting...";
    debug() << "Listening on" << port();
}

void 
Tcpd::newConnection(TcpConnection *c)
{
    debug() << "Master I'm here to serve you";
    // by the and, will call readFinished();
    c->read(); 
}

void 
Tcpd::readFinished(TcpConnection *c)
{ 
    debug() << "read finished";
    debug() << "buffer" << c->buffer()->data();

    QByteArray reply("OK\n");
    uint64_t r = c->write(reply.data(), reply.size());

    debug() << "write result" << r;
    //c->close();
}

void 
Tcpd::writeFinished(TcpConnection *c)
{ 
    debug() << "write finished";
}
