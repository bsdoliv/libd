#include "uvwrapper.h"

uvMutexLocker::uvMutexLocker(uv_mutex_t *mtx)
{
    _m = mtx;
    uv_mutex_lock(_m);
}

uvMutexLocker::~uvMutexLocker()
{
    uv_mutex_unlock(_m);
}
