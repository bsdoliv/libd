#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include "daemon.h"

D_BEGIN_NAMESPACE

class HttpDaemon : public Daemon
{
public:
    HttpDaemon();
    virtual ~HttpDaemon();

};

D_END_NAMESPACE

#endif // !HTTPSERVER_H
