#include "daemon.h"

#include <libuv/uv.h>

D_BEGIN_NAMESPACE

Daemon::Daemon() { }

int Daemon::exec()
{
    uv_loop_t *loop = uv_loop_new();
    return uv_run(loop, UV_RUN_DEFAULT);
}

Daemon::~Daemon() { }

D_END_NAMESPACE
