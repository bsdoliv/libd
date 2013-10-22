#include "tcpd.h"

#include <TcpConnection>

#include <qt/qdebug.h>

#define debug() qDebug() << Q_FUNC_INFO

Tcpd::Tcpd() : TcpServer() { }

Tcpd::~Tcpd() { }

void Tcpd::run()
{
    debug() << "Starting...";
    debug() << "Listening on" << port();
}

void Tcpd::newConnection(TcpConnection *c)
{
    debug() << "Master I'm here to serve you";
//    debug() << "Request: " << request.c_str();
//    reply->assign("OK\n");
}
