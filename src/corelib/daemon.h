#ifndef DAEMON_H
#define DAEMON_H

#include "dglobal.h"

D_BEGIN_NAMESPACE

class EventLoop;
class DaemonPrivate;
class Daemon 
{
public:
    Daemon();
    virtual ~Daemon();

    int exec();
    virtual void run() = 0;

protected:
    EventLoop *defaultLoop();

private:
    DaemonPrivate *d;
    friend class DaemonPrivate;
};

D_END_NAMESPACE

#endif // ! DAEMON_H
