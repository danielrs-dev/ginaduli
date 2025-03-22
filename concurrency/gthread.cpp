#include "gthread.h"

using namespace gcf;

gThread::gThread(gThreadFunction *func, gu32 nstacksize)
{
#ifdef __gnu_linux__
    d = new gThreadLinux(func,nstacksize);
#endif
#ifdef WIN32
    d = new gThreadWin32(func,nstacksize);
#endif

}

gThread::~gThread()
{
    delete d;
}
void gThread::join()
{
    d->join();
}
gu32 gThread::threadID() const
{
    return d->threadID();
}
gu32 gThread::stackSize() const
{
    return d->stackSize();
}
bool gThread::isFinished() const
{
    return d->isFinished();
}

gThreadFunction *gThread::threadFunction()
{
    return d->threadFunction();
}
