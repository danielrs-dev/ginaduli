#ifndef GLINKEDLISTNODE_H
#define GLINKEDLISTNODE_H

/*****************************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File glinkedlistnode.h
        Description: Implementation of the template class gLinkedListNode
******************************************************************************/
#include <base/gdallocator.h>

namespace gcf
{
/*! \brief The gLinkedListNode represents an item of a linked list. It holds
           the user data.
    \param T Type of data held by the linked list
    \param DA Standard allocator - deallocator
*/
template<class T, class DA = gNDAllocator<T> >
class gLinkedListNode
{
public:
    /// Standard constructor
    gLinkedListNode():
        m_data(0),
        m_next(0)
    {

    }
    /// Standard destructor. If a deallocator was set. It is called to destroy
    /// the user data.
    ~gLinkedListNode()
    {
        DA dealloc;
        if(dealloc.isDestructive())
        {
            dealloc.dalloc(m_data);
        }
    }
    /*! \brief Sets the user data.
        \param ref: Pointer to user data.
    */
    void setData(T *ref)
    {
        m_data = ref;
    }
    /*! \brief Returns the user data.
        \return Pointer to user data of type T.
     */
    T *data()
    {
        return m_data;
    }
    /// Const version of gLinkedListNode::data()
    const T *data() const
    {
        return m_data;
    }
    /*! \brief Sets the pointer of the "next" item of the linked list.
        \param pnext: Pointer to the next item of the list.
    */
    void setNext(gLinkedListNode<T,DA> *pnext)
    {
        m_next = pnext;
    }
    /*! \brief Returns the "next" pointer or item of the linked list.
        \returns Pointer to the "next" item or node of the linked list.
    */
    gLinkedListNode<T,DA> *next()
    {
        return m_next;
    }

protected:
    /// User data of type T.
    T *m_data;
    /// The following or next node of the linked list.
    gLinkedListNode<T,DA> *m_next;
};
}
#endif // GLINKEDLISTNODE_H
