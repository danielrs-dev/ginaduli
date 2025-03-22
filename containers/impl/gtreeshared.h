#ifndef GTREESHARED_H
#define GTREESHARED_H
/*****************************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File gtreeshared.h
        Description: Implementation of the template class gTreeShared.
******************************************************************************/

#include "gtreenode.h"
#include "gtreelevel.h"

namespace gcf
{
/*! \brief The gTreeShared class is the object property held by gTree that
           provides all the functionality of trees. This class is shareable.
    \param T: Type of user data the tree stores.
    \param D: Type allocator-dealloctor.
*/
template <class T, class D>
class gTreeShared: public gSharedObject
{
public:
    /// Main constructor.
    gTreeShared():
        m_master(new gTreeNode<T,D>(0)),
        m_node(m_master),
        m_level(1),
        m_lastlevel(0),
        m_walknode(0)
    {

    }
    /// Destructor
    ~gTreeShared()
    {
        clear();
    }
    /// Clears or deletes the tree.
    void clear()
    {
        m_master->clear();
        delete m_master;
    }
    /*! \brief Appends a child to the current selected node of the tree.
        \param ref: User data of child to add.
    */
    void appendChild(T *ref)
    {
        m_node->appendChild(ref);
    }
    /// Selects the next child from the current selected node.
    void nextChild()
    {
        m_node->nextChild();
    }
    /// Selects the first child from the current selected node.
    void firstChild()
    {
        m_node->firstChild();
    }
    /// Selects the last child from the current selected node.
    void lastChild()
    {
        m_node->lastChild();
    }
    /// Moves the current selected node to its father.
    void setFather()
    {
        m_node = m_node->father();
    }
    /// Moves the current selected node to the selected child.
    void setChild()
    {
        m_node = m_node->child();
    }
    /*! \brief Gets the current selected node.
        \param Reference pointer of current node.
    */
    gTreeNode<T,D> *node()
    {
        return m_node;
    }
    /*! \brief Gets the current selected child from the selected node.
        \return Reference pointer of child node.
    */
    gTreeNode<T,D> *childNode()
    {
        return m_node->child();
    }
    bool hasChilds() const
    {
        return m_node->hasChilds();
    }
    /*! \brief Sets the user data to current selected node.
        \param ndata: Data to set to node.
    */
    void setData(T *ndata)
    {
        m_node->setData(ndata);
    }
    void setMasterData(T *ndata)
    {
        m_master->setData(ndata);
    }
    /*! \brief Sets the user data to current selected child node
               from the selected node.
        \param ndata: Data to set to node.
    */
    void setChildData(T *ndata)
    {
        childNode()->setData(ndata);
    }
    /*! \brief Returns the user data of the selected node.
        \return User data.
    */
    T *data()
    {
        return m_node->data();
    }
    /// Const version of gTreeShared::data()
    const T *data() const
    {
        return m_node->data();
    }
    /*! \brief Gets the user data from the selected child node from the
               selected node.
        \return User data.
    */
    T *childData()
    {
        return childNode()->data();
    }
    /// Const version of gTreeShared::childData()
    const T *childData() const
    {
        return childNode()->data();
    }
    /// Moves the selected to the master of the tree.
    void setMaster()
    {
        m_level = 1;
        m_lastlevel = 0;
        m_walknode = 0;
        m_node = m_master;
    }
    /*! \brief Gets the master node.
        \return Reference pointer of the master node.
    */
    gTreeNode<T,D> *master()
    {
        return m_master;
    }
    /// Removes the current selected node from the tree.
    void remove()
    {
        gTreeNode<T,D> *nfather = m_node->father();
        nfather->removeChild(m_node);
        m_node = nfather;
    }
    /*! \brief Copies a tree to this object.
        \param other: Tree to copy from.
     */
    virtual void copy(const gSharedObject *other)
    {
        gTreeShared<T,D> *ol = (gTreeShared<T,D> *)(other);
        m_master->copy(ol->master());
    }
    /*! \brief Walks through the tree in linear way.
        \return Item found while walking.
    */
    T *walk()
    {
        T *ret;
        gTreeNode<T,D> *lnode;
        bool done = false;
        while(done == false)
        {
            if(m_level <= m_lastlevel)
            {
                nextChild();
            }
            if(m_level > m_lastlevel)
            {
                firstChild();
            }
            m_lastlevel = m_level;
            lnode = childNode();
            if(lnode)
            {
                setChild();
                if(hasChilds())
                {
                    m_level++;
                }
                else
                {
                    setFather();
                }
                done = true;
            }
            else
            {
                m_level--;
                if(m_level)
                {
                    setFather();
                }
                else
                {
                    done = true;
                }
            }
        }
        if(m_level)
        {
            m_walknode = lnode;
            ret = lnode->data();
            return ret;
        }
        else
        {
            setMaster();
            return 0;
        }
    }
    /*! \brief Registers a "level" in an internal list.
        \param The integer ID to register.
    */
    void addLevel(gs32 nid)
    {
        gTreeLevel *nlevel = level(nid);
        if(nlevel)
        {
            return;
        }
        nlevel= new gTreeLevel(m_level);
        nlevel->setLevelID(nid);
        m_levels.append(nlevel);
    }
    void addLevel(const gString &sid)
    {
        gTreeLevel *nlevel = level(sid);
        if(nlevel)
        {
            return;
        }
        nlevel= new gTreeLevel(m_level);
        nlevel->setLevelID(sid);
        m_levels.append(nlevel);
    }

