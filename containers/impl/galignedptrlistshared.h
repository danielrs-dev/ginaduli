#ifndef GALIGNEDPTRLISTSHARED_H
#define GALIGNEDPTRLISTSHARED_H
/***************************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File: galignedptrlistshared.h
        Description: Implementation of shared object gAlignedPtrListShared.
****************************************************************************/
/// Defines the increment used on preallocation of the list
#define GALPTR_DEFINC 12
#include <base/gsharedobject.h>
#include <cstdlib>
#include <base/gdallocator.h>
#include <gmath/galgorithm.h>
#include <system/gmemory.h>
namespace gcf
{
/*! \brief The AlignedPtrListShared class provides the main functionality
           of the class gAlignedPtrList.
    \param T: Object of type the used by list.
    \param DA: Data deallocator of list.
*/
template <class T, class DA = gNDAllocator<T> >
class gAlignedPtrListShared: public gSharedObject
{
public:
    /// Standard constructor. It iniatilizes every property as 0.
    gAlignedPtrListShared():
        m_data(0),
        m_capacity(0),
        m_used(0),
        m_cleardata(true)
    {

    }
    /// Standarad destructor. Clears and deallocates data from list.
    ~gAlignedPtrListShared()
    {
        clear();
    }
    /// Clears and deallocates internal data.
    void clear()
    {
        gu32 i;
        T *ref;
        DA deallocator;
        if(m_data == 0)
        {
            return;
        }
        if(deallocator.isDestructive() && m_cleardata)
        {
            for(i = 0; i < m_used; i++)
            {
                ref = m_data[i];

                if(ref)
                {
                    deallocator.dalloc(ref);
                }
                m_data[i] = 0;
            }
        }
        gMemory::dalloc(m_data);
        m_data = 0;
        m_used = 0;
        m_capacity = 0;
    }
    /*! \brief Allocates memory for the fixed array.
        \param nsize: Size to be allocated.
        \return true if success else false.
    */
    bool alloc(gu32 nsize)
    {
        if(nsize == 0)
        {
            return false;
        }
        clear();
        m_data = static_cast<T**>(gMemory::alloc(nsize * sizeof(T*)));
        if(m_data)
        {

            m_capacity = nsize;
            zeros();
        }
        return m_data !=0;
    }
    /*! \brief Resizes the internal array.
        \param nsize: New size of internal array.
        \return true if success else false.
    */
    bool resize(gu32 nsize)
    {
        DA deallocator;
        if(nsize == 0)
        {
            return false;
        }
        if(m_data == 0)
        {
            return alloc(nsize);
        }
        if(nsize < m_used && deallocator.isDestructive() && m_cleardata)
        {
            T *ref;

            gu32 i;

            for(i = nsize; i <m_used; i++)
            {
                ref = m_data[i];
                if(ref)
                {
                    deallocator.dalloc(ref);
                }
            }
        }
        m_data = static_cast<T**>(gMemory::ralloc(m_data,nsize * sizeof(T*)));
        if(m_data)
        {
            gu32 i;
            m_capacity = nsize;
            for(i = m_used; i < m_capacity; i++)
            {
                m_data[i] = 0;
            }
        }
        return m_data != 0;
    }
    /*! \brief Pre-allocates memory for the internal array. This function
               is used by gAlignedPtrList::append() and it is used to set
               the array size and increase it when used elements exceed the
               array capacity.
        \param nsize: Allocation size and increment.
    */
    void prealloc(gu32 nsize)
    {
        if(m_capacity == m_used)
        {
            resize(m_capacity + nsize);
        }
    }
    /// Set all data array to zero.
    void zeros()
    {
        gu32 i;
        if(m_data)
        {
            for(i = 0; i < m_capacity;i++)
            {
                m_data[i] = 0;
            }
        }
    }
    /*! \brief Copies another gAlignedPtrList.
        \param other: List to be copies.
    */
    virtual void copy(const gSharedObject *other)
    {
        gu32 i;
        const T *v;
        DA allocator;
        const gAlignedPtrListShared<T,DA> *oc =
                static_cast<const gAlignedPtrListShared<T,DA> *>(other);
        if(oc->isEmpty())
        {
            clear();
            return;
        }
        alloc(oc->m_capacity);
        m_used = oc->m_used;
        if(allocator.isAllocator() == false)
        {
            for(i = 0 ; i < m_used; i++)
            {
                m_data[i] = oc->m_data[i];
            }
        }
        else
        {
            for(i = 0 ; i < m_used; i++)
            {
                v = oc->m_data[i];
                if(v)
                {
                    m_data[i] = allocator.alloc(*oc->m_data[i]);
                }
                else
                {
                    m_data[i] = 0;
                }
            }
        }
    }
    /*! \brief Appends an element to the list.
        \param ref: Item to be added to list.
    */
    void append(T *ref)
    {
        prealloc(GALPTR_DEFINC);
        m_data[m_used] = ref;
        m_used++;
    }
    T *apendix(gu32 index)
    {
        T *ref;
        if(index >= m_used)
        {
            ref = new T();
            append(ref);
        }
        else
        {
            ref = m_data[index];
        }
        return ref;
    }
    T *apendix()
    {
        T *ref;
        if(m_used == m_capacity)
        {
            ref = new T();
            append(ref);
        }
        else
        {
            ref = m_data[m_used];
            if(!ref)
            {
                ref = new T();
                m_data[m_used] = ref;
            }
            m_used++;
        }
        return ref;
    }

