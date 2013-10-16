#ifndef HTTPD_H
#define HTTPD_H

#include <Daemon>

class Httpd : public Daemon
{
public:
    Httpd();
    virtual ~Httpd();
    void run();
    void handleRequest(uv_stream_t *, ssize_t, uv_buf_t);
};

#endif // !HTTPD_H
