#ifndef IOOBJECT_H
#define IOOBJECT_H

#include "dglobal.h"

D_BEGIN_NAMESPACE

class TcpConnection;
class IOObject
{
public:
    virtual void readFinished(TcpConnection *);
    virtual void writeFinished(TcpConnection *);
};

D_END_NAMESPACE

#endif //! IOOBJECT_H
