#ifndef DAEMON_P_H
#define DAEMON_P_H

#include "dglobal.h"
#include "uv.h"

D_BEGIN_NAMESPACE

struct EventLoop
{
public:
    uv_loop_t *uv_loop()
    { 
        return uv_default_loop();
    }
};

D_END_NAMESPACE

#endif //! DAEMON_P_H
