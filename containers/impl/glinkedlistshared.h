#ifndef GLINKEDLISTSHARED_H
#define GLINKEDLISTSHARED_H
/*****************************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File glinkedlistshared.h
        Description: Implementation of the template class gLinkedListShared
******************************************************************************/
#include <cstdlib>
#include <base/gsharedobject.h>
#include "glinkedlistnode.h"
namespace gcf
{
/*! \brief The gLinkedListShared class provides the main functionality and
           represets the major part of a linked list. This object is basically
           the shared object or property held by gLinkedList, that handles
           the core functionality of the linked list.
    \param T: Type of data the linked list contains.
    \param DA: Standard allocator - deallocator.
*/
template<class T, class DA = gNDAllocator<T> >
class gLinkedListShared: public gSharedObject
{
public:
    /// Standard constructor
    gLinkedListShared():
        m_first(0),
        m_node(0),
        m_last(0)
    {

    }
    /// Destructor
    ~gLinkedListShared()
    {
        clear();
    }
    /*! \brief Returns whether the list is empty or not.
        \return true if empty else false.
    */
    bool isEmpty() const
    {
        return m_first == 0;
    }
    /// Cleanup function. Removes every item from the linked list.
    void clear()
    {
        gLinkedListNode<T,DA> *m_nextnode;
        m_node = m_first;
        while(m_node)
        {
            m_nextnode = m_node->next();
            delete m_node;
            m_node = m_nextnode;
        }
        m_first = 0;
        m_last = 0;
    }
    /*! \brief Adds an item to the end of the linked list.
        \param ref: Pointer to item to add.
    */
    void append(T *ref)
    {
        if(isEmpty())
        {
            m_first = new gLinkedListNode<T,DA>;
            m_node = m_first;
            m_last = m_first;
            m_node->setNext(0);
            m_node->setData(ref);
            return;
        }
        m_node = new gLinkedListNode<T,DA>();
        m_node->setData(ref);
        m_last->setNext(m_node);
        m_node->setNext(0);
        m_last = m_node;
    }
    /*! \brief Returns the current selected a item from the linked list.
        \return Pointer to item to retrieve.
    */
    T *value()
    {
        if(isEmpty())
        {
            return 0;
        }
        if(m_node)
        {
            return m_node->data();
        }
        return 0;
    }
    /// Const version gLinkedListShared::value()
    const T *value() const
    {
        if(isEmpty())
        {
            return 0;
        }
        if(m_node)
        {
            return m_node->data();
        }
        return 0;
    }
    /// Selects the first item of the linked list.
    void setFirst()
    {
        if(isEmpty())
        {
            return;
        }
        m_node = m_first;
    }
    /// Selects the last item of the linked list.
    void setLast()
    {
        m_node = m_last;
    }
    /*! \brief Selects the next following item of the list and returns it.
        \return Next item or new selected one.
    */
    gLinkedListNode<T,DA> *next()
    {
        m_node = m_node->next();
        return m_node;
    }
    /*! \brief Returns the current selected item as a node of the linked list.
        \returns Pointer to node.
     */
    gLinkedListNode<T,DA> *node()
    {
        return m_node;
    }
    /// Removes the current selected item from the list.
    void remove()
    {
        gLinkedListNode<T,DA> *prev = 0;
        gLinkedListNode<T,DA> *toremove = m_node;
        if(m_first == m_last)
        {

            delete m_first;
            m_last = 0;
            m_first = 0;
            m_node = 0;

            return;
        }
        m_node = m_first;
        while(m_node)
        {
            if(m_node == toremove)
            {
                break;
            }
            prev = m_node;
            next();
        }
        if(m_node == m_first)
        {
            m_first = m_node->next();
        }
        else if(m_node == m_last)
        {
            m_last = prev;
            m_last->setNext(0);
        }
        else
        {
            prev->setNext(m_node->next());
        }
        delete m_node;
        m_node = m_last;

    }
    /*! \brief Removes and item from the list.
        \param index 0 based of item on list.
    */
    void remove(gu32 index)
    {
        gLinkedListNode<T,DA> *prev = 0;
        gLinkedListNode<T,DA> *toremove = m_node;
        gu32 count = 0;
        if(m_first == m_last)
        {

            delete m_first;
            m_last = 0;
            m_first = 0;
            m_node = 0;

            return;
        }
        m_node = m_first;
        while(m_node)
        {
            if(count == index)
            {
                break;
            }
            prev = m_node;
            next();
            count++;
        }
        if(m_node == m_first)
        {
            m_first = m_node->next();
        }
        else if(m_node == m_last)
        {
            m_last = prev;
            m_last->setNext(0);
        }
        else
        {
            prev->setNext(m_node->next());
        }
        delete m_node;
        m_node = m_last;

    }
    /*! \brief Finds and removes an item from the list.
        \param ref: Reference pointer of item to remove.
    */
    void remove(T *ref)
    {
        gLinkedListNode<T,DA> *prev = 0;
        if(m_first == m_last)
        {
            //just one element
            if(m_first->data() == ref)
            {
                delete m_first;
                m_last = 0;
                m_first = 0;
                m_node = 0;
            }
            return;
        }
        m_node = m_first;

        while(m_node)
        {
            if(m_node->data() == ref)
            {
                if(m_node == m_first)
                {
                    m_first = m_node->next();
                }
                else if(m_node == m_last)
                {
                    m_last = prev;
                    m_last->setNext(0);
                }
                else
                {
                    prev->setNext(m_node->next());
                }
                delete m_node;
                m_node = m_last;
                break;
            }
            prev = m_node;
            next();
        }

    }
    /*! \brief Searches an item from the list and returns its containing node.
        \returns Pointer to node item.
    */
    gLinkedListNode<T,DA> *search(T *ref)
    {
        m_node = m_first;

        while(m_node)
        {
            if(m_node->data() == ref)
            {
                return m_node;
            }
            m_node->next();
        }
    }
    /*! \brief Copies an linked a list to this object.
        \param other: Linked list to copy.
    */
    virtual void copy(const gSharedObject *other)
    {
        gLinkedListShared<T,DA> *ol = (gLinkedListShared<T,DA> *)other;
        gLinkedListNode<T,DA> *mnode;
        T *val,*nval;
        DA allocator;
        clear();

        ol->setFirst();

        while(ol->node())
        {
            mnode = ol->node();
            val = mnode->data();
            if(val && allocator.isAllocator())
            {
                nval = allocator.alloc(*val);
            }
            else
            {
                nval = val;
            }
            append(nval);
            ol->next();
        }

    }

protected:
    /// First item of the list or node.
    gLinkedListNode<T,DA> *m_first;
    /// Current selected node of the list.
    gLinkedListNode<T,DA> *m_node;
    /// Last Node of the list.
    gLinkedListNode<T,DA> *m_last;
};

}
#endif // GLINKEDLISTSHARED_H
