#ifndef GRECT_H
#define GRECT_H
#include "gcommon.h"
#include "gmath/gmath.h"
namespace gcf
{
template <class V>
class gRect
{
public:
    gRect():
        m_top(0),
        m_bottom(0),
        m_left(0),
        m_right(0)
    {

    }
    gRect(const gRect<V> &o):
        m_top(o.m_top),
        m_bottom(o.m_bottom),
        m_left(o.m_left),
        m_right(o.m_right)
    {

    }
    gRect(const V &ntop, const V &nbottom, const V &nleft,const V &nright):
        m_top(ntop),
        m_bottom(nbottom),
        m_left(nleft),
        m_right(nright)
    {

    }
    gRect<V> &operator = (const gRect<V> &o)
    {
        m_top = o.m_top;
        m_bottom = o.m_bottom;
        m_left = o.m_left;
        m_right = o.m_right;
        return *this;
    }
    void setValues(const V &ntop, const V &nbottom, const V &nleft,const V &nright)
    {
        m_top = ntop;
        m_bottom = nbottom;
        m_left = nleft;
        m_right = nright;
    }
    void setTop(const V &ntop)
    {
        m_top = ntop;
    }
    void setBottom(const V &nbottom)
    {
        m_bottom = nbottom;
    }
    void setLeft(const V &nleft)
    {
        m_left = nleft;
    }
    void setRight(const V &nright)
    {
        m_right = nright;
    }
    V &top()
    {
        return m_top;
    }
    const V &top() const
    {
        return m_top;
    }
    V &bottom()
    {
        return m_bottom;
    }
    const V &bottom() const
    {
        return m_bottom;
    }
    V &left()
    {
        return m_left;
    }
    const V &left() const
    {
        return m_left;
    }
    V &right()
    {
        return m_right;
    }
    const V &right() const
    {
        return m_right;
    }
    V radius() const
    {
        V result = 0;
        V offy = m_bottom - m_top;
        V offx = m_right - m_left;
        V offr = (offx * offx + offy * offy);

        result = gMath::fastSquareRoot(offr) * 0.5f;
        return result;
    }
protected:
    V m_top;
    V m_bottom;
    V m_left;
    V m_right;
};
typedef gRect<gf32> gRectf;
typedef gRect<gs32> gRecti;
}
#endif // GRECT_H
