#ifndef GTHREADFUNCTION_H
#define GTHREADFUNCTION_H
/****************************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File: gthreadfunction.h
        Description: Definition of the abstract class gThreadFunction
*****************************************************************************/
#include <base/gcommon.h>

namespace gcf
{
/*! \brief The gThreadFunction represents the callback object for multithreading
           system of GINA DULI. It is paased to gThread object where it uses
           to run the thread by calling the run function of the gThreadFunction
           class.
           Because this class is abstract. It must be derived by the client
           program and reimplemented the run function. Later the derived class
           can be passed to gThread.
*/
class gThreadFunction
{
public:
    /// Called function by the thread linked to this callback object.
    virtual void run() = 0;
};
}
#endif // GTHREADFUNCTION_H
