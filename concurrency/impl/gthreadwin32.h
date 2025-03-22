#ifndef GTHREADWIN32_H
#define GTHREADWIN32_H
/*************************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File gthreadwin32.h
        Description: Definition of the class gThreadWin32 for gThread.
                     Threads for Windows Systems.
**************************************************************************/
#ifdef WIN32

#include <windows.h>
#include <concurrency/gthreadshared.h>
namespace gcf
{
/*! \brief The class gThreadWin32 defines and implements threads for
           Windows Systems.
*/
class gThreadWin32: public gThreadShared
{
public:
    /*! \brief Standard constructor.
        \param func: Callback object where thread executes.
    */
    gThreadWin32(gThreadFunction *func, gu32 nstacksize);
    /// Standard destructor
    ~gThreadWin32();
    /// Puts the calling thread on wait mode until the new thread ends.
    virtual void join();
    /*! \brief Static function where the new thread works. Interanlly it calls
               the callback object function run.
        \param data: Data passed to thread function. By default it passes
               "this" pointer.
     */
    static DWORD threadFunc(void *data);

protected:
    /// Windows thread handle
    HANDLE m_threadHandle;
};
}

#endif
#endif // GTHREADWIN32_H
