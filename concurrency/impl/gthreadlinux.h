#ifndef GTHREADLINUX_H
#define GTHREADLINUX_H
/**************************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File: gthreadlinux.h
        Description: Implementation of threads for linux.
***************************************************************************/
#ifdef __gnu_linux__

#include <pthread.h>
#include <concurrency/gthreadshared.h>
namespace gcf
{
/*! \brief The gThreadLinux defines the thread functionality for the gThread
           on Linux sistems. It uses POSIX threads(pthreads).
*/
class gThreadLinux: public gThreadShared
{
public:
    /*! \brief Standard constructor.
        \param func: Callback object that runs on the thread.
        \param nstacksize: The stack size of the thread.
    */
    gThreadLinux(gThreadFunction *func, gu32 nstacksize);
    /// Standard destructor
    ~gThreadLinux();
    /// Join function puts the calling thread on wait mode for the new thread
    virtual void join();
    /*! \brief Static function where threads works. It internally calls
               the callback object function gThreadFunction::run.
        \param data: Data passed to thread function. In this case it passed
               the pointer "this"
    */
    static void *threadFunc(void *data);
protected:
    /// ID Identificator of the thread.
    pthread_t m_thread;
};
}

#endif
#endif // GTHREADLINUX_H
