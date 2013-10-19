#include "httpd.h"

#include <qt/qdebug.h>

#define debug() qDebug() << Q_FUNC_INFO

Httpd::Httpd() : Daemon() { }

Httpd::~Httpd() { }

void Httpd::run()
{
    debug() << "Starting...";
}

void Httpd::handleRequest(const std::string &request, std::string *reply)
{
    debug() << "Master I'm here to serve you";
    debug() << "Request: " << request.c_str();
    reply->assign("OK\n");
}
