#ifndef GALIGNEDLISTSHARED_H
#define GALIGNEDLISTSHARED_H
/**************************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File: galignedlistshared.h
        Description: Implementation of the shared object gAlignedListShared
                     for the container gAlignedList
***************************************************************************/
/// Defines the default increment of reallocation of the list data
#define GAL_DEFINC 10
#include <base/gsharedobject.h>
#include <gmath/galgorithm.h>
#include <system/gmemory.h>
#include <cstdlib>
namespace gcf
{
/*! \brief The gAlignedListShared class represent the shared object and main
           provider of functionality for the class gAlignedList.
    \param T : Base class defining the internal array type of the object.
 */
template<class T>
class gAlignedListShared: public gSharedObject
{
public:
    /// Standard constructor. It initializes everything as null or 0.
    gAlignedListShared():
        m_data(0),
        m_used(0),
        m_capacity(0)
    {

    }
    /// Standard destructor. It clears and deallocates all internal data.
    ~gAlignedListShared()
    {
        clear();
    }
    /*! \brief Allocates memory for the list given the size of it.
        \param nsize: The size of the allocation for the list.
        \return true if allocated succesfully false if failed.
    */
    bool alloc(gu32 nsize)
    {
        if(nsize == 0)
        {
            return false;
        }
        clear();
        m_data = static_cast<T *>(gMemory::alloc(nsize * sizeof(T)));
        if(m_data)
        {
            m_capacity = nsize;
        }
        return m_data !=0;
    }
    /*! \brief Resizes the internal array of the list to a new size.
        \param newcap The new size of the internal array to be resized.
        \return true if success else false.
    */
    bool resize(gu32 newcap)
    {
        if(newcap == 0)
        {
            return false;
        }
        if(m_data == 0)
        {
            return alloc(newcap);
        }

        m_data = static_cast<T *>(gMemory::ralloc(m_data,newcap * sizeof(T)));
        m_capacity = newcap;
        return m_data != 0;
    }
    /*! \brief Preallocates memoery for the list giving an increment. It
               basically increases the size of the list.
        \param increment: The incremental value of the list.
    */
    void prealloc(gu32 increment)
    {
        if(m_capacity == m_used)
        {
            resize(m_capacity + increment);
        }
    }
    /*! \brief It appends a new item to the list to the end of it.
        \param val: Value of type T to be appended.
    */
    void append(const T &val)
    {
        prealloc(GAL_DEFINC);
        m_data[m_used] = val;
        m_used++;
    }
    /*! \brief Sets a value in the list giving its index.
        \param val: Value to be set.
        \param index: 0 based index pointing to direction on list.
    */
    void setValue(const T &val, gu32 index)
    {
        if(index >= m_used)
        {
            return;
        }
        m_data[index] = val;
    }
    /*! \brief Returns a value from the list given its index.
        \param index: 0 based index pointing to item in list.
        \return Reference to value.
    */
    T &value(gu32 index)
    {
        if(index >= m_used)
        {
            return m_empty;
        }
        return m_data[index];
    }
    /// Const version of previous value function
    const T &value(gu32 index) const
    {
        if(index >= m_used)
        {
            return m_empty;
        }
        return m_data[index];
    }
    /*! \brief Removes an item from the list given an index.
        \param index: 0 based index of item to be removed.
    */
    void remove(gu32 index)
    {
        gu32 nused = m_used - 1;
        gu32 i,j;
        if(m_data == 0)
        {
            return;
        }
        if(index >= m_used)
        {
            return;
        }
        if(m_used == 0)
        {
            return;
        }
        for(i = index, j = index + 1; i < nused; i++, j++)
        {
            m_data[i] = m_data[j];
        }
        m_used = nused;

    }
    /*! \brief Removes an item in list in a fast way given an index.
        \param index: 0 based index pointing to item on list.
    */
    void fastRemove(gu32 index)
    {
        if(m_data == 0)
        {
            return;
        }
        if(index >= m_used)
        {
            return;
        }
        m_data[index] = m_data[m_used - 1];
        m_used--;
    }
    /// Clears and deallocates every internal data from the list.
    void clear()
    {
        if(m_data)
        {
            gMemory::dalloc(m_data);
        }
        m_data = 0;
        m_used = 0;
        m_capacity = 0;
    }
    /*! \brief Copies one list to another. This function is used
               internally by the base class of gAlignedList gSharingObjectModel
               to copy directly data from one object to another.
        \param other: const pointer to the object to be copied.
    */
    virtual void copy(const gSharedObject *other)
    {
        gu32 i;
        const gAlignedListShared *ol = static_cast<const gAlignedListShared *>(other);
        if(ol->isEmpty())
        {
            clear();
            return;
        }
        alloc(ol->m_capacity);

        for(i = 0; i < ol->m_used; i++)
        {
            m_data[i] = ol->m_data[i];
        }
        m_used = ol->m_used;
    }
    /*! \brief Sets the internal size of the internal array m_data.
        \param newval: New capacity to be set.
    */
    void setCapacity(gu32 newval)
    {
        m_capacity = newval;
    }
    /*! \brief Sets the quantity of used elements of the list.
        \param newval: New size to be set.
    */
    void setUsed(gu32 newval)
    {
        m_used = newval;
    }
    /*! \brief Returns the capacity of the list.
        \return Integer containing the capacity of the list.
    */
    gu32 capacity() const
    {
        return m_capacity;
    }
    /*! \brief Returns the quantity of used elements of the list.
        \return Integer value of used elements.
    */
    gu32 used() const
    {
        return m_used;
    }
    /*! \brief Returns the list array pointer.
        \return List array pointer of type T.
     */
    T *data()
    {
        return m_data;
    }
    /// Const version of gAlignedListShared::data()
    const T *data() const
    {
        return m_data;
    }
    /*! \brief Returns if list empty or has no used elements at all.
        \return true if empty or else false.
    */
    bool isEmpty() const
    {
        return m_used == 0;
    }
    template <class SF>
    void sort()
    {
        if(m_data == 0)
        {
            return;
        }
        if(m_used == 0)
        {
            return;
        }
        gAlgorithm::sort<T,SF>(m_data,m_used);
    }

protected:
    /// Internal data array of type T.
    T *m_data;
    /// Used elements of list.
    gu32 m_used;
    /// The size or capaicty of m_data.
    gu32 m_capacity;
    /// Empty
    T m_empty;
};

}

#endif // GALIGNEDLISTSHARED_H
