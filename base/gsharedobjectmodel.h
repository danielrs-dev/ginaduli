#ifndef GSHAREDOBJECTMODEL_H
#define GSHAREDOBJECTMODEL_H

/*******************************************************************
        Gina Duli C++ Framework
        Author: Daniel Rios
        File: gsharedobjectmodel.h
        Descritpion: Defines the gsharedobjectmodel interface
********************************************************************/

// Include files
#include "gcommon.h"
#include "gsharedobject.h"

namespace gcf
{
    /*! \brief The template class is gSharedObjectModel is the base fundation
               for object that hold data shared by other objects of the same type.
               This is part of the shared object system used by GINA DULI C++ Framework
               This is explained in file gsharedobject.h. Objects using this system
               must use gSharedObjectModel as base deriving from it.
         \param P Object derived from class gSharedObject.

     */
    template <class P>
    class gSharedObjectModel
    {
    public:
        /// Standard constructor
        gSharedObjectModel(): d(0)
        {

        }
        /*! \brief Optional constructor. It optionally intializates
                  property d of type P
             \param setup true to initialize property d false to ignore.
        */
        gSharedObjectModel(bool setup): d(0)
        {
            if(setup)
            {
                d = new P();
            }
        }
        /*! \brief Copy constructor. If property d from "other" is set as
                   shared it just set d as the pointer address from other.d
                   increasing the reference count. Else it just copies data
                   from other object.
            \param other gSharedObjectMode to copy data from.
        */
        gSharedObjectModel(const gSharedObjectModel<P> &other):
            d(0)
        {
            if(other.d == 0)
            {
                return;
            }
            if(other.isShared())
            {
                d = other.d;
                d->incRefCount();
            }
            else
            {
                d = new P();
                d->copy(other.d);
            }
        }
        /// Destructor.
        virtual ~gSharedObjectModel()
        {
            clear();
        }

        /*! \brief Copies data from another gSharedObjectModel.
            \param other gSharedObjectModel object to copy data from.
        */
        void assign(const gSharedObjectModel<P> &other)
        {
            clear();
            if(other.d == 0)
            {
                return;
            }
            if(other.isShared())
            {
                d = other.d;
                d->incRefCount();
                d->setShared(false);
            }
            else
            {
                d = new P();
                d->copy(other.d);
            }
        }
        /*! \brief Clears and removes every data of this object deallocating
                   and destroying main property d.
         */
        virtual void clear()
        {
            if(d == 0)
            {
                return;
            }
            d->decRefCount();
            if(d->refCount() == 0)
            {
                delete d;
            }
            d = 0;
        }
        /*! \brief Sets the flag "shared" for the property d.
            \param set True to set it or false to unset it.
        */
        void setShared(bool set)
        {
            if(d)
            {
                d->setShared(set);
            }
        }
        /*! \brief Retunrs whether the object was set for sharing or not.
            \return true if set false if not.
        */
        bool isShared() const
        {
            if(d)
            {
                return d->isShared();
            }
            return false;
        }
        /*! \brief Returns if the object is empty or property d has not been
                   allocated yet.
            \return true if empty false if not.
        */
        virtual bool isEmpty() const
        {
            return (d == 0);
        }

    protected:
        P *d;
    };
}
#endif // GSHAREDOBJECTMODEL_H
