#include "tcpserver.h"
#include "tcpconnection_p.h"
#include "tcpconnection.h"
#include "tools.h"
#include "daemon_p.h"

#include <unistd.h>

#define TCPCONNECTION_DEBUG

#ifdef TCPCONNECTION_DEBUG
#   define debug() d_debug()
#endif

D_BEGIN_NAMESPACE

typedef struct {
    uv_write_t req;
    uv_buf_t buf;
} write_req_t;

typedef struct {
    TcpConnectionPrivate *tcpriv;
    QByteArray *read_buffer;
} read_req_t;

struct TcpConnectionPrivate
{
    TcpConnection *parent;
    uv_tcp_t *uv_client;
    uv_stream_t *uv_server;
    ConnectionData *conn_data;
    int read_count;

    int op_status;

    static uv_buf_t on_alloc_buffer(uv_handle_t *handle, size_t suggested_size);
    static void on_read(uv_stream_t *handle, ssize_t, uv_buf_t);
    static void on_write(uv_write_t *req, int status);
    static void on_close(uv_handle_t *handle);
    static void on_wait(uv_timer_t *handle, int status);
};

TcpConnection::TcpConnection(TcpServer * parent, 
                             ConnectionData * data) :
    d(new TcpConnectionPrivate)
{
    d->parent = this;
    d->uv_server = data->uv_server;
    d->uv_client = data->uv_client;
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
    read_req_t *req = (read_req_t *)malloc(sizeof(read_req_t));
    req->read_buffer = buffer;
    req->tcpriv = d;
    d->uv_client->data = req;
    uv_read_start((uv_stream_t *)d->uv_client,
                  &TcpConnectionPrivate::on_alloc_buffer,
                  &TcpConnectionPrivate::on_read);
}

bool
TcpConnection::timedRead(QByteArray *buffer, int timeout)
{
    uv_timer_t timer;
    bool tmout = false;
    // start timer
    timer.data = &tmout;
    uv_timer_init(uv_default_loop(), &timer);
    uv_timer_start(&timer, &TcpConnectionPrivate::on_wait, timeout, 0);

    read(buffer);

    bool sleep = true;
    bool rvalue = false;
    do {
        uv_run(uv_default_loop(), UV_RUN_ONCE);

        if (d->read_count > 0) {
            d->read_count--;
            sleep = false;
            rvalue = true;
            uv_timer_stop(&timer);
            debug() << "read";
        }

        if (tmout) {
            debug() << "timeout";
            sleep = false;
            rvalue = true;
        }

        static int msec = 1;
        usleep(msec * 1000);
    } while (sleep);

    return rvalue;
}

uint64_t
TcpConnection::write(const char * data, uint64_t size)
{
    write_req_t *wr = (write_req_t *)malloc(sizeof(write_req_t));
    wr->buf = uv_buf_init((char *)malloc(size), size);
    memcpy(wr->buf.base, data, size);
    int r = uv_write(&wr->req, (uv_stream_t *)d->uv_client, &wr->buf, 1, 
                     &TcpConnectionPrivate::on_write);
    return r;
};

void
TcpConnectionPrivate::on_write(uv_write_t *req, int status) 
{

    write_req_t *wr = (write_req_t *)req;
    free(wr->buf.base);
    free(wr);
}

void
TcpConnectionPrivate::on_read(uv_stream_t *handle,
                              ssize_t nread,
                              uv_buf_t buf)
{
    read_req_t *req = (read_req_t *)handle->data;
    TcpConnectionPrivate *tcpriv = req->tcpriv;
    QByteArray *read_buffer = req->read_buffer;
    TcpServer *ts = (TcpServer *)tcpriv->uv_server->data;

    if (nread == -1) {
        if (uv_last_error(ts->defaultLoop()->uv_loop()).code == UV_EOF) {
            debug() << "EOF: discarding connection";
            tcpriv->op_status = TcpConnection::ReadFail;
        }
    }

    if (nread > 0) {
        //read_buffer->resize(nread);
        read_buffer->append(buf.base);
        uv_read_stop(handle);
        tcpriv->op_status = TcpConnection::ReadOk;
    }

    if (buf.base)
        free(buf.base);

    free(req);

    debug() << "last error" << (uv_last_error(ts->defaultLoop()->uv_loop()).code == UV_EAGAIN);
    debug() << "status";

    tcpriv->read_count++;
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
    TcpServer *ts = (TcpServer *)d->uv_server->data;
    ts->closeConnection(d->conn_data);
}

int
TcpConnection::status()
{
    return d->op_status;
}

void 
TcpConnectionPrivate::on_wait(uv_timer_t *handle, int status)
{
    bool *timeout = (bool *)handle->data;
    *timeout = true;
    uv_timer_stop(handle);
}

D_END_NAMESPACE