    gTreeLevel *level(gs32 nid)
    {
        gTreeLevel *ret;
        m_levels.setFirst();
        while(m_levels.node())
        {
            ret = m_levels.value();
            if(ret->levelID() == nid)
            {
                return ret;
            }
            m_levels.next();
        }
        return 0;
    }
    gTreeLevel *level(const gString &sid)
    {
        gTreeLevel *ret;
        m_levels.setFirst();
        while(m_levels.node())
        {
            ret = m_levels.value();
            if(ret->stringLevelID() == sid)
            {
                return ret;
            }
            m_levels.next();
        }
        return 0;
    }
    void removeLevel(gs32 nid)
    {
        gTreeLevel *ret;
        m_levels.setFirst();
        while(m_levels.node())
        {
            ret = m_levels.value();
            if(ret->levelID() == nid)
            {
                m_levels.remove();
                return;
            }
            m_levels.next();
        }

    }
    void removeLevel(const gString &sid)
    {
        gTreeLevel *ret;
        m_levels.setFirst();
        while(m_levels.node())
        {
            ret = m_levels.value();
            if(ret->stringLevelID() == sid)
            {
                m_levels.remove();
                return;
            }
            m_levels.next();
        }
    }
    bool inLevel(gs32 nid)
    {
        gTreeLevel *nlevel;
        m_levels.setFirst();
        while(m_levels.node())
        {
            nlevel = m_levels.value();
            if(nlevel->levelID() == nid)
            {
                return (nlevel->level() >= m_level);
            }
            m_levels.next();
        }
        return false;
    }
    bool inLevel(const gString &str)
    {
        gTreeLevel *nlevel;
        m_levels.setFirst();
        while(m_levels.node())
        {
            nlevel = m_levels.value();
            if(nlevel->stringLevelID() == str)
            {
                return (nlevel->level() >= m_level);
            }
            m_levels.next();
        }
        return false;
    }
    void clearLevels()
    {
        m_levels.clear();
    }
    gs32 walkLevel()const
    {
        return m_level;
    }
    gTreeNode<T,D> *walkNode()
    {
        return m_walknode;
    }
    T *walkData()
    {
        return m_walknode->data();
    }

protected:
    /// Master node
    gTreeNode<T,D> *m_master;
    /// Selected node.
    gTreeNode<T,D> *m_node;
    /// List levels
    gLinkedList<gTreeLevel,gDAllocator<gTreeLevel> > m_levels;
    /// Current level for walk function
    gs32 m_level;
    /// Last level
    gs32 m_lastlevel;
    /// Walknode
    gTreeNode<T,D> *m_walknode;
};
}

#endif // GTREESHARED_H
