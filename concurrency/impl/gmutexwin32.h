#ifndef GMUTEXWIN32_H
#define GMUTEXWIN32_H
/***********************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File gmutexwin32.h
        Description: Declaration of class gMutexWin32 for mutexes on
                     on Windows Systems.
************************************************************************/
#ifdef WIN32
#include <windows.h>
#include <concurrency/gmutexshared.h>
namespace gcf
{
/*! \brief The class gMutexWin32 encapsulates all functionality of Mutexes
           using the base API of Windows.
 */
class gMutexWin32: public gMutexShared
{
public:
    /// Standard constructor initializes the mutex
    gMutexWin32();
    /*! \brief Destructor clears the mutex deallocating m_mutex using base
               functions of the Windows API
     */
    ~gMutexWin32();
    /// Locks the mutex on the current thread.
    virtual void lock();
    /// Unlocks the mutex on the current thread.
    virtual void unlock();
protected:
    /// Windows handle of a mutex.
    HANDLE m_mutex;
};
}
#endif
#endif // GMUTEXWIN32_H
