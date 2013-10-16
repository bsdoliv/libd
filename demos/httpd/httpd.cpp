#include "httpd.h"
#include <iostream>

Httpd::Httpd() : Daemon() { }

Httpd::~Httpd() { }

void Httpd::run()
{
    std::cout << "Starting..." << std::endl;
}

void Httpd::handleRequest(uv_stream_t *, ssize_t, uv_buf_t)
{
    std::cout << "Master I'm here to serve you" << std::endl;
}
