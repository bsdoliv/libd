#include "daemon.h"
#include "daemon_p.h"
#include "uvwrapper.h"

#include "uv.h"

#include <iostream>
#include <assert.h>
#include <string.h>

D_BEGIN_NAMESPACE

struct DaemonPrivate
{
    EventLoop default_loop;
};

Daemon::Daemon() :
    d(new DaemonPrivate)
{ }

Daemon::~Daemon() 
{ 
    delete d;
}

// runs event loop
int 
Daemon::exec()
{
    // calls derived class pre-exec() method
    run();
    uv_loop_t *loop = uv_default_loop();
    return uv_run(loop, UV_RUN_DEFAULT);
}

EventLoop *
Daemon::defaultLoop()
{
    return &d->default_loop;
}

#if 0
static Daemon *parent = 0;

#define MAXTASKS 4

struct TaskData {
    int id;
    uv_buf_t buf;
    ssize_t bufsize;
    uv_stream_t *client;
};

struct DaemonPrivate {
    uv_tcp_t server;
    int curtask;
    uv_mutex_t mtx;
    uv_work_t req[MAXTASKS];
    TaskData databucket[MAXTASKS];

    static uv_buf_t alloc_buffer(uv_handle_t *handle, size_t suggested_size);
    static void handle_accept(uv_stream_t *, int);
    static void read_socket(uv_stream_t *, ssize_t, uv_buf_t);

    void spawnRequestHandlerTask(uv_stream_t *client);
    static void requestHandlerTask(uv_work_t *req);
    static void taskFinished(uv_work_t *req, int status);
};

void 
DaemonPrivate::spawnRequestHandlerTask(uv_stream_t *client)
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

    std::cout << "Task spawned: " << td->id << std::endl;
}

void
DaemonPrivate::taskFinished(uv_work_t *req, int status)
{
    uvMutexLocker(&parent->d->mtx);
    --parent->d->curtask;

    TaskData *td = (TaskData *)req->data;
    std::cout << "Task finished: " << td->id << std::endl;
}

void
DaemonPrivate::requestHandlerTask(uv_work_t *req)
{
    TaskData *td = (TaskData *)req->data;
    uv_read_start((uv_stream_t *)td->client,
                  &DaemonPrivate::alloc_buffer,
                  &DaemonPrivate::read_socket);
}

Daemon::Daemon() :
    d(new DaemonPrivate) 
{
    parent = this;
    d->curtask = 0;
}

Daemon::~Daemon() 
{ 
    delete d;
}



void
DaemonPrivate::handle_accept(uv_stream_t *server, int status)
{
    assert(server);
    if (parent->d->curtask >= MAXTASKS) {
        std::cout << "Too many tasks, no room to handle this one.";
        return;
    }

#if 0
    std::cout << "Status " << status << std::endl;
    std::cout << "Server pointer " << server << std::endl;
#endif

    if (status == -1) {
        std::cout << "Problem" << std::endl;
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

    std::cout << "Connection accepted" << std::endl;
}

uv_buf_t 
DaemonPrivate::alloc_buffer(uv_handle_t *handle, size_t suggested_size) 
{
    return uv_buf_init((char*)malloc(suggested_size), suggested_size);
}

void
DaemonPrivate::read_socket(uv_stream_t *server, ssize_t nread, uv_buf_t buf)
{
    if (nread == -1) {
        std::cout << "Buffer crappy" << std::endl;
        uv_close((uv_handle_t *) server, NULL);
        free(buf.base);
        return;
    }

#if 0
    std::cout << "Bytes read: " << nread << std::endl;
    std::cout << "Buffer: " << buf.base << std::endl;
#endif

    free(buf.base);
    uv_read_stop(server);

    std::string reply;
    // process request
    parent->handleRequest(std::string(buf.base), &reply);

    // prepare answer
    uv_write_t ans;
    uv_buf_t ansbuf;
    ansbuf.base = const_cast<char *>(reply.c_str());
    ansbuf.len = reply.size();

    int r = uv_write(&ans, server, &ansbuf, reply.size(), NULL);
    std::cout << "Bytes written: " << reply.size() << std::endl;

    uv_close((uv_handle_t *) server, NULL);
}
#endif

D_END_NAMESPACE
