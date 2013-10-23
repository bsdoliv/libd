#ifndef IOOBJECT_H
#define IOOBJECT_H

#include "dglobal.h"

D_BEGIN_NAMESPACE

class TcpConnection;
class IOObject
{
public:
    virtual void readFinished(TcpConnection *) = 0;
    virtual void writeFinished(TcpConnection *) = 0;
};

D_END_NAMESPACE

#endif //! IOOBJECT_H
