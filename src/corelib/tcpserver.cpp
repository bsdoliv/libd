#include "tcpserver.h"
#include "uvwrapper.h"
#include "daemon_p.h"
#include "tools.h"
#include "tcpconnection.h"
#include "tcpconnection_p.h"

#include "uv.h"

#include "qqueue.h"

#include <assert.h>

#define TCPSERVER_DEBUG

#ifdef TCPSERVER_DEBUG
#define    debug() d_debug()
#endif

D_BEGIN_NAMESPACE

#define MAXTASKS 4
struct TcpServerPrivate {
    TcpServer *parent;
    uv_tcp_t uv_server;

    uint16_t port;
    HostAddress bind_address;

    int curtask;
    bool listening;

    uv_mutex_t mtx;
    uv_work_t req[MAXTASKS];
    ConnectionData conns_databucket[MAXTASKS];

    void enqueueConnection(uv_stream_t *server, uv_tcp_t *client);
    static void handle_accept_cb(uv_stream_t *, int);
    static void newconnection_cb(uv_work_t *req);
    static void connection_finished_cb(uv_work_t *req, int status);
};

void
TcpServerPrivate::newconnection_cb(uv_work_t * req)
{
#if 0
    ConnectionData *td = (ConnectionData *)req->data;
    TcpServer *ts = (TcpServer *)td->tcpserver;
    ts->newConnection(new TcpConnection(ts, td));
#endif
}

void 
TcpServerPrivate::enqueueConnection(uv_stream_t *server, uv_tcp_t *client)
{
    uvMutexLocker(&parent->d->mtx);
    ++curtask;

    ConnectionData *td = &conns_databucket[curtask];
    td->clear();
    td->id = curtask;
    td->uv_client = client;
    td->uv_server = server;
//    req[curtask].data = (void *)td;

//    ConnectionData *td = (ConnectionData *)req->data;
//    TcpServer *ts = (TcpServer *)td->tcpserver;
    parent->newConnection(new TcpConnection(parent, td));
#if 0
    uv_queue_work(uv_default_loop(), 
                    &req[curtask],
                    newconnection_cb,
                    connection_finished_cb);

    debug() << "Connection spawned:" << td->id;
#endif
}

void
TcpServerPrivate::connection_finished_cb(uv_work_t *req, int status)
{
#if 0
    ConnectionData *td = (ConnectionData *)req->data;
    TcpServer *ts = (TcpServer *)td->tcpserver;

    uvMutexLocker(&ts->d->mtx);
    --ts->d->curtask;

    debug() << "Connection finished: " << td->id;
#endif
}

TcpServer::TcpServer() : 
    d(new TcpServerPrivate)
{
    d->curtask = 0;
    d->listening = false;
    d->parent = this;
}

TcpServer::~TcpServer() 
{ 
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
        debug() << "Listen error" << ::uv_err_name(uv_last_error(loop));
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
    
    if (ts->d->curtask >= MAXTASKS) {
        debug() << "Too many tasks, no room to handle this one.";
        return;
    }

    debug() << "Status " << status;
    debug() << "Server pointer " << server;

    if (status == -1) {
        debug() << "Error on accept";
        return;
    }
    
    uv_tcp_t *client = (uv_tcp_t *)malloc(sizeof(uv_tcp_t));
    uv_tcp_init(uv_default_loop(), client);
    if (uv_accept((uv_stream_t *)server,
                  (uv_stream_t *)client) == 0) {
        ts->d->enqueueConnection(server, client);
    } else {
        uv_close((uv_handle_t *)client, NULL);
        return;
    }

    debug() << "Connection accepted";
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

D_END_NAMESPACE
