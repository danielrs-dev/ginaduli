#ifdef __gnu_linux__
#include "gmutexlinux.h"


using namespace gcf;


gMutexLinux::gMutexLinux():

{
    pthread_mutexattr_t attributes;

    pthread_mutexattr_init(&attributes);
    pthread_mutexattr_settype(&attributes, PTHREAD_MUTEX_RECURSIVE);

    pthread_mutex_init(&m_mutex, &attributes);
}

gMutexLinux::~gMutexLinux()
{
    pthread_mutex_destroy(&m_mutex);
}
void gMutexLinux::lock()
{
    m_locked = true;
    pthread_mutex_lock(&m_mutex);
}
void gMutexLinux::unlock()
{
    m_locked = false;
    pthread_mutex_unlock(&m_mutex);
}
#endif
