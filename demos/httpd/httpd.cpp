#include "httpd.h"

#include <qt/qdebug.h>

Httpd::Httpd() : Daemon() { }

Httpd::~Httpd() { }

void Httpd::run()
{
    qDebug() << "Starting...";
}

void Httpd::handleRequest(const std::string &request, std::string *reply)
{
    qDebug() << "Master I'm here to serve you";
    qDebug() << "Request: " << request.c_str();
    reply->assign("OK\n");
}
