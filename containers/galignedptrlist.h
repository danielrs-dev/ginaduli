#ifndef GALIGNEDPTRLIST_H
#define GALIGNEDPTRLIST_H

/***************************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File: galignedptrlist.h
        Description: Implementation of shared object gAlignedPtrList.
****************************************************************************/
#include "impl/galignedptrlistshared.h"
#include <base/gsharedobjectmodel.h>
namespace gcf
{
/*! \brief The gAlignedPtrList class is a base container of the GINA DULI
           C++ Framework that represents a list of pointers of type T which
           are stored in a fixed array. It works using a scheme of a preallocataed
           array that determines the capacity or size of the array and a set
           of used elements which represent added items. Therefore appending data
           is really fast.

    \param T: Type of data the list would be storing.
    \param DA: Allocator and deallocator of elements when copying and
               removing data.
*/
template <class T, class DA = gNDAllocator<T> >
class gAlignedPtrList: public gSharedObjectModel<gAlignedPtrListShared<T,DA> >
{
public:
    /// Standard constructor
    gAlignedPtrList()
    {

    }
    /*! \brief Standard copy constructor. Copies another list.
        \param other: List to be copies.
    */
    gAlignedPtrList(const gAlignedPtrList<T,DA> &other):
        gSharedObjectModel<gAlignedPtrListShared<T,DA> >(other)
    {

    }
    /// Standard destructor.
    virtual ~gAlignedPtrList()
    {

    }
    /*! \brief Allocates memory for the list.
        \param ncap: Size of the list array.
        \return true if success false if failed.
    */
    virtual bool alloc(gu32 ncap)
    {
        if(this->d == 0)
        {
            this->d = new gAlignedPtrListShared<T,DA>();
        }
        return this->d->alloc(ncap);
    }
    /// Sets every item in the list a zeros or NULL pointer.
    void zeros()
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->zeros();
    }
    /*! \brief Appends an item to the list. The item is a pointer of type T.
        \param ref: Item to be added to the list.
    */
    void append(T *ref)
    {
        if(this->d == 0)
        {
            this->d = new gAlignedPtrListShared<T,DA>();
        }
        this->d->append(ref);
    }
    T *apendix(gu32 index)
    {
        if(this->d == 0)
        {
            this->d = new gAlignedPtrListShared<T,DA>();
        }
        return this->d->apendix(index);
    }
    T *apendix()
    {
        if(this->d == 0)
        {
            this->d = new gAlignedPtrListShared<T,DA>();
        }
        return this->d->apendix();
    }

    /*! \brief Sets an item to the list. Notice this replaces the previous item in it.
        \param ref: New item to set to list.
        \param index: Index of list to set item.
    */
    void setValue(T *ref, gu32 index, bool deallocOld = true)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->setValue(ref,index,deallocOld);
    }
    /*! \brief Gets an item from the list given an index. If list is empty
               it returns 0 or NULL.
        \param index: Index of item to get from list.
        \return Item from list or 0 if empty or item is a null pointer.
    */
    T *value(gu32 index)
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->value(index);
    }
    /// Const version of gAlignedPtrList::value()
    const T *value(gu32 index) const
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->value(index);
    }
    /*! \brief Removes an item from the list given an index. If a
               deallocator of items was set the item gets destroyed
               by this function.
        \param index: Index of item to remove.
     */
    void remove(gu32 index)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->remove(index);
    }
    /*! \brief Removes an item from the list given the reference of it.
               It searches the item and if found it gets removed.
               Same as remove(index) if a deallocator was set then
               the item gets destroyed.
        \param ref: Item to remove.
    */
    void remove(T *ref)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->remove(ref);
    }
    /// Fast version of gAlignedPtrList::remove(index)
    void fastRemove(gu32 index)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->fastRemove(index);
    }
    /// Fast version of gAlignedPtrList::remove(T *ref)
    void fastRemove(T *ref)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->fastRemove(ref);
    }
    void swap(gu32 from, gu32 to)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->swap(from,to);
    }

    /*! \brief Searches an item in list and returns whether found or not.
               Optionally a parameter to get the index of the item found
               can be added.
        \param ref: Item to find in list.
        \param indexOut: Optional pointer to integer to get index of found
                         element. If set to 0 or NULL this gets ignored.
        \return true if found else false.
    */
    bool contains(T *ref, gu32 *indexOut) const
    {
        if(this->d == 0)
        {
            return false;
        }
        return this->d->contains(ref,indexOut);
    }
    /*! \brief Searches an item in list and returns whether found or not.
               Optionally a parameter to get the index of the item found
               can be added.
        \param ref: Item to find in list.
        \param indexOut: Optional pointer to integer to get index of found
                         element. If set to 0 or NULL this gets ignored.
        \return true if found else false.
    */
    bool contains(const T &ref, gu32 *indexOut) const
    {
        if(this->d == 0)
        {
            return false;
        }
        return this->d->contains(ref,indexOut);
    }
    /*! \brief Returns the size of added elements to the list.
        \return Integer of used or added elements from list.
    */
    gu32 used() const
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->used();
    }
    /// Does the same as gAlignedPtrList::used()
    gu32 size() const
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->used();
    }
    /*! \brief Returns the actual size of the internal array of the list.
        \return Capacity of list.
    */
    gu32 capacity() const
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->capacity();
    }
    /*! \brief Sets the capacity of the list. This references the size of
               internal data array. Better use gAlignedListPtr::alloc().
        \param newcap: New capacity to set.
    */
    void setCapacity(gu32 newcap)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->setCapacity(newcap);

    }
    void setClearData(bool set)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->setClearData(set);
    }

    /*! \brief Sets the size of used or added elements by the list.
               This function is handy when you call alloc and you want
               to set the size of added elements to use another function
               such as setValue to set data.
        \param newval: New size of added elements to set.
    */
    void setUsed(gu32 newval)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->setUsed(newval);
    }
    /// Pretty much the same as gAlignedPtrList::value(index)
    T *operator [] (gu32 index)
    {
        return value(index);
    }
    /// Const version of operator []
    const T *operator [] (gu32 index) const
    {
        return value(index);
    }
    /*! \brief Assigns or copies another list to this list.
        \param other: List to copy.
        \return Reference to this object.
    */
    gAlignedPtrList<T,DA> &operator = (const gAlignedPtrList<T,DA> &other)
    {
        this->assign(other);
        return *this;
    }
    template <class SF>
    void sort()
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->sort<SF>();
    }

};

}

#endif // GALIGNEDPTRLIST_H
