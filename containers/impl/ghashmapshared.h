#ifndef GHASHMAPSHARED_H
#define GHASHMAPSHARED_H
/*****************************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File ghashmapshared.h
        Description: Implementation of the template class gHashMapShared
******************************************************************************/

#include <containers/glinkedlist.h>
#include <containers/galignedptrlist.h>
#include "ghashmapnode.h"
namespace gcf
{
template <class K, class V>
struct gHashMapKeyValue
{
    gHashMapKeyValue():
        value(0)
    {

    }
    gHashMapKeyValue(const K &nkey, V *nvalue):
        key(nkey),
        value(nvalue)
    {

    }

    K key;
    V *value;
};

/// Macro to make short of list map.
#define gHashMapList(K,V,D) gLinkedList<gHashMapNode<K,V,D>,gDAllocator<gHashMapNode<K,V,D> > >
#define gHashMapKVList(K,V) gAlignedPtrList<gHashMapKeyValue<K,V>, gDAllocator<gHashMapKeyValue<K,V> > >

/*! \brief The gHashMapShared is the base object part of the gHashMap class.
           It represents the shareable object and provides all function used
           by a hash map.
    \param K: Type of key used in the map.
    \param V: Type of data value used in the map.
    \param H: The standard hash function.
    \param D: The standard allocator deallocator.
*/
template <class K, class V,class H,class D >
class gHashMapShared: public gSharedObject
{
public:
    /// Standard constructor
    gHashMapShared()
    {

    }
    /*! \brief Constructor that initializes the data array of the map.
        \param datasize: Size of the data array.
    */
    gHashMapShared(gu32 datasize)
    {
        setup(datasize);
    }
    /// Standard destructor
    ~gHashMapShared()
    {

    }
    /*! \brief Initializes the data array.
        \param tablesize: Size of the data array.
    */
    void setup(gu32 tablesize)
    {
        if(tablesize == 0)
        {
            return;
        }
        m_data.alloc(tablesize);
        m_data.setUsed(tablesize);

    }
    /*! \brief Sets a values in the map.
        \param nkey: Key identificator of item.
        \param val: Item value.
    */
    void setValue(const K &nkey, V *val)
    {
        gu32 idx = hashFunc(nkey,m_data.size());
        V *v;
        gHashMapList(K,V,D) *item;
        gHashMapNode<K,V,D> *node;
        item = m_data.value(idx);

        if(item == 0)
        {
            return;
        }
        item->setFirst();
        while(item->node())
        {
            node = item->node()->data();
            if(node->key() == nkey)
            {
                v = node->value();
                if(v)
                {
                    D dealloc;
                    if(dealloc.isDestructive())
                    {
                        dealloc.dalloc(v);
                    }
                }
                node->setValue(val);
                break;
            }
            item->next();
        }


    }
    /*! \brief Adds an item to the map.
        \param nkey: Key of item value.
        \param val: Value of item.
    */
    void append(const K &nkey, V *val)
    {
        gu32 idx = hashFunc(nkey,m_data.size());

        gHashMapList(K,V,D) *item;
        gHashMapNode<K,V,D> *node;
        item = m_data.value(idx);
        if(item == 0)
        {
            item = new gHashMapList(K,V,D)();
            m_data.setValue(item,idx);
        }

        item->setFirst();
        while(item->node())
        {
            node = item->node()->data();
            if(node->key() == nkey)
            {
                return;
            }
            item->next();
        }
        item->append(new gHashMapNode<K,V,D>(nkey,val));
    }
    /*! \brief Gets a value given a key.
        \param nkey: Key value identificator of value.
        \return Value of found item or 0 if not found.
    */
    V *value(const K &nkey)
    {
        gu32 idx = hashFunc(nkey,m_data.size());

        gHashMapList(K,V,D) *item;
        gHashMapNode<K,V,D> *node;
        item = m_data.value(idx);
        if(item == 0)
        {
            return 0;
        }
        item->setFirst();
        while(item->node())
        {
            node = item->node()->data();
            if(node->key() == nkey)
            {
                return node->value();
            }
            item->next();
        }
        return 0;
    }
    const V *value(const K &nkey) const
    {
        gu32 idx = hashFunc(nkey,m_data.size());

        gHashMapList(K,V,D) *item;
        gHashMapNode<K,V,D> *node;
        item = (gHashMapList(K,V,D) *)m_data.value(idx);
        if(item == 0)
        {
            return 0;
        }
        item->setFirst();
        while(item->node())
        {
            node = item->node()->data();
            if(node->key() == nkey)
            {
                return node->value();
            }
            item->next();
        }
        return 0;
    }
    gHashMapKVList(K,V) values() const
    {
        gu32 i;
        gHashMapList(K,V,D) *item;
        gHashMapNode<K,V,D> *node;
        gAlignedPtrList<gHashMapKeyValue<K,V>,
                        gDAllocator<gHashMapKeyValue<K,V> > > vals;
        for(i = 0; i < m_data.size(); i++)
        {
            item = (gHashMapList(K,V,D) *)m_data.value(i);
            if(item == 0)
            {
                continue;
            }
            item->setFirst();
            while(item->node())
            {
                node = item->node()->data();
                vals.append(new gHashMapKeyValue<K,V>(node->key(),node->value()));
                item->next();
            }
        }
        vals.setShared(true);
        return vals;
    }
    /// Returns whether map contains a key a value pair
    bool contains(const K &key) const
    {
        const V *val = value(key);
        return val != 0;
    }

    /*! \brief Removes an item from the map.
        \param nkey: Item key to remove.
    */
    void remove(const K &nkey)
    {
        gu32 idx = hashFunc(nkey,m_data.size());

        gHashMapList(K,V,D) *item;
        gHashMapNode<K,V,D> *node;
        item = m_data.value(idx);
        if(item == 0)
        {
            return;
        }
        item->setFirst();
        while(item->node())
        {
            node = item->node()->data();
            if(node->key() == nkey)
            {
                item->remove();
                return;
            }
            item->next();
        }
    }
    void clear()
    {
        m_data.clear();
    }
    /*! \brief Copies a hash map to this object.
        \param other: Map to copy from.
    */
    virtual void copy(const gSharedObject *other)
    {
        gHashMapShared<K,V,H,D> *ol =(gHashMapShared<K,V,H,D> *)other;
        V *val,*nval;
        D allocator;
        clear();
        const gu32 msize = ol->m_data.size();
        gu32 i;
        gHashMapList(K,V,D) *mlist;
        gHashMapList(K,V,D) *nlist;
        gHashMapNode<K,V,D> *mnode;
        gHashMapNode<K,V,D> *nnode;
        m_data.alloc(msize);
        m_data.setUsed(msize);
        m_data.zeros();
        for(i = 0; i < msize;i++)
        {
            mlist = ol->m_data.value(i);
            if(mlist)
            {
                nlist = new gHashMapList(K,V,D)();
                mlist->setFirst();

                while(mlist->node())
                {
                    mnode = mlist->node()->data();
                    val = mnode->value();
                    if(allocator.isAllocator() && val)
                    {
                        nval = allocator.alloc(*val);
                    }
                    else
                    {
                        nval = val;
                    }
                    nnode = new gHashMapNode<K,V,D>(mnode->key(),nval);
                    nlist->append(nnode);
                    mlist->next();
                }
                m_data.setValue(nlist,i);
            }

        }
    }

protected:
    /// All hash map data.
    gAlignedPtrList<gHashMapList(K,V,D)> m_data;
    /// Hash function.
    H hashFunc;
};
}

#endif // GHASHMAPSHARED_H
