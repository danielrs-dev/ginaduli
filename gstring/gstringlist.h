#ifndef GSTRINGLIST_H
#define GSTRINGLIST_H
/***********************************************************************
        GINA Duli C++ Framework
        Author: Daniel Rios
        File: gstringlist.h
        Description: Implementation of class gStringList
************************************************************************/
#include "gstring.h"
#include <containers/galignedptrlist.h>

namespace gcf
{
struct gStringSortA
{
    bool operator()(const gString *s1, const gString *s2) const
    {
        return (s1->compare(*s2) < 0);
    }
};
struct gStringSortD
{
    bool operator()(const gString *s1, const gString *s2) const
    {
        return (s1->compare(*s2) > 0);
    }
};
enum GSTRING_SORT
{
    GSSORT_ACCEND,
    GSSORT_DECEND
};
typedef gAlignedPtrList<gString,gDAllocator<gString> > gStringPtrList;
class gStringList: public  gStringPtrList
{
public:
    gStringList()
    {

    }
    gStringList(const gStringList &other):
        gStringPtrList(other)
    {

    }

    ~gStringList()
    {

    }
    virtual bool alloc(gu32 ncap)
    {
        gu32 i;
        bool ret = gStringPtrList::alloc(ncap);
        if(ret == false)
        {
            return false;
        }
        setUsed(ncap);

        for(i = 0; i < size(); i++)
        {
            setValue(new gString(),i);
        }
        return true;
    }
    void addString(const gString &str)
    {
        append(new gString(str));
    }
    void setString(const gString &str, gu32 index)
    {
        gString *vstr = value(index);
        if(vstr)
        {
            vstr->setString(str);
        }
    }
    gString &string(gu32 index)
    {
        gString *str = value(index);
        return (*str);
    }
    const gString &string(gu32 index) const
    {
        const gString *str = value(index);
        return (*str);
    }
    void sort(gs32 sortmode)
    {
        if(sortmode == GSSORT_ACCEND)
        {
            gStringPtrList::sort<gStringSortA>();
        }
        else
        {
            gStringPtrList::sort<gStringSortD>();
        }
    }

};
}

#endif // GSTRINGLIST_H
