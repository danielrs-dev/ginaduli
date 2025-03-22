#include "gmutex.h"
#ifdef WIN32
#include "impl/gmutexwin32.h"
#endif
#ifdef __gnu_linux__
#include "impl/gmutexlinux.h"
#endif
using namespace gcf;


gMutex::gMutex()
{
#ifdef WIN32
    d = new gMutexWin32();
#endif
#ifdef __gnu_linux__
    d = new gMutexLinux();
#endif
}
gMutex::~gMutex()
{
    delete d;
}
void gMutex::lock()
{
    d->lock();
}
void gMutex::unlock()
{
    d->unlock();
}
bool gMutex::isLocked() const
{
    return d->isLocked();
}
