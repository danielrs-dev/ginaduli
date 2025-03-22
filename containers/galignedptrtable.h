#ifndef GALIGNEDPTRTABLE_H
#define GALIGNEDPTRTABLE_H
#include "impl/galignedptrtableshared.h"
namespace gcf
{
template <class T, class A = gNDAllocator<T> >
class gAlignedPtrTable: public gSharedObjectModel<gAlignedPtrTableShared<T,A> >
{
public:
    gAlignedPtrTable()
    {

    }
    gAlignedPtrTable(const gAlignedPtrTable<T,A> &other):
        gSharedObjectModel<gAlignedPtrTableShared<T,A> >(other)
    {

    }
    ~gAlignedPtrTable()
    {

    }
    virtual void alloc(gu32 nwidth, gu32 nheight)
    {
        if(this->d == 0)
        {
            this->d = new gAlignedPtrTableShared<T,A>();
        }
        this->d->alloc(nwidth, nheight);
    }
    void allocColumns(gu32 rowindex, gu32 numcolumns)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->allocColumns(rowindex,numcolumns);
    }
    void allocRows(gu32 numrows)
    {
        if(this->d == 0)
        {
            this->d = new gAlignedPtrTableShared<T,A>();
        }
        this->d->allocRows(numrows);
    }

    void appendRow()
    {
        if(this->d == 0)
        {
            this->d = new gAlignedPtrTableShared<T,A>();
        }
        this->d->appendRow();
    }
    void append(T *ref ,gu32 xrow)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->append(ref, xrow);
    }
    void setValue(T *ref, gu32 xrow, gu32 ycol, bool freeold)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->setValue(ref,xrow,ycol,freeold);
    }
    T *value(gu32 xrow, gu32 ycol)
    {
        if(this->d == 0)
        {
            return 0;
        }
        this->d->value(xrow,ycol);
    }
    const T *value(gu32 xrow, gu32 ycol) const
    {
        if(this->d == 0)
        {
            return 0;
        }
        this->d->value(xrow,ycol);
    }
    void removeRow(gu32 xrow)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->removeRow(xrow);
    }
    void remove(gu32 xrow, gu32 ycol)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->remove(xrow,ycol);
    }
    void remove(T *ref, gu32 xrow)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->remove(ref, xrow);
    }
    void fastRemove(gu32 xrow, gu32 ycol)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->fastRemove(xrow,ycol);
    }
    void fastRemove(T *ref, gu32 xrow)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->fastRemove(ref, xrow);
    }
    bool contains(T *ref, gu32 xrow, gu32 *indexout) const
    {
        if(this->d == 0)
        {
            return false;
        }
        return this->d->contains(ref,xrow,indexout);
    }
    bool contains(const T &ref, gu32 xrow, gu32 *indexout) const
    {
        if(this->d == 0)
        {
            return false;
        }
        return this->d->contains(ref,xrow,indexout);
    }
    gu32 rows() const
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->rows();
    }
    gu32 columns(gu32 xrow) const
    {
        if(this->d == 0)
        {
            return 0;
        }
        return this->d->columns(xrow);
    }
    void setUsedRows(gu32 val)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->setUsedRows(val);
    }
    void setUsedColumns(gu32 val, gu32 xrow)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->setUsedColumns(val,xrow);
    }
    template <class SF>
    void sort(gu32 xrow)
    {
        if(this->d == 0)
        {
            return;
        }
        this->d->sort<SF>(xrow);
    }
    gAlignedPtrTable<T,A> &operator = (const gAlignedPtrTable<T,A> &other)
    {
        assign(other);
        return *this;
    }
};
}
#endif // GALIGNEDPTRTABLE_H
