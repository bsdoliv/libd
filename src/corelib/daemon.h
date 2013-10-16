#ifndef DAEMON_H
#define DAEMON_H

#include <libuv/uv.h>
#include <string>

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
    virtual void handleRequest(const std::string &request, std::string *reply) = 0;

private:
    DaemonPrivate *d;
};

D_END_NAMESPACE

#endif // ! DAEMON_H
