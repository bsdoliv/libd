#ifndef DAEMON_H
#define DAEMON_H

#include <libuv/uv.h>

#include "dglobal.h"

D_BEGIN_NAMESPACE

struct DaemonPrivate;
class Daemon 
{
public:
    Daemon();
    virtual ~Daemon();

    int exec();
    virtual void run() = 0;
    void handleAccept(uv_stream_t *, int);
    virtual void handleRequest(uv_stream_t *, ssize_t, uv_buf_t) = 0;

private:
    DaemonPrivate *d;

    uv_buf_t alloc_buffer(uv_handle_t *handle, size_t suggested_size);

    typedef uv_buf_t (Daemon::*ab)(uv_handle_t *, size_t);
    typedef void (Daemon::*hr)(uv_stream_t *, ssize_t, uv_buf_t);
    typedef void (Daemon::*ha)(uv_stream_t *, int);
};

void handleAccept(uv_stream_t *, int);

D_END_NAMESPACE

#endif // ! DAEMON_H
