#ifndef GALGORITHM_H
#define GALGORITHM_H
/**************************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File: galgorithm.h
        Description: Implementation of sort of number of algorithms.
***************************************************************************/

#include <base/gcommon.h>
namespace gcf
{
/*! \brief Sort comparative class function.
    \param T: Type of values to compare.
*/
template <class T>
struct gSortCompare
{
    /*! \brief Compares two values.
        \param val1: Value 1.
        \param val2: Value 2.
        \return true if comparison rules match users desire.
                This example class returns whether val1 is
                minor than val2.
     */
    bool operator()(const T &val1, const T &val2) const
    {
        return (val1 < val2);
    }
};
/// Holdas a set functions and instructions that perform different algorithms.
struct gAlgorithm
{
    template <class T, class gSortFunc>
    static void sort(T *list, gu32 size)
    {
        gu32 i = 0;
        gu32 j = 0,topIndex = 0;
        T p1 = 0 ,p2 = 0 ,top = 0;
        bool bDiffValue=true;
        gSortFunc sortfunc;
        while(i < size)
        {
            if(j  < size)
            {
                p1 = list[i];
                p2 = list[j];
            }
            if(j == i)
            {
                top = p1;
                topIndex = j;
                bDiffValue = false;
            }
            if(sortfunc(p2,top))
            {
                top = p2;
                topIndex = j;
                bDiffValue = true;
            }
            if(j == size)
            {
                if(bDiffValue)
                {

                    p1 = list[i];
                    list[i] = top;
                    list[topIndex] = p1;
                }
                i++;
                j = i;
            }
            else
            {
                j++;
            }
        }
    }


};

}


#endif // GALGORITHM_H
