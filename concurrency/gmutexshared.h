#ifndef GMUTEXSHARED_H
#define GMUTEXSHARED_H
/***************************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File: gmutexshared.h
        Description: Declares the abstract class gMutexShared.
****************************************************************************/
#include <base/gcommon.h>

namespace gcf
{
/*! \brief The class gMutexShared is the main abstraction class that provides
           the functionality for object gMutex.
           This class is abstract and must derived. Derived object provides
           the actual mutex function as they target an specific operating system.
           For example for windows this class is derived to gMutexWin32
*/
class gMutexShared
{
public:
    /// Standard constructor. It just initializes property m_locked.
    gMutexShared():
        m_locked(false)
    {

    }
    /// Virtual destructor.
    virtual ~gMutexShared()
    {

    }
    /// Locks the mutex on the current thread.
    virtual void lock() = 0;
    /// Unlocks the mutex on the current thread.
    virtual void unlock() = 0;
    /*! \brief Returns whether the thread is locked or not.
        \return true if locked false if not.
     */
    bool isLocked() const
    {
        return m_locked;
    }
protected:
    /// Flag that tells if the mutex is locked or not.
    bool m_locked;
};
}

#endif // GMUTEXSHARED_H
