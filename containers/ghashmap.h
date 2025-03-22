#ifndef GHASHMAP_H
#define GHASHMAP_H
/*****************************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File ghashmap.h
        Description: Implementation of the template class gHashMap.
******************************************************************************/

#include "impl/ghashmapshared.h"
#include <base/gsharedobjectmodel.h>
#include <gstring/gstring.h>
namespace gcf
{
/*! \brief Basic hash function.
    \param K: Type of key.
*/
template <class K>
struct gHashFunction
{
    /*! \brief Function that supplies the hash value for the map.
        \param val: Key to generate hash.
        \param nsize: Size of data array of map.
        \return Hash value.
    */
    gu32 operator()(const K &val, gu32 nsize)
    {
        return val % nsize;
    }
};
/*! \brief Hash Function that takes a string as key.
  */
struct gHashStringFunction
{
    /*! \brief Function that supplies the hash value to the map.
        \param key: Key string value.
        \param nsize: Size of the data array of the map.
        \return Hash value.
    */
    gu32 operator()(const gString &key, gu32 nsize) const
    {
        return (key.hash()) % nsize;
    }
};
/*! \brief The gHashMap class is a base container of the GINA DULI C++ Framework.
           It works storing data based on a map of key and values.
           Keys are identification system to reference the value in the map.
           Internally it stores in a fixed array which data is indexed
           by the hashkey calculated from the Key parameter. This is done
           by hash function set by the template parameter H.
           It basically works like this.
            \code
            itemlist = dataarray[hashfunction(key,arraysize)];
            \code
            Each dataarray item is a pointer to a linked list which holds
            user data in form of nodes.
            This is because collision could happend when key values generate
            the same hashkey value.
            Values in the gHashMap class are just pointers to whatever the
            user want to store.
            This pointer can be deleted if the user specifies a destructive
            deallocator on the parameter D of the template.
    \param K: Type of key value.
    \param V: Type of value or data.
    \param H: Hash function.
    \param D: Deallocator allocator.
 */

template <class K,
          class V,
          class H = gHashFunction<K>,
          class D = gNDAllocator<V> >
class gHashMap: public gSharedObjectModel<gHashMapShared<K,V,H,D> >
{
public:
    /// Standard constructor
    gHashMap()
    {

    }
    /*! \brief Constructor that initializes the data array of the map.
        \param datasize: Size of the data array.
    */
    gHashMap(gu32 datasize)
    {
        setup(datasize);
    }
    /*! \brief Copy constructor.
        \param other: Map to copy from.
    */
    gHashMap(const gHashMap<K,V,H,D> &other):
        gSharedObjectModel<gHashMapShared<K,V,H,D> >(other)
    {

    }
    /// Destructor
    ~gHashMap()
    {

    }
    /*! \brief Initializes the data array of the map.
        \param nsize: Size of the data array.
    */
    void setup(gu32 nsize)
    {
        if(this->d == 0)
        {
            this->d = new gHashMapShared<K,V,H,D>();
        }
        this->d->setup(nsize);
    }
    /*! \brief Adds an item to the hash map.
        \param key: Key value of the item.
        \param val: Value of item.
    */
    void append(const K &key,V *val)
    {
        if(this->d == 0)
        {
            this->d = new gHashMapShared<K,V,H,D>();
        }
        this->d->append(key,val);
    }
    /*! \brief Sets an item to the hash map given its key.
               Notice if key was not set before function does nothing.
               Previous value gets replaced.
        \param key: Key value of the item.
        \param val: Value of item.
    */
    void setValue(const K &key, V *val)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->setValue(key,val);
    }
    /*! \brief Gets an item value from the map. If not found it returns
               0 or null.
        \param Key value of item to find.
        \return Found value or 0 if not found.
    */
    V *value(const K &key)
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->value(key);
    }
    /// Const version of value()
    const V *value(const K &key) const
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->value(key);
    }
    gHashMapKVList(K,V) values() const
    {
        if(this->d == 0)
        {
            return gHashMapKVList(K,V)();
        }
        return this->d->values();
    }

    /// Returns whether map contains a key a value pair
    bool contains(const K &key) const
    {
        if(this->d == 0)
        {
            return false;
        }
        return this->d->contains(key);
    }
    /*! \brief Removes an item from the hash map. If destructive deallocator
               is set then item value data gets deallocated.
        \param key: Key of item to remove.
    */
    void remove(const K &key)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->remove(key);
    }
    /*! \brief Copies a map to this map using the operator =.
        \param other: Map to copy from.
        \return Reference to this map.
    */
    gHashMap<K,V,H,D> &operator = (const gHashMap<K,V,H,D> &other)
    {
        this->assign(other);
        return *this;
    }

};
}
#endif // GHASHMAP_H
