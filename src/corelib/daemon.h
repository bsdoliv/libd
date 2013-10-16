#ifndef DAEMON_H
#define DAEMON_H

#include "dglobal.h"

D_BEGIN_NAMESPACE

class Daemon 
{
public:
    Daemon();
    virtual ~Daemon();
    int exec();
};

D_END_NAMESPACE

#endif // ! DAEMON_H
