#ifndef GMUTEXLINUX_H
#define GMUTEXLINUX_H
/*****************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File: gmuteslinux.h
        Description: Defines the class gMutexLinux for main class gMutex.
                     For Linux Systems.
******************************************************************/
#ifdef __gnu_linux__
#include <concurrency/gmutexshared.h>
#include <pthread.h>
namespace gcf
{
/*! \brief The class gMutexLinux represents the main functionality for mutex
           on Linux Operating Systems. It uses POSIX mutexes.
*/
class gMutexLinux: public gMutexShared
{
public:
    /// Main constructor
    gMutexLinux();
    /// Main destructor
    ~gMutexLinux();
    /*! \brief Locks the mutex on the current thread.
     */
    virtual void lock();
    /*! \brief Unlocks the mutex on the current thread.
     */
    virtual void unlock();
protected:
    /// Property of the mutex handle
    pthread_mutex_t m_mutex;
};
#endif
#endif // GMUTEXLINUX_H
