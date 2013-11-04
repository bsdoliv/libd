#include "tcpserver.h"
#include "tcpconnection_p.h"
#include "tcpconnection.h"
#include "tools.h"
#include "daemon_p.h"

#define TCPCONNECTION_DEBUG

#ifdef TCPCONNECTION_DEBUG
#   define debug() d_debug()
#endif

D_BEGIN_NAMESPACE

typedef struct {
    uv_write_t req;
    uv_buf_t buf;
} write_req_t;

struct TcpConnectionPrivate
{
    TcpConnection *parent;
    uv_tcp_t *uv_client;
    uv_stream_t *uv_server;
    ConnectionData *conn_data;
    int read_count;

    QByteArray *read_buffer;
    int op_status;

    static uv_buf_t on_alloc_buffer(uv_handle_t *handle, size_t suggested_size);
    static void on_read(uv_stream_t *handle, ssize_t, uv_buf_t);
    static void on_write(uv_write_t *req, int status);
    static void on_close(uv_handle_t *handle);
};

TcpConnection::TcpConnection(TcpServer * parent, 
                             ConnectionData * data) :
    d(new TcpConnectionPrivate)
{
    d->parent = this;
    d->uv_server = data->uv_server;
    d->uv_client = data->uv_client;
    d->uv_client->data = d;
    d->conn_data = data;
    d->read_count = 0;
}

TcpConnection::~TcpConnection()
{
    delete d;
}

void
TcpConnection::read(QByteArray *buffer)
{
    d->read_buffer = buffer;
    uv_read_start((uv_stream_t *)d->uv_client,
                  &TcpConnectionPrivate::on_alloc_buffer,
                  &TcpConnectionPrivate::on_read);
}

uint64_t
TcpConnection::write(const char * data, uint64_t size)
{
    write_req_t *wr = (write_req_t *)malloc(sizeof(write_req_t));
    wr->req.data = d;
    wr->buf = uv_buf_init((char *)malloc(size), size);
    memcpy(wr->buf.base, data, size);
    int r = uv_write(&wr->req, (uv_stream_t *)d->uv_client, &wr->buf, 1, 
                     &TcpConnectionPrivate::on_write);
    return r;
};

void
TcpConnectionPrivate::on_write(uv_write_t *req, int status) 
{
//    debug() << "Status: " << status;

    TcpConnectionPrivate *tcp = (TcpConnectionPrivate *)req->data;

    write_req_t *wr = (write_req_t *)req;
    free(wr->buf.base);
    free(wr);

#if 0
    debug() << "tcp" << tcp;
    debug() << "ts" << ts;
    debug() << "tcp->parent" << tcp->parent;
#endif
    tcp->parent->writeFinished(tcp->parent);
}

void
TcpConnectionPrivate::on_read(uv_stream_t *handle,
                              ssize_t nread,
                              uv_buf_t buf)
{
    TcpConnectionPrivate *tcp = (TcpConnectionPrivate *)handle->data;
    TcpServer *ts = (TcpServer *)tcp->uv_server->data;

    if (nread == -1) {
        if (uv_last_error(ts->defaultLoop()->uv_loop()).code == UV_EOF) {
            debug() << "EOF: discarding connection";
            tcp->op_status = TcpConnection::ReadFail;
            ts->closeConnection(tcp->conn_data);
        }
    }

    if (nread > 0) {
        tcp->read_buffer->append(buf.base);
        uv_read_stop(handle);
        tcp->op_status = TcpConnection::ReadOk;
    }

    if (buf.base)
        free(buf.base);

    tcp->read_count++;
//  TODO notification mechanism
//    tcp->parent->readFinished(tcp->parent);
}

uv_buf_t 
TcpConnectionPrivate::on_alloc_buffer(uv_handle_t *handle, size_t suggested_size) 
{
    return uv_buf_init((char*)malloc(suggested_size), suggested_size);
}

void
TcpConnection::close()
{
    //debug() << "Closing";
    TcpServer *ts = (TcpServer *)d->uv_server->data;
    ts->closeConnection(d->conn_data);
}

int
TcpConnection::status()
{
    return d->op_status;
}

QByteArray *
TcpConnection::buffer()
{
    return d->read_buffer;
}

bool
TcpConnection::wait(int timeout)
{
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);

    if (d->read_count > 0) {
        d->read_count--;
        return true;
    }

    return false;
}

D_END_NAMESPACE
