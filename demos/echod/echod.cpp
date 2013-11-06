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
    QByteArray *m_buffer = new QByteArray;
    c->timedRead(m_buffer, 5000); 

//    QByteArray *m_buffer = c->buffer();
    if (c->status() != TcpConnection::ReadOk) {
        debug() << "read failed";
        c->close();
        delete c;
        delete m_buffer;
        return;
    }

    debug() << "buffer" << m_buffer->size();
    debug() << "buffer" << "*** omitting data";

    //sleep(3);
    QByteArray reply("OK\n");
    uint64_t r = c->write(reply.data(), reply.size());

    debug() << "write result" << r;
    c->close();
    delete m_buffer;
}
