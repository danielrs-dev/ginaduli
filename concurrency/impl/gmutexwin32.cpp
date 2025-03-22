#include "gmutexwin32.h"

using namespace gcf;

gMutexWin32::gMutexWin32():
    m_mutex(0)
{
    m_mutex = CreateMutex(0,false,0);
}
gMutexWin32::~gMutexWin32()
{
    if(m_mutex)
    {
        CloseHandle(m_mutex);
    }
}
void gMutexWin32::lock()
{
    m_locked = true;
    if(WaitForSingleObject(m_mutex,INFINITE) == WAIT_ABANDONED)
    {
        ReleaseMutex(m_mutex);
        WaitForSingleObject(m_mutex,0);
    }
}
void gMutexWin32::unlock()
{
    m_locked = false;
    ReleaseMutex(m_mutex);
}
