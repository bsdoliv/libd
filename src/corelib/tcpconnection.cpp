#include "tcpserver.h"
#include "tcpconnection_p.h"
#include "tcpconnection.h"
#include "tools.h"

#define TCPCONNECTION_DEBUG

#ifdef TCPCONNECTION_DEBUG
#   define debug() d_debug()
#endif

D_BEGIN_NAMESPACE

static TcpConnection *parent = 0;

#if 1
struct TcpConnectionPrivate
{
    TcpServer * server_parent;
    ConnectionData *cdata;
    static uv_buf_t alloc_buffer(uv_handle_t *handle, size_t suggested_size);
    static void read_finished(uv_stream_t *, ssize_t, uv_buf_t);
};
#endif

TcpConnection::TcpConnection(TcpServer * parent, 
                             ConnectionData * data) :
    d(new TcpConnectionPrivate)
{
    d->server_parent = parent;
    d->cdata = data;
}

TcpConnection::~TcpConnection()
{
    delete d;
}

void
TcpConnection::setConnectionData(ConnectionData * cdata)
{
    d->cdata = cdata;
}

uint64_t 
TcpConnection::read(char * data)
{
    uv_read_start((uv_stream_t *)d->cdata->client,
                  &TcpConnectionPrivate::alloc_buffer,
                  NULL);

#if 0
    uv_buf_t *buf = (uv_buf_t *)d->cdata->client->data;

    if (nread == -1) {
        debug() << "Buffer crappy";
        uv_close((uv_handle_t *) server, NULL);
        free(buf.base);
        return;
    }

    debug() << "Bytes read: " << nread;
    debug() << "Buffer: " << buf.base;

    uv_read_stop(server);
    free(buf.base);
#endif
//                  &TcpConnectionPrivate::read_finished);
//
}

uint64_t 
TcpConnection::write(char * data, uint64_t size)
{
};

void
TcpConnectionPrivate::read_finished(uv_stream_t *server, ssize_t nread, 
                                     uv_buf_t buf)
{
}


uv_buf_t 
TcpConnectionPrivate::alloc_buffer(uv_handle_t *handle, size_t suggested_size) 
{
    return uv_buf_init((char*)malloc(suggested_size), suggested_size);
}

D_END_NAMESPACE
