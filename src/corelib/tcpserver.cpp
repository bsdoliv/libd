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

struct TcpServerPrivate {
    TcpServer *parent;
    uv_tcp_t uv_server;

    uint16_t port;
    HostAddress bind_address;

    int conns;
    bool listening;

    uv_mutex_t mtx;
//    ConnectionData conns_databucket[MAXTASKS];

    QHash<QByteArray, ConnectionData *> conntable;
    void enqueueConnection(uv_stream_t *server, uv_tcp_t *client);
    ConnectionData * addConnection(uv_tcp_t *client)
    {
        struct sockaddr sa;
//        char addr[128];
        int len;
        memset(&sa, 0x0, sizeof(sa));
//        memset(addr, 0x0, 128);
        int r;
        r = uv_tcp_getsockname(client, &sa, &len);
        debug() << "getsock" << r;
        r = uv_tcp_getpeername(client, &sa, &len);
        debug() << "getpeer" << r;
        struct sockaddr_in sain = *(struct sockaddr_in *)&sa;
//        uv_ip4_name(&sain, addr, sizeof(addr));

        HostAddress peer_address(&sa);
        QByteArray peer_port = QByteArray::number(ntohs(sain.sin_port));
//        debug() << "peer_address"  << peer_address;
//        debug() << "peer_port"  << peer_port;
        if (peer_address.isNull() || peer_port == "0") {
            debug() << "*** ERROR *** couldn't retrieve peer address or port";
            return 0;
        }

        ConnectionData *cd = new ConnectionData;
        cd->id = peer_address.toString().toLatin1() % ":" % peer_port;
        cd->uv_client = client;
        cd->uv_server = (uv_stream_t *)&this->uv_server;
        conntable.insert(cd->id, cd);
        ++conns;
        return cd;
    };

    void removeConnection(ConnectionData *cd)
    {
        uvMutexLocker(&this->mtx);
        ConnectionData *c = conntable.take(cd->id);
        //delete c;
        --conns;
    };

    static void handle_accept_cb(uv_stream_t *, int);
    static void on_enqueue(uv_work_t *);
    static void on_enqueue_finished(uv_work_t *, int);
    static void on_close(uv_handle_t *);
};

void
TcpServerPrivate::on_enqueue(uv_work_t *req)
{
    uv_tcp_t *client = (uv_tcp_t *)req->data;
    assert(client);
    TcpServerPrivate *d = (TcpServerPrivate *)client->data;
    assert(d);
    uvMutexLocker(&d->mtx);
    ConnectionData *cd = d->addConnection(client);
    if (cd == 0) {
        uv_close((uv_handle_t *)client, 
                 &TcpServerPrivate::on_close);
        debug() << "failure initializing connection";
        return;
    }

    debug() << "Connection task" << cd->id;
    debug() << "table size" << d->conntable.size();
    d->parent->newConnection(new TcpConnection(d->parent, cd));
}

void 
TcpServerPrivate::enqueueConnection(uv_stream_t *server, uv_tcp_t *client)
{
    uv_work_t *req = (uv_work_t *)malloc(sizeof(uv_work_t));
    client->data = this;
    req->data = client;

    uv_queue_work(parent->defaultLoop()->uv_loop(),
                  req,
                  on_enqueue,
                  on_enqueue_finished);
}

TcpServer::TcpServer() : 
    d(new TcpServerPrivate)
{
    d->conns = 0;
    d->listening = false;
    d->parent = this;
    uv_mutex_init(&d->mtx);
}

TcpServer::~TcpServer() 
{ 
    uv_mutex_destroy(&d->mtx);
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
    d->removeConnection(data);
}

void
TcpServerPrivate::on_close(uv_handle_t *handle)
{
//    free(handle);
}

void
TcpServerPrivate::on_enqueue_finished(uv_work_t *handle, int status)
{
//    free(handle);
}

D_END_NAMESPACE
