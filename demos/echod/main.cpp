#include "echod.h"

int
main(int argc, char **argv)
{
    Echod echod;
    echod.listen(HostAddress::Any, 8080);
    return echod.exec();
}
