/****************************************************************************
**
** Copyright (C) 2013 Andre Oliveira
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
****************************************************************************/

#include "tcpserver.h"
#include "uvwrapper.h"
#include "daemon_p.h"
#include "tools.h"
#include "tcpconnection.h"
#include "tcpconnection_p.h"

#include "uv.h"

#include "qstringbuilder.h"

#include <assert.h>

#define TCPSERVER_DEBUG

#ifdef TCPSERVER_DEBUG
#define    debug() d_debug()
#endif

D_BEGIN_NAMESPACE

#define MAXCONNS 4

struct TcpServerPrivate 
{


    int max_conns;
    TcpServer *parent;
    uv_tcp_t uv_server;

    uint16_t port;
    HostAddress bind_address;

    int conns;
    bool listening;

    uv_mutex_t conntbl_mtx;
    uv_mutex_t enq_mtx;
    uv_mutex_t read_mtx;
    uv_mutex_t write_mtx;

    QHash<QByteArray, ConnectionData *> conntable;
    void enqueueConnection(uv_stream_t *server, uv_tcp_t *client);
    QByteArray getPeerNamePort(uv_tcp_t *client)
    {
        uvMutexLocker(&this->enq_mtx);
        struct sockaddr sa;
        int len;
        memset(&sa, 0x0, sizeof(sa));
        int r;
        r = uv_tcp_getsockname(client, &sa, &len);
        debug() << "getsock" << r;
        r = uv_tcp_getpeername(client, &sa, &len);
        debug() << "getpeer" << r;
        struct sockaddr_in sain = *(struct sockaddr_in *)&sa;

        QByteArray res;
        res += 
                HostAddress(&sa).toString().toLatin1() % ":" % 
                QByteArray::number(ntohs(sain.sin_port));
        if (res == ":0" || ntohs(sain.sin_port) <= 0) { 
            res.clear();
            debug() << "*** ERROR *** couldn't retrieve peer address or port";
        }

        return res;
    }

#if 0
    void addConnection(ConnectionData *cd)
    {
        uvMutexLocker(&this->conntbl_mtx);
        conntable.insert(cd->id, cd);
        ++conns;
    };
#endif

    void removeConnection(ConnectionData *cd)
    {
        uvMutexLocker(&this->conntbl_mtx);
        ConnectionData *c = conntable.take(cd->id);
        delete c;
        --conns;
    };

    static void handle_accept_cb(uv_stream_t *, int);
//    static void on_enqueue(uv_work_t *);
    static void on_close(uv_handle_t *);
};

#if 0
void
TcpServerPrivate::on_enqueue(uv_work_t *req)
{
    uv_tcp_t *client = (uv_tcp_t *)req->data;
    TcpServerPrivate *d = (TcpServerPrivate *)client->data;

    ConnectionData *cd = new ConnectionData;
    d->addConnection(cd);
    cd->id = d->getPeerNamePort(client);
    if (cd->id.isNull()) {
        uv_close((uv_handle_t *)client, 
                 &TcpServerPrivate::on_close);
        debug() << "failure initializing connection";
        return;
    }

    cd->uv_client = client;
    cd->uv_server = (uv_stream_t *)&d->uv_server;

    debug() << "Connection task" << cd->id;
    debug() << "table size" << d->conntable.size();
    d->parent->newConnection(new TcpConnection(d->parent, cd));
}
#endif

void 
TcpServerPrivate::enqueueConnection(uv_stream_t *server, uv_tcp_t *client)
{
    assert(client);
    assert(server);

    ConnectionData *cd = new ConnectionData;
//    addConnection(cd);
    cd->id = getPeerNamePort(client);
    if (cd->id.isNull()) {
        uv_close((uv_handle_t *)client, 
                 &TcpServerPrivate::on_close);
        debug() << "failure initializing connection";
        return;
    }

    cd->uv_client = client;
    cd->uv_server = (uv_stream_t *)server;

    debug() << "Connection task" << cd->id;
    debug() << "table size" << conntable.size();
    parent->newConnection(new TcpConnection(parent, cd));
}

TcpServer::TcpServer() : 
    d(new TcpServerPrivate)
{
    d->conns = 0;
    d->listening = false;
    d->parent = this;
    uv_mutex_init(&d->conntbl_mtx);
    uv_mutex_init(&d->enq_mtx);
}

TcpServer::~TcpServer() 
{ 
    uv_mutex_destroy(&d->enq_mtx);
    uv_mutex_destroy(&d->conntbl_mtx);
    delete d;
}

void
TcpServer::run() 
{ }

bool 
TcpServer::listen(const HostAddress &address, uint16_t port)
{
    d->port = port;
    d->bind_address = address;

    uv_loop_t *loop = defaultLoop()->uv_loop();
    uv_tcp_init(loop, &d->uv_server);

    struct sockaddr_in bind_addr = uv_ip4_addr(address.toString().toLatin1(),
                                               port);
    uv_tcp_bind(&d->uv_server, bind_addr);
    d->uv_server.data = this;
    int r = uv_listen((uv_stream_t *)&d->uv_server, 128,
                      &TcpServerPrivate::handle_accept_cb);
    if (r != 0) {
        debug() << "Listen error" << uv_err_name(uv_last_error(loop));
        return (d->listening = false);
    }

    uv_tcp_simultaneous_accepts(&d->uv_server, 1);
    return (d->listening = true);
}

void
TcpServerPrivate::handle_accept_cb(uv_stream_t *server, int status)
{
    assert(server);
    TcpServer *ts = (TcpServer *)server->data;
    
    if (ts->d->conns >= MAXCONNS) {
        debug() << "Too many tasks, no room to handle this one.";
        return;
    }

    //debug() << "Status " << status;
    //debug() << "Server pointer " << server;

    if (status == -1) {
        debug() << "Error on accept";
        return;
    }
    
    uv_tcp_t *client = (uv_tcp_t *)malloc(sizeof(uv_tcp_t));
    uv_tcp_init(uv_default_loop(), client);
    if (uv_accept(server, (uv_stream_t *)client) == 0) {
        ts->d->enqueueConnection(server, client);
    } else {
        uv_close((uv_handle_t *)client, &TcpServerPrivate::on_close);
        return;
    }

    //debug() << "Connection accepted";
}

bool 
TcpServer::isListening() const
{
    return d->listening;
}

bool
TcpServer::hasConnections() const
{ }

uint16_t
TcpServer::port() const
{
    return d->port;
}

HostAddress
TcpServer::address() const
{
    return d->bind_address;
}

void
TcpServer::closeConnection(ConnectionData * data)
{
    assert(data);
    assert(data->uv_client);
//    debug() << "last error:" << 
//        uv_last_error(defaultLoop()->uv_loop()).code;
    uv_close((uv_handle_t *) data->uv_client, 
             &TcpServerPrivate::on_close);
    debug() << "Connection Task:" << data->id << "finished";
    delete data;
//    d->removeConnection(data);
}

void
TcpServerPrivate::on_close(uv_handle_t *handle)
{
    free(handle);
}

void
TcpServer::setMaxConnections(int numConnections)
{
    d->max_conns = numConnections;
}

int
TcpServer::maxConnections() const
{
    d->max_conns;
}

D_END_NAMESPACE
