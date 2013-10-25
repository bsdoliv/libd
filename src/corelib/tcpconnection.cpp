#include "tcpserver.h"
#include "tcpconnection_p.h"
#include "tcpconnection.h"
#include "tools.h"

#define TCPCONNECTION_DEBUG

#ifdef TCPCONNECTION_DEBUG
#   define debug() d_debug()
#endif

D_BEGIN_NAMESPACE

struct TcpConnectionPrivate
{
    TcpServer *tcpserver;
    ConnectionData *conndata;

    QByteArray buffer;
    int write_status;

    static uv_buf_t alloc_buffer(uv_handle_t *handle, size_t suggested_size);
    static void read_finished_cb(uv_stream_t *, ssize_t, uv_buf_t);
    static void write_finished_cb(uv_write_t *req, int status);
    static void close_finished_cb(uv_handle_t *handle);
};

TcpConnection::TcpConnection(TcpServer * parent, 
                             ConnectionData * data) :
    d(new TcpConnectionPrivate)
{
    data->tcpconn = this;
    d->conndata = data;
    d->tcpserver = parent;
    d->conndata->uv_client->data = this;
}

TcpConnection::~TcpConnection()
{
    delete d;
}

void
TcpConnection::setConnectionData(ConnectionData * cdata)
{
    d->conndata = cdata;
}

void
TcpConnection::read()
{
    ConnectionData *cd = (ConnectionData *)d->conndata;
    uv_read_start((uv_stream_t *)cd->uv_client,
                  &TcpConnectionPrivate::alloc_buffer,
                  &TcpConnectionPrivate::read_finished_cb);
}

uint64_t
TcpConnection::write(const char * data, uint64_t size)
{
    // prepare answer
    uv_write_t ans;
    //ans.data = this;
    uv_buf_t ansbuf;

    d->buffer.clear();
    d->buffer.push_front(data);
    ansbuf.base = (char *)data;
    ansbuf.len = size;
    debug() << "Size:" << size;
    debug() << "Buffer:" << data;

    ConnectionData *cd = (ConnectionData *)d->conndata;
    int r = uv_write(&ans, (uv_stream_t *)cd->uv_client, &ansbuf, 1, 
                     NULL);
                     //&TcpConnectionPrivate::write_finished_cb);
    (uv_handle_t *)
    cd->uv_client->data = 0;
    uv_close((uv_handle_t *) cd->uv_client, NULL);
    return r;
};

#if 1
void
TcpConnectionPrivate::write_finished_cb(uv_write_t *req, int status) 
{
    debug() << "Status: " << status;
    TcpConnection *tc = (TcpConnection *)req->data;
    tc->d->write_status = status;
    tc->d->tcpserver->writeFinished(tc);
}
#endif

void
TcpConnectionPrivate::read_finished_cb(uv_stream_t *server,
                                       ssize_t nread,
                                       uv_buf_t buf)
{
    if (nread == -1) {
        debug() << "Buffer crappy";
        uv_close((uv_handle_t *) server, NULL);
        free(buf.base);
        return;
    }

    debug() << "Bytes read: " << nread;
    debug() << "Buffer: " << buf.base;

    TcpConnection *tc = (TcpConnection *)server->data;

    tc->d->buffer += buf.base;

    uv_read_stop(server);
    free(buf.base);

    debug() << "Server pointer:" << server;
    tc->d->tcpserver->readFinished(tc);
}

uv_buf_t 
TcpConnectionPrivate::alloc_buffer(uv_handle_t *handle, size_t suggested_size) 
{
    return uv_buf_init((char*)malloc(suggested_size), suggested_size);
}

QByteArray *
TcpConnection::buffer()
{
    return &d->buffer;
}

void
TcpConnection::close()
{
    ConnectionData *cd = (ConnectionData *)d->conndata;
//    uv_shutdown_t shutdown_req;
//    uv_shutdown(&shutdown_req, (uv_stream_t *) cd->uv_client, NULL);
    uv_close((uv_handle_t *) cd->uv_client, NULL);
}

void
TcpConnectionPrivate::close_finished_cb(uv_handle_t *)
{
    debug() << "teste";
}

D_END_NAMESPACE
