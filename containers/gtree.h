#ifndef GTREE_H
#define GTREE_H
/*****************************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File gtree.h
        Description: Implementation of the template class gTree.
******************************************************************************/

#include "impl/gtreeshared.h"
#include <base/gsharedobjectmodel.h>
namespace gcf
{
/*! \brief The template class gTree is a base container of the
           GINA DULI C++ Framework. It is data structure holder
           of type of tree.
           It works like any tree.
           Data is hold by nodes. Each node has its child nodes and so on.
           Internally it uses linked lists to hold child nodes.
           User data is always a ponter of type T.
           User data can be deallocated from memory if a destructive
           deallocator is specified on the template.
           Selecting data from the tree in a way of node selection mode
           where selected node is referenced always by most of the working
           function members.
           This is pretty much alike gLinkedList.
           Navigation through the tree happens by moving the selection node from
           node to node.
    \param T: User data type.
    \param D: User data deallocator and allocator. Used while copying and
              removing user data.
 */
template <class T, class D>
class gTree: public gSharedObjectModel<gTreeShared<T,D> >
{
public:
    /// Standard constructor
    gTree()
    {

    }
    /*! \brief Copy constructor.
        \param other: Tree to copy from.
    */
    gTree(const gTree<T,D> &other):
        gSharedObjectModel<gTreeShared<T,D> >(other)
    {

    }
    /// Destructor
    ~gTree()
    {

    }
    /*! \brief Adds a child to the selected node of the tree.
        \param ref: User data to add.
    */
    void appendChild(T *ref)
    {
        if(this->d == 0)
        {
            this->d = new gTreeShared<T,D>();
        }
        this->d->appendChild(ref);
    }
    /// Moves the selected child to the next on the child list of selected
    /// node.
    void nextChild()
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->nextChild();
    }
    /// Selects the first child from list of child node of the selected node.
    void firstChild()
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->firstChild();
    }
    /// Selects the last child from the list of child node of the selected node.
    void lastChild()
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->lastChild();
    }
    /// Moves the selected node to the father of the current node.
    void setFather()
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->setFather();
    }
    /// Moves the selected node to the selected child of the current node.
    void setChild()
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->setChild();
    }
    /*! \brief Gets the current selected node pointer.
        \return Reference pointer of current selected node.
    */
    gTreeNode<T,D> *node()
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->node();
    }
    /*! \brief Gets the current selected child node from the selected node.
        \return Reference pointer of child node.
    */
    gTreeNode<T,D> *childNode()
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->childNode();
    }
    /*! \brief Sets the user data of the current node.
        \param ndata: User data.
    */
    void setData(T *ndata)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->setData(ndata);
    }
    void setMasterData(T *ndata)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->setMasterData(ndata);
    }

    /*! \brief Sets the user data of the current child of the selected node.
        \param ndata: User data.
    */
    void setChildData(T *ndata)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->setChildData(ndata);
    }
    /*! \brief Gets the user data from the current node.
        \return User data.
    */
    T *data()
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->data();
    }
    /// Const version of gTree::data()
    const T *data() const
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->data();
    }
    /*! \brief Gets the user data of the current child of the selected node.
        \return User data.
    */
    T *childData()
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->childData();
    }
    /// Const version of gTree::childData()
    const T *childData() const
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->childData();
    }
    bool hasChilds() const
    {
        if(this->d == 0)
        {
            return false;
        }
        return this->d->hasChilds();
    }
    /// Selects the current node to the master one.
    void setMaster()
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->setMaster();
    }
    /*! \brief Gets the master node reference pointer.
        \return Master node reference pointer.
    */
    gTreeNode<T,D> *master()
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->master();
    }
    /// Removes the current node.
    void remove()
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->remove();
    }
    /*! \brief Copies one tree to this tree object.
        \param other: Tree object to copy from.
    */
    gTree<T,D> &operator = (const gTree<T,D> &other)
    {
        this->assign(other);
        return *this;
    }
    T *walk()
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->walk();
    }
    T *walkData()
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->walkData();
    }
    void addLevel(gs32 nid)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->addLevel(nid);
    }
    void addLevel(const gString &sid)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->addLevel(sid);
    }
    gTreeLevel *level(gs32 nid)
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->level(nid);
    }
    gTreeLevel *level(const gString &sid)
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->level(sid);
    }
    void removeLevel(gs32 nid)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->removeLevel(nid);
    }
    void removeLevel(const gString &sid)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->removeLevel(sid);
    }
    void clearLevels()
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->clearLevels();
    }
    bool inLevel(gu32 nid)
    {
        if(this->d == 0)
        {
            return false;
        }
        return this->d->inLevel(nid);
    }
    bool inLevel(const gString &sid)
    {
        if(this->d == 0)
        {
            return false;
        }
        return this->d->inLevel(sid);
    }
};
}

#endif // GTREE_H
