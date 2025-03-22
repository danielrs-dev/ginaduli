#ifndef GLINKEDLIST_H
#define GLINKEDLIST_H
/*****************************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File glinkedlist.h
        Description: Implementation of the template class gLinkedList.
******************************************************************************/

#include "impl/glinkedlistshared.h"
#include <base/gsharedobjectmodel.h>
namespace gcf
{
/*! \brief The gLinkedList class is base container of the GINA DULI C++ Framework.
           It represents a container structure known as linked list.
           A linked list is a set items represented by nodes which link
           to each other by a pointer to each other in a forward way.
           Each node basically has the pointer to the next item of the list.
           And each node holds the user data of type T.
    \param T: User data of type T.
    \param DA: The allocator used when copying or removing data from the list.
               This applies for user data. By default a non destructive allocator
               is suggested.
*/
template <class T, class DA = gNDAllocator<T> >
class gLinkedList: public gSharedObjectModel<gLinkedListShared<T,DA> >
{
public:
    /// Standard constructor.
    gLinkedList()
    {

    }
    /*! \brief Copy constructor.
        \param other: Linked list to copy from.
     */
    gLinkedList(const gLinkedList<T,DA> &other):
        gSharedObjectModel<gLinkedListShared<T,DA> >(other)
    {

    }
    /// Destructor.
    virtual ~gLinkedList()
    {

    }
    /*! \brief Adds or appends an item to the end of the list.
        \param ref: Item to add.
    */
    void append(T *ref)
    {
        if(this->d == 0)
        {
            this->d = new gLinkedListShared<T,DA>();
        }
        this->d->append(ref);
    }
    /*! \brief Returns the current selected item.
        \return Pointer to user data of item.
    */
    T *value()
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->value();
    }
    /// Const version gLinkedList::value()
    const T *value() const
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->value();
    }
    /// Removes the current selected item from the list.
    void remove()
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->remove();
    }

    /*! \brief Removes an item given as parameter the referece of its user data.
        \param ref: Item to remove from list.
     */
    void remove(T *ref)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->remove(ref);
    }
    /*! \brief Removes an item from the list given its index.
        \param index: Item index to remove.
    */
    void remove(gu32 index)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->remove(index);
    }

    /// Selects the first item of the list.
    void setFirst()
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->setFirst();
    }
    /// Select the last item from the list.
    void setLast()
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->setLast();
    }
    /// Selects the next following item of the current selected one.
    void next()
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->next();
    }
    /*! \brief Returns the current selected item as linked list node data.
        \return Pointer to node.
    */
    gLinkedListNode<T,DA> *node()
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->node();
    }
    /*! \brief Copies a list to this list.
        \param other: List to copy from.
        \return Reference to this list.
     */
    gLinkedList<T,DA> &operator = (const gLinkedList<T,DA> &other)
    {
        this->assign(other);
        return *this;
    }

};
}


#endif // GLINKEDLIST_H
