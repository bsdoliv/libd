#include "httpd.h"

int
main(int argc, char **argv)
{
    Httpd httpd;
    return httpd.exec();
}
