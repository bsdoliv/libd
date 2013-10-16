#ifndef HTTPD_H
#define HTTPD_H

#include <Daemon>

class Httpd : public Daemon
{
public:
    Httpd();
    virtual ~Httpd();
};

#endif // !HTTPD_H
