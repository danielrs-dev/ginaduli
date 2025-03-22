#ifdef WIN32
#include "gthreadwin32.h"

using namespace gcf;

gThreadWin32::gThreadWin32(gThreadFunction *func, gu32 nstacksize):
    gThreadShared(func,nstacksize),
    m_threadHandle(0)
{
    DWORD id;
    m_threadHandle = CreateThread(NULL,
                                  (DWORD)nstacksize,
                                  (LPTHREAD_START_ROUTINE)gThreadWin32::threadFunc,
                                  this,
                                  0,
                                  &id);
    m_id = gu32(id);
    m_finished = false;

}
void gThreadWin32::join()
{
    WaitForSingleObject(m_threadHandle,INFINITE);
}
gThreadWin32::~gThreadWin32()
{
    if(m_threadHandle)
    {
        CloseHandle(m_threadHandle);
    }
}

DWORD gThreadWin32::threadFunc(void *data)
{
    gThreadWin32 *thread = static_cast<gThreadWin32 *>(data);
    gThreadFunction *func = thread->threadFunction();

    func->run();
    thread->setFinished(true);

    return 0;
}



#endif