    /*! \brief Sets a item in the list given an index.
        \param ref: New item to set.
        \param index: 0 based index of element to change.
    */
    void setValue(T *ref, gu32 index, bool deallocOld)
    {
        T *oldref;
        if(index >= m_used)
        {
            return;
        }
        oldref = m_data[index];
        if(oldref && deallocOld)
        {
            DA dealloc;
            if(dealloc.isDestructive() && m_cleardata)
            {
                dealloc.dalloc(oldref);
            }
        }
        m_data[index] = ref;
    }
    /*! \brief Gets an item from list.
        \param index: 0 based index of item to get.
        \return Pointer of item.
     */
    T *value(gu32 index)
    {
        if(index >= m_used)
        {
            return 0;
        }
        return m_data[index];
    }
    /// Const version of gAlignedPtrListShared::value()
    const T *value(gu32 index) const
    {
        if(index >= m_used)
        {
            return 0;
        }
        return m_data[index];
    }
    /*! \brief Removes an item from the list given its index.
        \param 0 based index of item to remove.
    */
    void remove(gu32 index)
    {
        if(m_used == 0)
        {
            return;
        }
        if(index >= m_used)
        {
            return;
        }
        gu32 nsize = m_used - 1;
        gu32 i,j;
        T *ref;
        DA deallocator;
        ref = m_data[index];
        for(i = index, j = index + 1; i < nsize;i++,j++)
        {
            m_data[i] = m_data[j];
        }

        if(deallocator.isDestructive() && ref != 0 && m_cleardata)
        {
            deallocator.dalloc(ref);
        }
        m_used = nsize;
    }
    /// Fast version gAlignedPtrListShared::remove()
    void fastRemove(gu32 index)
    {
        if(m_used == 0)
        {
            return;
        }
        if(index >= m_used)
        {
            return;
        }
        T *ref = m_data[index];
        DA dealloc;
        m_used--;
        if(ref && dealloc.isDestructive() && m_cleardata)
        {
            dealloc.dalloc(ref);
        }
        m_data[index] = m_data[m_used];
    }
    /*! \brief Search of an item on list and returns whether is there or not.
        \param ref: Item to search on list.
        \param indexOut: Optional parameter to retrieve the index of the item
                         found in list. If null this gets ignored.
        \return true if item found else false.
     */
    bool contains(T *ref, gu32 *indexOut) const
    {
        T *vref;
        gu32 i;
        for(i = 0; i < m_used; i++)
        {
            vref = m_data[i];
            if(vref == ref)
            {
                if(indexOut)
                {
                    *indexOut = i;
                }
                return true;
            }
        }
        return false;
    }
    /*! \brief Search of an item on list and returns whether is there or not.
        \param ref: Item to search on list.
        \param indexOut: Optional parameter to retrieve the index of the item
                         found in list. If null this gets ignored.
        \return true if item found else false.
     */
    bool contains(const T &ref, gu32 *indexOut) const
    {
        T *vref;
        gu32 i;
        for(i = 0; i < m_used; i++)
        {
            vref = m_data[i];
            if(vref == 0)
            {
                continue;
            }
            if((*vref) == ref)
            {
                if(indexOut)
                {
                    *indexOut = i;
                }
                return true;
            }
        }
        return false;
    }
    /*! \brief Removes an item list given its reference.
        \param ref: Reference of item.
     */
    void remove(T *ref)
    {
        gu32 index;
        if(contains(ref,&index))
        {
            remove(index);
        }
    }
    /// Fast version gAlignedPtrListShared::remove()
    void fastRemove(T *ref)
    {
        gu32 index;
        if(contains(ref,&index))
        {
            fastRemove(index);
        }
    }
    /// Swaps an list item from on to another.
    void swap(gu32 from, gu32 to)
    {
        T *ref;
        if(from >= m_used)
        {
            return;
        }
        if(to >= m_used)
        {
            return;
        }
        ref = m_data[to];
        m_data[to] = m_data[from];
        m_data[from] = ref;
    }

    /*! \brief Returns whether list has no used elements or not.
        \return true if has no used elements else false.
    */
    bool isEmpty() const
    {
        return m_used == 0;
    }
    /*! \brief Returns the size of used elements by the list.
        \return Size of used elements of the list.
    */
    gu32 used() const
    {
        return m_used;
    }
    /*! \brief Returns the capacity or total size of the internal data array.
        \return Capacity of the array.
    */
    gu32 capacity() const
    {
        return m_capacity;
    }
    /*! \brief Sets the size of used elements by the list.
        \param newval: New size to be set.
    */
    void setUsed(gu32 newval)
    {
        m_used = newval;
    }
    /*! \brief Sets the capacity of the internal array of list. Nevertheless,
               size of the array does not change.
        \param newcap: New capacity to set.
    */
    void setCapacity(gu32 newcap)
    {
        m_capacity = newcap;
    }
    void setClearData(bool set)
    {
        m_cleardata = set;
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
        gAlgorithm::sort<T *,SF>(m_data,m_used);
    }
protected:
    /// Internal data array
    T **m_data;
    /// The capacity of the list or size of internal data array
    gu32 m_capacity;
    /// Used elements by the list or added items.
    gu32 m_used;
    /// Clears all data
    bool m_cleardata;
};

}


#endif // GALIGNEDPTRLISTSHARED_H
