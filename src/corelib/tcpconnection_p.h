#ifndef TCPSOCKET_P_H
#define TCPSOCKET_P_H

#include "dglobal.h"
#include "uv.h"

D_BEGIN_NAMESPACE

struct ConnectionData {
    ConnectionData() { };
    ConnectionData(int id_, uv_tcp_t * client_) :
        id(id_)
        , client(client_)
    { }
    int id;
    uv_tcp_t *client;
    void clear()
    {
        id = -1;
        client = 0;
    }
};

D_END_NAMESPACE

#endif //! TCPSOCKET_P_H
