#include "httpd.h"
#include <iostream>

Httpd::Httpd() : Daemon() { }

Httpd::~Httpd() { }

void Httpd::run()
{
    std::cout << "Starting..." << std::endl;
}

void Httpd::handleRequest(const std::string &request, std::string *reply)
{
    std::cout << "Master I'm here to serve you" << std::endl;
    std::cout << "Request: " << request;
    reply->assign("OK\n");
}
