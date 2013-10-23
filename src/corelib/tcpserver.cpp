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

static TcpServer *parent = 0;

#define MAXTASKS 4
struct TcpServerPrivate {
    uv_tcp_t server;

    uint16_t port;
    HostAddress bind_address;

    int curtask;
    bool listening;

    uv_mutex_t mtx;
    uv_work_t req[MAXTASKS];
    ConnectionData conns_databucket[MAXTASKS];

    void enqueue_connection(uv_tcp_t *client);

    static void handle_accept(uv_stream_t *, int);
    static void newconnection_cb(uv_work_t *req);
    static void connection_finished(uv_work_t *req, int status);
};

void
TcpServerPrivate::newconnection_cb(uv_work_t *req)
{
    ConnectionData *td = (ConnectionData *)req->data;
    parent->newConnection(new TcpConnection(parent, td));
}

void 
TcpServerPrivate::enqueue_connection(uv_tcp_t *client)
{
    uvMutexLocker(&parent->d->mtx);
    ++parent->d->curtask;

    ConnectionData *td = &conns_databucket[parent->d->curtask];
    td->clear();
    td->id = parent->d->curtask;
    td->client = client;
    req[parent->d->curtask].data = (void *)td;

    uv_queue_work(uv_default_loop(), 
                    &req[parent->d->curtask],
                    newconnection_cb,
                    connection_finished);

    debug() << "Connection spawned:" << td->id;
}

void
TcpServerPrivate::connection_finished(uv_work_t *req, int status)
{
    uvMutexLocker(&parent->d->mtx);
    --parent->d->curtask;

    ConnectionData *td = (ConnectionData *)req->data;
    debug() << "Connection finished: " << td->id;
}

TcpServer::TcpServer() : 
    d(new TcpServerPrivate)
{
    parent = this;
    d->curtask = 0;
    d->listening = false;
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
    uv_tcp_init(loop, &d->server);

    struct sockaddr_in bind_addr = uv_ip4_addr(address.toString().toLatin1(),
                                               port);
    uv_tcp_bind(&d->server, bind_addr);
    int r = uv_listen((uv_stream_t *)&d->server, 128,
                      &TcpServerPrivate::handle_accept);
    if (r != 0) {
        debug() << "Listen error" << ::uv_err_name(uv_last_error(loop));
        return (d->listening = false);
    }

    uv_tcp_simultaneous_accepts(&d->server, 1);
    return (d->listening = true);
}

void
TcpServerPrivate::handle_accept(uv_stream_t *server, int status)
{
    assert(server);
    if (parent->d->curtask >= MAXTASKS) {
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
    if (uv_accept((uv_stream_t *)&parent->d->server,
                  (uv_stream_t *)client) == 0) {
        parent->d->enqueue_connection(client);
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
