#ifndef GVARIANTLIST_H
#define GVARIANTLIST_H
#include <containers/galignedptrlist.h>
#include "gvariant.h"
namespace gcf
{
typedef gAlignedPtrList<gVariant,gDAllocator<gVariant> > gVariantPtrList;
class gVariantList : public gVariantPtrList
{
public:
    gVariantList()
    {

    }
    gVariantList(const gVariantList &other):
        gVariantPtrList(other)
    {

    }
    ~gVariantList()
    {

    }
    virtual bool alloc(gu32 ncap)
    {
        gu32 i;
        gVariant *val;
        if(gVariantPtrList::alloc(ncap))
        {
            setUsed(capacity());
            for(i = 0; i < size(); i++)
            {
                val = new gVariant();
                setValue(val,i);
            }
            return true;
        }
        return false;
    }
    void addVariant(const gVariant &val)
    {
        gVariant *nval = new gVariant(val);
        append(nval);
    }
    gVariant &variant(gu32 index)
    {
        gVariant *nval = value(index);

        return (*nval);

    }
    const gVariant &variant(gu32 index) const
    {
        const gVariant *nval = value(index);
        return (*nval);

    }
};
}
#endif // GVARIANTLIST_H
