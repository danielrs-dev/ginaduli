#ifndef GARRAY_H
#define GARRAY_H
/*****************************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File: garray.h
        Description: Implementation of template class gArray
******************************************************************************/
#include <base/gcommon.h>

namespace gcf
{
/*! \brief The gArray is a base of object of hte GINA DULI C++ Frame work
           which represents a container of a fixed array of type T.
           The size of the array gets declared on template so pretty much
           like declaring a variable such as var[10].

   \param T: Type of data the array would be stored.
   \param N: The size of the array.
*/
template<class T,int N>
class gArray
{
public:
    /// Standard constructor.
    gArray()
    {

    }
    /*! \brief Copy constructor.
        \param Array to copy from.
    */
    gArray(const gArray<T,N> &other)
    {
        copy(other);
    }
    /// Destructor.
    ~gArray()
    {
    }
    /*! \brief Copies another array to this array.
        \param other: Array to be copied.
     */
    void copy(const gArray<T,N> &other)
    {
        gu32 i;
        for(i = 0; i < N; i++)
        {
            m_data[i] = other.m_data[i];
        }

    }
    /*! \brief Copies a plain array to this array
        \param arr: Pointer to array to copy. Notice array should be
                    the same size to prevent issues.
    */
    void copy(const T *arr)
    {
        gu32 i;
        for(i = 0; i < N; i++)
        {
            m_data[i] = arr[i];
        }
    }
    /*! \brief Gets a value from the array given an index.
        \param index: Index of array to get value from.
        \return Reference to value.
    */
    T &value(gu32 index)
    {
        return m_data[index];
    }
    /// Const version of gArray::value(index)
    const T &value(gu32 index) const
    {
        return m_data[index];
    }
    /*! \brief Sets a value in the array given an index. Old value gets replaced.
        \param val: New value to set.
        \param index: Index of array to store value.
    */
    void setValue(const T &val, gu32 index)
    {
        m_data[index] = val;
    }
    /*! \brief Sets the entire array to a single value.
        \param val: Value to set.
    */
    void setValues(const T &val)
    {
        gu32 i;
        for(i = 0; i < N;i++)
        {
            m_data[i] = val;
        }
    }
    /*! \brief Gets the size of the array. It basically returns the parameter
               from the template.
        \return Size of array.
    */
    gu32 size() const
    {
        return N;
    }
    /*! \brief Gets the array pointer.
        \return Array pointer of type T.
     */
    T *data()
    {
        return m_data;
    }
    /// Const version of gArray::data()
    const T *data() const
    {
        return m_data;
    }
    /// Pretty the same as gArray::value(index)
    T &operator [] (gu32 index)
    {
        return value(index);
    }
    /// Const version of operator[]
    const T &operator[] (gu32 index) const
    {
        return value(index);
    }

protected:
    /// Array data of type T.
    T m_data[N];
};


}


#endif // GARRAY_H
