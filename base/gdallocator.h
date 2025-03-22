#ifndef GDALLOCATOR_H
#define GDALLOCATOR_H

namespace gcf
{
/*! \brief Defines a non destructive deallocator for memory objects.
           This class is used in pointer containers when the container
           take owner ship of the item.
*/
template <class T>
struct gNDAllocator
{

    T *alloc(const T &obj)
    {
        GDUNUSED(obj);
        return 0;
    }
    /*! \brief Main function of deallocator. By defaul it does nothing.
        \param obj Object to deallocate.
    */

    void dalloc(T *obj)
    {
        GDUNUSED(obj);
    }
    bool isAllocator() const
    {
        return false;
    }

    /*! \brief Reports whether the deallocator actually deallocates or its
               not destructive.
        \return true if deallocator is destructive false if not
    */
    bool isDestructive() const
    {
        return false;
    }
};

/*! \brief Defines a destructive deallocator. This is handy when containers
           take ownership of every pointer object inside them.
*/
template <class T>
struct gDAllocator
{


    T *alloc(const T &obj)
    {
        return new T(obj);
    }
    /*! \brief Main function of object gDAllocator. It deallocates or frees memory
               given the pointer object as parameter.
        \param obj Pointer object to destroy.
    */
    void dalloc(T *ref)
    {
        delete ref;
    }
    bool isAllocator() const
    {
        return true;
    }
    /*! \brief Returns whether the deallocator destroy pointer data by operator()
        \return true if destrucive false if positive. This object always returns true
    */
    bool isDestructive() const
    {
        return true;
    }
};
}

#endif // GDALLOCATOR_H
