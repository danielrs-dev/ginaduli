#ifndef GTHREADSHARED_H
#define GTHREADSHARED_H
/****************************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File: gthreadshared.h
        Descritpion: Definition of the abstract class gThreadShared
*****************************************************************************/
#include <base/gsharedobject.h>
#include "gthreadfunction.h"

namespace gcf
{
/*! \brief The gThreadShared class represent the base object of gThread
           object, intended to give every functionality for threads.
           The main idea is that this object would be derived to the actually
           object giving the service. In this case an object for each operating
           system like linux and windows.
*/
class gThreadShared: public gSharedObject
{
public:
    /*! \brief Standard constructor. It takes two parameters. The callback
               function objects and the stacksize.
        \param func: Callback object function where thread would be running.
        \param nstacksize: The size of the stack of the thread.
    */
    gThreadShared(gThreadFunction *func, gu32 nstacksize):
        m_func(func),
        m_id(0),
        m_stacksize(nstacksize),
        m_finished(false)
    {

    }
    /// Standard destructor.
    virtual ~gThreadShared()
    {

    }

    /// Joins the calling thread to the new thread by waiting until new one ends.
    virtual void join() = 0;

    /*! \brief Returns the stack size of the thread.
        \returns 32 bit integer with stack size.
    */
    gu32 stackSize() const
    {
        return m_stacksize;
    }
    /*! \brief Returns the callback object function used by the thread.
        \return: Pointer to gThreadFunction object.
    */
    gThreadFunction *threadFunction()
    {
        return m_func;
    }
    /*! \brief Returns the thread ID of this thread.
        \return 32 bit integer of the ID.
     */
    gu32 threadID() const
    {
        return m_id;
    }
    /*! \brief Sets the flag whether the thread has ended or not. This function
               is called internally on the main thread function when it ends.
        \param set: true to set it has finished false else.
    */
    void setFinished(bool set)
    {
        m_finished = set;
    }
    /*! \brief Returns whether the thread has ended or not.
        \return true if ended else false.
    */
    bool isFinished() const
    {
        return m_finished;
    }
protected:
    /// Pointer to callback object function.
    gThreadFunction *m_func;
    /// Thread ID.
    gu32 m_id;
    /// The stack size of the thread.
    gu32 m_stacksize;
    /// Flag telling whether the thread ended or not-
    bool m_finished;
};
}


#endif // GTHREADSHARED_H
