#ifndef GALIGNEDPTRTABLESHARED_H
#define GALIGNEDPTRTABLESHARED_H
#include "containers/galignedptrlist.h"

namespace gcf
{

template <class T, class A>
class gAlignedPtrTableShared : public gSharedObject
{
public:
    typedef gAlignedPtrList<T,A> gTableRow;
    typedef gAlignedPtrList<gTableRow, gDAllocator<gTableRow> > gTableData;

    void alloc(gu32 nwidth, gu32 nheight)
    {
        gu32 i;
        gTableRow *prow;
        m_data.alloc(nwidth);
        m_data.setUsed(nwidth);
        for(i = 0; i <nwidth; i++)
        {
            prow = new gTableRow;
            prow->alloc(nheight);
            m_data.setValue(prow,i,false);
        }
    }
    void allocColumns(gu32 rowindex, gu32 numcolumns)
    {
        gTableRow *prow = m_data.value(rowindex);
        if(prow)
        {
            prow->alloc(numcolumns);
        }
    }
    void allocRows(gu32 numrows)
    {
        gTableRow *prow;
        gu32 i;
        m_data.alloc(numrows);
        m_data.setUsed(numrows);
        for(i = 0; i < numrows; i++)
        {
            prow = new gTableRow();
            m_data.setValue(prow,i,false);
        }
    }

    virtual void clear()
    {
        m_data.clear();
    }
    virtual void copy(const gSharedObject *other)
    {
        const gAlignedPtrTableShared<T,A> *table =
                other->cast<gAlignedPtrTableShared<T,A> >();
        m_data = table->m_data;
    }

    void appendRow()
    {
        gTableRow *prow = new gTableRow();
        m_data.append(prow);
    }
    void append(T *ref, gu32 index)
    {
        gTableRow *prow = m_data.value(index);

        if(prow)
        {
            prow->append(ref);
        }
    }
    void setValue(T *ref, gu32 wx, gu32 wy, bool freeold)
    {
        gTableRow *prow = m_data.value(wx);
        if(prow)
        {
            prow->setValue(ref,wy,freeold);
        }
    }
    T *value(gu32 wx, gu32 wy)
    {
        gTableRow *prow = m_data.value(wx);
        if(prow)
        {
            return prow->value(wy);
        }
        return 0;
    }
    const T *value(gu32 wx, gu32 wy) const
    {
        gTableRow *prow = m_data.value(wx);
        if(prow)
        {
            return prow->value(wy);
        }
        return 0;
    }
    void removeRow(gu32 wx)
    {
        m_data.remove(wx);
    }
    void remove(gu32 wx, gu32 wy)
    {
        gTableRow *prow = m_data.value(wx);
        if(prow)
        {
            prow->remove(wy);
        }
    }
    void remove(T *ref, gu32 wx)
    {
        gTableRow *prow = m_data.value(wx);
        if(prow)
        {
            prow->remove(ref);
        }
    }
    void fastRemove(gu32 wx, gu32 wy)
    {
        gTableRow *prow = m_data.value(wx);
        if(prow)
        {
            prow->fastRemove(wy);
        }
    }
    void fastRemove(T *ref, gu32 wx)
    {
        gTableRow *prow = m_data.value(wx);
        if(prow)
        {
            prow->fastRemove(ref);
        }
    }
    bool contains(T *ref, gu32 wx, gu32 *indexout) const
    {
        gTableRow *prow = m_data.value(wx);
        if(prow)
        {
            return prow->contains(ref,indexout);
        }
        return false;
    }
    bool contains(const T &ref, gu32 wx, gu32 *indexout)
    {
        gTableRow *prow = m_data.value(wx);
        if(prow)
        {
            return prow->contains(ref,indexout);
        }
        return false;
    }
    gu32 rows() const
    {
        return m_data.size();
    }
    gu32 columns(gu32 wx) const
    {
        const gTableRow *prow = m_data.value(wx);
        if(prow)
        {
            return prow->size();
        }
        return 0;
    }
    void setUsedRows(gu32 val)
    {
        m_data.setUsed(val);
    }
    void setUsedColumns(gu32 val, gu32 wx)
    {
        gTableRow *prow = m_data.value(wx);
        if(prow)
        {
            return prow->setUsed(val);
        }

    }
    template <class SF>
    void sort(gu32 wx)
    {
        gTableRow *prow = m_data.value(wx);
        if(prow)
        {
            return prow->sort<SF>();
        }
    }


protected:
    gTableData m_data;
};
}
#endif // GALIGNEDPTRTABLESHARED_H
