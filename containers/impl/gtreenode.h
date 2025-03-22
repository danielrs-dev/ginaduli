#ifndef GTREENODE_H
#define GTREENODE_H
/*****************************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File gtreenode.h
        Description: Implementation of the template class gTreeNode.
******************************************************************************/


#include <containers/glinkedlist.h>
#include <gstring/gstring.h>

namespace gcf
{

/*! \brief The gTreeNode class represents a node item of gTree object.
           It holds all data referencing the tree object:
           -User data.
           -Child nodes.
   \param T: Type of user data stored by the tree.
   \param D: Type of allocator deallocator.
*/
template <class T, class D>
class gTreeNode
{
public:
    /*! \brief Main constructor. It takes the father node as parameter.
        \param nfather: Father node holding this node as a child.
                        Set it to 0 if this is the master node of the tree.
    */
    gTreeNode(gTreeNode<T,D> *nfather):
        m_data(0),
        m_father(nfather)
    {

    }
    /// Destructor
    ~gTreeNode()
    {
        clear();
    }
    /// Clears the tree.
    void clear()
    {
        D dealloc;
        m_childs.clear();
        if(dealloc.isDestructive())
        {
            if(m_data)
            {
                dealloc.dalloc(m_data);
            }
        }
    }
    /*! \brief Appends a child node to the end of the list of child node.
        \param ndata: User data of the new node.
    */
    void appendChild(T *ndata)
    {
        gTreeNode<T,D> *nnode = new gTreeNode<T,D>(this);
        nnode->setData(ndata);
        m_childs.append(nnode);
    }
    /// Removes a child node list of childs.
    /// It removes the currect selected child node.
    void removeChild()
    {
       m_childs.remove();
    }
    /*! \brief Removes a child given its reference.
        \param rchild: Child node to remove from the tree.
    */
    void removeChild(gTreeNode<T,D> *rchild)
    {
        m_childs.remove(rchild);
    }
    /// Selects the first child.
    void firstChild()
    {
        m_childs.setFirst();
    }
    /// Selects the last child.
    void lastChild()
    {
        m_childs.setLast();
    }
    /// Sets the next child as current child node.
    void nextChild()
    {
        m_childs.next();
    }
    /*! \brief Gets the current selected child from the child list.
        \return Reference of node child.
    */
    gTreeNode<T,D> *child()
    {
        return m_childs.value();
    }
    /*! \brief Gets the father node of this node.
        \return Reference of father node.
    */
    gTreeNode<T,D> *father()
    {
        return m_father;
    }
    /*! \brief Returns whether this node has childs or not.
        \return true if node has childs else false.
    */
    bool hasChilds() const
    {
        return m_childs.isEmpty() == false;
    }
    /*! \brief Sets the user data of the node.
        \param ndata: User data.
    */
    void setData(T *ndata)
    {
        m_data = ndata;
    }
    /*! \brief Gets the user data of this node.
        \return Reference of user data.
     */
    T *data()
    {
        return m_data;
    }
    /// Const version gTreeNode::data()
    const T *data() const
    {
        return m_data;
    }
    /*! \brief Copies a tree node to this node.
        \param other: TreeNode to copy from.
    */
    void copy(gTreeNode<T,D> *ol)
    {
        D alc;
        gTreeNode<T,D> *nn,*pn;

        if(alc.isAllocator() && ol->m_data)
        {
            m_data = alc.alloc(*ol->m_data);
        }
        else
        {
            m_data = ol->m_data;
        }
        ol->m_childs.setFirst();
        while(ol->m_childs.node())
        {
            nn = ol->m_childs.value();
            pn = new gTreeNode<T,D>(this);
            pn->copy(nn);
            m_childs.append(pn);
            ol->m_childs.next();
        }
    }

protected:
    /// User data of type T.
    T *m_data;
    /// List of child nodes
    gLinkedList<gTreeNode<T,D>,gDAllocator<gTreeNode<T,D> > > m_childs;
    /// Reference to the father node.
    gTreeNode<T,D> *m_father;
    /// Level of this node
    gs32 m_ilevel;
};
}

#endif // GTREENODE_H
