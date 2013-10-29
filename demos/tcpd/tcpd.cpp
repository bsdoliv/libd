#include "tcpd.h"

#include <TcpConnection>

#include <qt/qdebug.h>

#include <unistd.h>

#define debug() qDebug() << __FILE__ << ":" << __LINE__ << Q_FUNC_INFO

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
    //debug() << "new connection";
    QByteArray *m_buffer = new QByteArray;
    c->read(m_buffer); 
    new Connection(c);
}

void 
Connection::readFinished(TcpConnection *c)
{ 
    TcpServer::readLock();
//    debug() << "read finished";
    //debug() << "status" << c->status();
    QByteArray *m_buffer = c->buffer();
    if (c->status() != TcpConnection::ReadOk) {
        c->close();
//        delete c;
        delete m_buffer;
        return;
    }

    debug() << "buffer" << m_buffer->size();
    debug() << "buffer" << "*** omitting data";

    //sleep(3);
    QByteArray reply("OK\n");
    uint64_t r = c->write(reply.data(), reply.size());

//    debug() << "write result" << r;
    //c->close();
    delete m_buffer;
}

void 
Connection::writeFinished(TcpConnection *c)
{ 
    //debug() << "write finished";
    c->close();
//    delete c;
}
