#ifndef GHASHMAPNODE_H
#define GHASHMAPNODE_H
/*****************************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File ghashmapnode.h
        Description: Implementation of the template class gHashMapNode
******************************************************************************/

#include <base/gdallocator.h>
namespace gcf
{
/*! \brief The gHashMapNode class represents an item of a gHashMap container.
           This template holds both properties the Key and the Data of map.
    \param K: Key of the item.
    \param V: Value or item data of the class.
    \param D: Deallocator of the item data of the class.
*/
template <class K, class V, class D>
class gHashMapNode
{
public:
    /*! \brief Main constructor.
        \param nkey: Key value of node.
        \param nvalue: Data or value of the node.
     */
    gHashMapNode(const K &nkey, V *nvalue):
        m_key(nkey),
        m_value(nvalue)
    {

    }
    /// Destructor. It remoeves or deallocates user data if deallocatot is
    /// specified in the template parameter.
    ~gHashMapNode()
    {
        D dealloc;
        if(dealloc.isDestructive())
        {
            dealloc.dalloc(m_value);
        }

    }
    /*! \brief Returns the key of item node.
        \return Reference of key value.
    */
    const K &key() const
    {
        return m_key;
    }
    /*! \brief Returns the value or data of item node.
        \return Item node value.
    */
    V *value()
    {
        return m_value;
    }
    /// Const version of gHashMapNode::value()
    const V *value() const
    {
        return m_value;
    }
    /*! \brief Sets a new value or data.
        \param nval: New value to set.
    */
    void setValue(V *nval)
    {
        m_value = nval;
    }

protected:
    /// Key property of type K
    K m_key;
    /// Value or data propertyo of type V
    V *m_value;
};
}
#endif // GHASHMAPNODE_H
