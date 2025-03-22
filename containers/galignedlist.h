#ifndef GALIGNEDLIST_H
#define GALIGNEDLIST_H
/***************************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File: galignedlist.h
        Description: Implementation template container class gAlignedList.
****************************************************************************/
#include "impl/galignedlistshared.h"
#include <base/gsharedobjectmodel.h>

namespace gcf
{
/*! \brief The gAlignedList class is a basic container of items of type T.
           It is a generic template where it is easy manipulate a simple list
           where data is stored as an fixed array which expands or shrinks.

           By defualt the list items are added by the function append which
           expands the list using the trick of a preallocated array of many
           elements and a counter of used elements that differs to the actual
           size of the array.

           The list can be allocalted with the function alloc to set a predeterminated
           capacity.
           Also items can be set by index.
           This is a versatile easy to use list.
    \param T: Type of data to be stored in list.
*/
template <class T>
class gAlignedList: public gSharedObjectModel<gAlignedListShared<T> >
{
public:
    /// Standard constructor.
    gAlignedList()
    {

    }
    /*! \brief Copy constructor. It copies data from another gAlignedList
               object the shared object model of GINA DU.
        \param other: Object to be copied.
    */
    gAlignedList(const gAlignedList<T> &other):
        gSharedObjectModel<gAlignedListShared<T> >(other)
    {

    }
    /// Destructor.
    ~gAlignedList()
    {

    }
    /*! \brief Allocates memory for the list. It internally sets the array
               size by the parameter ncap.
        \param ncap: Size of the list to be set.
        \return true if success else fail.
    */
    bool alloc(gu32 ncap)
    {
        if(this->d == 0)
        {
            this->d = new gAlignedListShared<T>();
        }
        return this->d->alloc(ncap);
    }
    /*! \brief Appends an item to the list. Internally it increases
               the size of used elements by 1 that started as 0.
        \param val: Value to be added to the list.
    */
    void append(const T &val)
    {
        if(this->d == 0)
        {
            this->d = new gAlignedListShared<T>();
        }
        this->d->append(val);
    }
    /*! \brief Sets a value in the list given an index. Notice if index
               is bigger than used() you will be writing outside the boundaries
               of the desired list space. More than capacity means an error.
        \param val: Value to be added.
        \param index: Index of item to be set.
     */
    void setValue(const T &val,gu32 index)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->setValue(val,index);
    }
    /*! \brief Removes an item from list given an index. It shrinks the list
               and reallocates items in the proper position.
        \param index: Index of item to be removed.
     */
    void remove(gu32 index)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->remove(index);
    }
    /// Fast version of gAlignedList::remove()
    void fastRemove(gu32 index)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->fastRemove(index);
    }
    /*! \brief Returns a value given an index.
        \param index: Index of value to get from list.
        \return Reference value of item from list which can be modified.
    */
    T &value(gu32 index)
    {
        GASSERT(this->d,"ERROR: List must have values to get gAlignedList::value");
        return this->d->value(index);
    }
    /// Const version of gAlignedList::value
    const T &value(gu32 index) const
    {
        GASSERT(this->d ,"ERROR: List must have values to get gAlignedList::value");
        return this->d->value(index);
    }
    /*! \brief Sets the capacity of the list. It changes the internal property
               capacity which refers to the size of the internal array.
               Changing this to a bigger than the array size may cause issues.
        \param nval: New capacity value to be set.
    */
    void setCapacity(gu32 nval)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->setCapacity(nval);
    }
    /*! \brief Sets the size of used values or added elements to the list.
               This function is handy when you call alloc and want to set
               which elements are going to be set as used because by default
               alloc() just modfies the capacity but set used elements as 0.
        \param nval: New size of used elements to be set.
    */
    void setUsed(gu32 nval)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->setUsed(nval);
    }
    /*! \brief Returns the capacity of the list. Capacity is the size of the
               internal array.
        \return 32 bit value of capacity.
    */
    gu32 capacity() const
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->capacity();
    }
    /*! \brief Returns the size of used elements of the list.
               This data is not the fixed size of the internal array.
               It is the number of added items to the list.
        \return The size of used elements of the list.
    */
    gu32 used() const
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->used();
    }
    /// Same as gAlignedList::used().
    gu32 size() const
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->used();
    }
    /*! \brief Returns the pointer of the internal fixed array.
        \return Pointer to an array of type T.
    */
    T *data()
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->data();
    }
    /// Const version of gAlignedList::data()
    const T *data() const
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->data();
    }
    /*! \brief Returns whether the list is empty or has not used elements.
        \return true if list has not used elements or else false.
    */
    virtual bool isEmpty() const
    {
        if(this->d == 0)
        {
            return true;
        }
        return this->d->isEmpty();
    }
    /// Implementaion of operator [] pretty much as gAlignedList::value()
    T &operator [] (gu32 index)
    {
        return value(index);
    }
    /// Const version of operator[]
    const T &operator[](gu32 index) const
    {
        return value(index);
    }
    /*! \brief Assign operator =. Copies data from another list.
        \param other: List to be copies.
        \return Reference to this object.
    */
    gAlignedList<T> &operator = (const gAlignedList<T> &other)
    {
        assign(other);
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

#endif // GALIGNEDLIST_H
