#ifndef UVWRAPPER_H
#define UVWRAPPER_H

#include "dglobal.h"
#include "uv.h"

D_BEGIN_NAMESPACE

class uvMutexLocker 
{
public:
    uvMutexLocker(uv_mutex_t *mtx);
    ~uvMutexLocker();

private:
    uv_mutex_t *_m;
};

D_END_NAMESPACE

#endif //! UVWRAPPER_H
