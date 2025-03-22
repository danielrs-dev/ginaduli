#ifdef __gnu_linux__
#include "gthreadlinux.h"

using namespace gcf;

gThreadLinux::gThreadLinux(gThreadFunction *func, gu32 nstacksize):
    gThreadShared(func,nstacksize)
{
    pthread_attr attr;
    pthread_attr_init(&attr);
    if(nstacksize)
    {
        pthread_attr_setstacksize(&attr,(size_t)nstacksize);
    }
    pthread_create(&m_thread,&attr,&gThreadLinux::threadFunc,this);
    m_id = gu32(m_thread);
}
gThreadLinux::~gThreadLinux()
{
    if(m_thread)
    {
        pthread_cancel(m_thread);
    }
}

void gThreadLinux::join()
{
    pthread_join(m_thread);
}

void *gThreadLinux::threadFunc(void *data)
{
    gThreadLinux *thread = static_cast<gThreadLinux *>(data);
    gThreadFunction *func = thread->threadFunction();
    func->run();
    thread->setFinished(true);
    return 0;
}

#endif
