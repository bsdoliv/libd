#ifndef HTTPD_H
#define HTTPD_H

#include <Daemon>

class Httpd : public Daemon
{
public:
    Httpd();
    virtual ~Httpd();
    void run();
    void handleRequest(const std::string &request, std::string *reply);
};

#endif // !HTTPD_H
