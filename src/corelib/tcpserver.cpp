#include "tcpserver.h"
#include "uvwrapper.h"
#include "daemon_p.h"

#include "uv.h"

#include "qdebug.h"

#include <assert.h>

#define TCPSERVER_DEBUG

#ifdef TCPSERVER_DEBUG
#define    debug() qDebug() << Q_FUNC_INFO
#endif

D_BEGIN_NAMESPACE

static TcpServer *parent = 0;

#define MAXTASKS 4

struct TaskData {
    int id;
    uv_buf_t buf;
    ssize_t bufsize;
    uv_stream_t *client;
};

struct TcpServerPrivate {
    uint16_t port;
    HostAddress bind_address;
    uv_tcp_t server;
    int curtask;
    uv_mutex_t mtx;
    uv_work_t req[MAXTASKS];
    TaskData databucket[MAXTASKS];
    bool listening;

    static uv_buf_t alloc_buffer(uv_handle_t *handle, size_t suggested_size);
    static void handle_accept(uv_stream_t *, int);
    static void read_socket(uv_stream_t *, ssize_t, uv_buf_t);

    void spawnRequestHandlerTask(uv_stream_t *client);
    static void requestHandlerTask(uv_work_t *req);
    static void taskFinished(uv_work_t *req, int status);
};

void 
TcpServerPrivate::spawnRequestHandlerTask(uv_stream_t *client)
{
    uvMutexLocker(&parent->d->mtx);
    ++parent->d->curtask;

    TaskData *td = &databucket[parent->d->curtask];
    memset(td, 0x0, sizeof(*td));
    td->id = parent->d->curtask;
    td->client = client;
    req[parent->d->curtask].data = (void *)td;

    uv_queue_work(uv_default_loop(), 
                    &req[parent->d->curtask],
                    requestHandlerTask,
                    taskFinished);

    debug() << "Task spawned:" << td->id;
}

void
TcpServerPrivate::taskFinished(uv_work_t *req, int status)
{
    uvMutexLocker(&parent->d->mtx);
    --parent->d->curtask;

    TaskData *td = (TaskData *)req->data;
    debug() << "Task finished: " << td->id;
}

void
TcpServerPrivate::requestHandlerTask(uv_work_t *req)
{
    TaskData *td = (TaskData *)req->data;
    uv_read_start((uv_stream_t *)td->client,
                  &TcpServerPrivate::alloc_buffer,
                  &TcpServerPrivate::read_socket);
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

    struct sockaddr_in bind_addr = uv_ip4_addr(address.toString().toLatin1(), port);
    uv_tcp_bind(&d->server, bind_addr);
    int r = uv_listen((uv_stream_t *)&d->server, 128, &TcpServerPrivate::handle_accept);
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
        parent->d->spawnRequestHandlerTask((uv_stream_t *)client);
    } else {
        uv_close((uv_handle_t *)client, NULL);
        return;
    }

    debug() << "Connection accepted";
}

uv_buf_t 
TcpServerPrivate::alloc_buffer(uv_handle_t *handle, size_t suggested_size) 
{
    return uv_buf_init((char*)malloc(suggested_size), suggested_size);
}

void
TcpServerPrivate::read_socket(uv_stream_t *server, ssize_t nread, uv_buf_t buf)
{
    if (nread == -1) {
        debug() << "Buffer crappy";
        uv_close((uv_handle_t *) server, NULL);
        free(buf.base);
        return;
    }

    debug() << "Bytes read: " << nread;
    debug() << "Buffer: " << buf.base;

    free(buf.base);
    uv_read_stop(server);

    std::string reply;
    // process request
    //parent->handleRequest(std::string(buf.base), &reply);

    // prepare answer
    uv_write_t ans;
    uv_buf_t ansbuf;
    ansbuf.base = const_cast<char *>(reply.c_str());
    ansbuf.len = reply.size();

    int r = uv_write(&ans, server, &ansbuf, reply.size(), NULL);
    debug() << "Bytes written: " << reply.size();

    uv_close((uv_handle_t *) server, NULL);
}

bool 
TcpServer::isListening() const
{
    return d->listening;
}

bool
TcpServer::hasConnections() const
{ }

TcpSocket *nextConnection()
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
