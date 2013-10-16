#include "daemon.h"

#include <iostream>

#include <assert.h>

D_BEGIN_NAMESPACE

static Daemon *parent = 0;
struct DaemonPrivate {
    uv_tcp_t server;

    static uv_buf_t alloc_buffer(uv_handle_t *handle, size_t suggested_size);
    static void handleAccept(uv_stream_t *, int);
    static void handleRequest(uv_stream_t *, ssize_t, uv_buf_t);
};

Daemon::Daemon() :
    d(new DaemonPrivate) 
{
    parent = this;
}

Daemon::~Daemon() 
{ 
    delete d;
}

int 
Daemon::exec()
{
    // calls derived class pre-exec() method
    run();

    uv_loop_t *loop = ::uv_default_loop();

    ::uv_tcp_init(loop, &d->server);
    struct sockaddr_in bind_addr = ::uv_ip4_addr("0.0.0.0", 8080);
    ::uv_tcp_bind(&d->server, bind_addr);

    int r = ::uv_listen((uv_stream_t *)&d->server, 128, &DaemonPrivate::handleAccept);
    if (r != 0) {
        std::cout << "Listen error " << ::uv_err_name(uv_last_error(loop)) 
            << std::endl;
        return r;
    }

    ::uv_tcp_simultaneous_accepts(&d->server, 1);

    std::cout << "Listening on " << 8080 << std::endl;
    return ::uv_run(loop, UV_RUN_DEFAULT);
}

void
DaemonPrivate::handleAccept(uv_stream_t *server, int status)
{
    assert(server);

    std::cout << "Status " << status << std::endl;
    std::cout << "Server pointer " << server << std::endl;
    if (status == -1) {
        std::cout << "Problem" << std::endl;
        return;
    }

    uv_tcp_t *client = (uv_tcp_t *)::malloc(sizeof(uv_tcp_t));
    ::uv_tcp_init(::uv_default_loop(), client);
    if (::uv_accept(server, (uv_stream_t *)client) == 0) {
        ::uv_read_start((uv_stream_t *)client, &DaemonPrivate::alloc_buffer,
                        &DaemonPrivate::handleRequest);
    } else {
        ::uv_close((uv_handle_t *)client, NULL);
    }

    std::cout << "Connection accepted" << std::endl;
}

uv_buf_t 
DaemonPrivate::alloc_buffer(uv_handle_t *handle, size_t suggested_size) 
{
    return uv_buf_init((char*) malloc(suggested_size), suggested_size);
}

void
DaemonPrivate::handleRequest(uv_stream_t *server, ssize_t nread, uv_buf_t buf)
{
    if (nread == -1) {
        std::cout << "Buffer crappy" << std::endl;
        ::uv_close((uv_handle_t *) server, NULL);
        ::free(buf.base);
        return;
    }

    std::cout << "Bytes read: " << nread << std::endl;
    std::cout << "Buffer: " << buf.base << std::endl;

    std::string reply;
    // process request
    parent->handleRequest(std::string(buf.base), &reply);

    ::free(buf.base);
    ::uv_read_stop(server);

    // prepare answer
    uv_write_t req;
    uv_buf_t ansbuf;
    ansbuf.base = const_cast<char *>(reply.c_str());
    ansbuf.len = reply.size();

    int r = ::uv_write(&req, server, &ansbuf, reply.size(), NULL);
    std::cout << "Bytes written: " << reply.size() << std::endl;

    ::uv_close((uv_handle_t *) server, NULL);
}

D_END_NAMESPACE
