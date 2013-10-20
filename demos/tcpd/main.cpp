#include "tcpd.h"

int
main(int argc, char **argv)
{
    Tcpd tcpd;
    tcpd.listen(HostAddress::Any, 8080);
    return tcpd.exec();
}
