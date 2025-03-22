#ifndef GMUTEX_H
#define GMUTEX_H

#include <base/gcommon.h>
#include "gmutexshared.h"
/********************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File: gmutex.h
        Description: Declaration of gMutex Class.
*********************************************************************/

namespace gcf
{
/*! \brief The class gMutex represents a low level mutex used on multithreading.
           It is usually used to prevent global data to be writen in a chaotic
           by many threads by locking the thread putting it on hold while other
           thread work on. Whoever locks first takes the data and the other wait.
*/
class SHARED_GCF gMutex
{
public:
    /*! \brief Standard constructor. It initializes the mutex by initializing member gSharedMutex *d.
               Depending of the operating system it creates property d by derived clases of gSharedMutex
               either gMutexLinux of gMutexWin32
     */
    gMutex();
    /*! \brief Standard destructor. Removes the mutex. It basically deletes property d
               which does everything on its destructor.
    */
    ~gMutex();

    /*! \brief Locks the Mutex for the current thread preventing other threads to go furthermore.
               Whoever mutex locks first gets access first.
    */
    void lock();
    /*! \brief Unlocks the Mutex telling the OS othe threads can go further.
     */
    void unlock();
    /*! \brief Returns whether the Mutex is locked or not.
        \return true if locked or false if not.
    */
    bool isLocked() const;
protected:
    /// Main property which provides every functionality of this class.
    gMutexShared *d;
};
}

#endif // GMUTEX_H
