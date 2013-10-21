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

D_END_NAMESPACE
