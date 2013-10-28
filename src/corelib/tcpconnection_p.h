#ifndef TCPSOCKET_P_H
#define TCPSOCKET_P_H

#include "dglobal.h"
#include "uv.h"

D_BEGIN_NAMESPACE

struct ConnectionData {
    ConnectionData() :
    id()
    , uv_client(0)
    , uv_server(0)
    { };

    QByteArray id;
    uv_tcp_t *uv_client;
    uv_stream_t *uv_server;

    void clear()
    {
        id.clear();
        uv_client = 0;
        uv_server = 0;
    }
};

D_END_NAMESPACE

#endif //! TCPSOCKET_P_H
