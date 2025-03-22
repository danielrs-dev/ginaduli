#ifndef GTHREAD_H
#define GTHREAD_H
/************************************************************************
        GINA DULI C++ Framwork
        Author: Daniel Rios
        File: gthread.h
        Description: Definition and implementation of threads.
*************************************************************************/
#ifdef __gnu_linux__
#include "impl/gthreadlinux.h"
#endif
#ifdef WIN32
#include "impl/gthreadwin32.h"
#endif
namespace gcf
{
/*! \brief The gThread class represents a thread object on GINA DULI framework.
           It adds multithreading capabilities to the framework adding concurrency
           on any task implemented by the client application. It uses the
           operating system native multithreading system.

           Naturally it works on a callback object calling its function run, where
           everthing happens.
*/
class SHARED_GCF gThread
{
public:
    /*! \brief Constructor of the class and initializator of the thread.
               After construction happend thread starts working immediatly.
        \param func: Callback object function where thread will work.
        \param nstacksize: The stack size of the thread. Default 0 means
                           The OS decides the size.
    */
    gThread(gThreadFunction *func, gu32 nstacksize = 0);
    /*! \brief Destructor of the class. It basically destroys the property
               d which its destructor terminates the thread.
     */
    ~gThread();
    /// Joins  the calling thread to the new thread by waiting until the new thread ends.
    void join();
    /*! \brief Returns this thread ID.
        \return 32 Bit integer with thread ID.
    */
    gu32 threadID() const;
    /*! \brief Returns whether the thread has ended or not.
        \return true if thread has ended false if not.
    */
    bool isFinished() const;
    /*! \brief Returns the stack size of this thread.
        \return 32 bit integer with stack size data.
     */
    gu32 stackSize() const;
    /*! \brief Returns the pointer to callback object function of this thread.
        \return Pointer to gThreadObject.
     */
    gThreadFunction *threadFunction();
protected:
    /*! \brief Property holder of all functionallity of threads. */
    gThreadShared *d;
};
}
#endif // GTHREAD_H
