#include "daemon.h"

#include <iostream>

#include <assert.h>

D_BEGIN_NAMESPACE

struct DaemonPrivate {
    uv_tcp_t server;
};

Daemon::Daemon() :
    d(new DaemonPrivate) { }

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
//    uv_connection_cb cb = (uv_connection_cb)&Daemon::handleConnection;
    Daemon::ha _ha = &Daemon::handleAccept;
    uv_connection_cb *cb = reinterpret_cast<uv_connection_cb *>(&_ha);

    int r = ::uv_listen((uv_stream_t *)&d->server, 128, *cb);
    if (r != 0) {
        std::cout << "Listen error " << ::uv_err_name(uv_last_error(loop)) 
            << std::endl;
        return r;
    }

    std::cout << "Listening on " << 8080 << std::endl;
    return ::uv_run(loop, UV_RUN_DEFAULT);
}

void handleAccept(uv_stream_t *, int)
{
};

void
Daemon::handleAccept(uv_stream_t *server, int status)
{
//    assert(server);

    std::cout << "Status " << status << std::endl;
    std::cout << "Server pointer " << server << std::endl;
    if (status == -1) {
        std::cout << "Problem" << std::endl;
        return;
    }

    uv_tcp_t *client = (uv_tcp_t *)::malloc(sizeof(uv_tcp_t));
    ::uv_tcp_init(::uv_default_loop(), client);
//    std::cout << "client loop" << client->loop;
//    std::cout << "server loop" << server->loop;
    if (::uv_accept(server, (uv_stream_t *)client) == 0) {
        Daemon::hr _hr = &Daemon::handleRequest;
        uv_read_cb *read_cb = reinterpret_cast<uv_read_cb *>(&_hr);

        Daemon::ab _ab = &Daemon::alloc_buffer;
        uv_alloc_cb *alloc_cb = reinterpret_cast<uv_alloc_cb *>(&_ab);

        uv_read_start((uv_stream_t *)client, *alloc_cb, *read_cb);
    } else {
        uv_close((uv_handle_t *)client, NULL);
    }

    std::cout << "handling accept" << std::endl;
}

uv_buf_t 
Daemon::alloc_buffer(uv_handle_t *handle, size_t suggested_size) 
{
    return uv_buf_init((char*) malloc(suggested_size), suggested_size);
}

D_END_NAMESPACE
