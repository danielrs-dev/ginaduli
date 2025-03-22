#ifndef GSHAREDOBJECT_H
#define GSHAREDOBJECT_H
/*************************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File: gsharedobject.h
        Description: Declaration and implementation of class object gSharedObject
**************************************************************************/


#include "gcommon.h"

namespace gcf
{
    /*! \brief The class gSharedObject is part of the data sharing system of
               GINA DULI. The sharing system is used on class object that tend
               to contain large data such as strings list containers. The main
               idea is to increase speed when passing information between objects
               of the same type such as string1 = string2 or functions returning
               a string or a list and instead of copying data to the temporary object
               that the program tend to do it just passes this gSharedObject which
               can be shared with objects of the same type using a reference count system
               which prevents objects to be destroyed when other use it.
     */

    class gSharedObject
    {
    public:
        /// Main contructor
        gSharedObject():
            m_shared(false),
            m_refcount(1)
        {

        }
        /// Main destructor
        virtual ~gSharedObject()
        {

        }
        /*! \brief Copies data from another gSharedObject
            \param gSharedObject to copy from
        */
        virtual void copy(const gSharedObject *other)
        {
            GDUNUSED(other);
        }
        /*! \brief Returns whether the shared object flag "shared" is on.
            \return true if object is shared or false if not.
        */
        bool isShared() const
        {
            return m_shared;
        }
        /*! \brief Sets the flag "shared" to the object.
            \param set True to set it as shared false to unset it.
        */
        void setShared(bool set)
        {
            m_shared = set;
        }
        /*! \brief Returns the current reference count of this object.
                   more than 1 means owned by many objects. 0 means ready
                   to get destroyed.
            \return Value of refence count.
        */
        gs32 refCount() const
        {
            return m_refcount;
        }
        /*! \brief Increases the reference count of this object*/
        void incRefCount() const
        {
            m_refcount++;
        }
        /// Decreases the reference count of this object.
        void decRefCount() const
        {
            m_refcount--;
        }
        template <class C>
        C *cast()
        {
            return static_cast<C *>(this);
        }
        template<class C>
        const C *cast() const
        {
            return static_cast<const C*>(this);
        }
    protected:
        /// Object flag "shared"
        mutable bool m_shared;
        /// Variable holding the reference count.
        mutable gs32 m_refcount;
    };
}

#endif // GSHAREDOBJECT_H
