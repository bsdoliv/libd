#include "tcpserver.h"
#include "tcpconnection_p.h"
#include "tcpconnection.h"
#include "tools.h"

#define TCPCONNECTION_DEBUG

#ifdef TCPCONNECTION_DEBUG
#   define debug() d_debug()
#endif

D_BEGIN_NAMESPACE

static TcpConnection *static_tcpconn = 0;

struct TcpConnectionPrivate
{
    TcpServer * server_parent;
    IOObject *call_on_finish;
    ConnectionData *conn_data;
    QByteArray buffer;
    int write_status;

    static uv_buf_t alloc_buffer(uv_handle_t *handle, size_t suggested_size);
    static void read_finished(uv_stream_t *, ssize_t, uv_buf_t);
    static void write_finished(uv_write_t *req, int status);
};

TcpConnection::TcpConnection(TcpServer * parent, 
                             ConnectionData * data) :
    d(new TcpConnectionPrivate)
{
    d->conn_data = data;
    d->call_on_finish = 0;
    static_tcpconn = this;
    d->server_parent = parent;
}

TcpConnection::~TcpConnection()
{
    delete d;
}

void
TcpConnection::setConnectionData(ConnectionData * cdata)
{
    d->conn_data = cdata;
}

void
TcpConnection::read()
{
    uv_read_start((uv_stream_t *)d->conn_data->client,
                  &TcpConnectionPrivate::alloc_buffer,
                  &TcpConnectionPrivate::read_finished);
}

uint64_t
TcpConnection::write(const char * data, uint64_t size)
{
    // prepare answer
    uv_write_t ans;
    uv_buf_t ansbuf;

    static_tcpconn->d->buffer.clear();
    static_tcpconn->d->buffer.push_front(data);
    debug() << "data" << data;
    ansbuf.base = const_cast<char *>(static_tcpconn->d->buffer.data());
    ansbuf.len = size;

    int r = uv_write(&ans, (uv_stream_t *) d->conn_data->client, &ansbuf, size, 
                     &TcpConnectionPrivate::write_finished);
    return r;
};

#if 1
void
TcpConnectionPrivate::write_finished(uv_write_t *req, int status) 
{
    debug() << "Status: " << status;
    static_tcpconn->d->write_status = status;
    static_tcpconn->d->server_parent->writeFinished(static_tcpconn);
//    uv_close((uv_handle_t *) static_tcpconn->d->conn_data->server, NULL);
}
#endif

void
TcpConnectionPrivate::read_finished(uv_stream_t *server, ssize_t nread,
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
    
    static_tcpconn->d->buffer += buf.base;

    uv_read_stop(server);
    free(buf.base);

    debug() << "Server pointer:" << server;
    debug() << "Client pointer:" << static_tcpconn->d->conn_data->client;
    static_tcpconn->d->conn_data->server = server;
    static_tcpconn->d->server_parent->readFinished(static_tcpconn);
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

D_END_NAMESPACE
