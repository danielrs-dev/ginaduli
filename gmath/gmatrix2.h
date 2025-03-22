#ifndef GMATRIX2_H
#define GMATRIX2_H
#include "base/gcommon.h"
#include "gvector2.h"
namespace gcf
{
template <class V>
class gMatrix2
{
public:
    gMatrix2()
    {
        m_data[0][0] = 0;
        m_data[0][1] = 0;
        m_data[1][0] = 0;
        m_data[1][1] = 0;
    }
    gMatrix2(const gMatrix2<V> &other)
    {
        copy(other);
    }

    ~gMatrix2()
    {

    }
    gMatrix2<V> &operator = (const gMatrix2<V> &other)
    {
        copy(other);
        return *this;
    }
    void copy(const gMatrix2<V> &other)
    {
        m_data[0][0] = other.m_data[0][0];
        m_data[0][1] = other.m_data[0][1];
        m_data[1][0] = other.m_data[1][0];
        m_data[1][1] = other.m_data[1][1];
    }
    void setValue(const V &val, gu32 row, gu32 col)
    {
        m_data[row][col] = val;
    }
    void setValue(const V &a, const V &b, const V &c, const V &d)
    {
        m_data[0][0] = a;
        m_data[0][1] = b;
        m_data[1][0] = c;
        m_data[1][1] = d;
    }

    V &value(gu32 row, gu32 col)
    {
        return m_data[row][col];
    }
    const V &value(gu32 row,gu32 col) const
    {
        return m_data[row][col];
    }
    V *operator [] (gu32 row)
    {
        return m_data[row];
    }
    const V *operator [] (gu32 row) const
    {
        return m_data[row];
    }
    void setIdentity()
    {
        m_data[0][0] = 1;
        m_data[0][1] = 0;
        m_data[1][0] = 0;
        m_data[1][1] = 1;
    }
    void setTranspose()
    {
        /* a b  =  a c
           c d     b d
        */

        m_data[0][1] = m_data[1][0];
        m_data[1][0] = m_data[0][1];

    }

    void multiply(const gMatrix2<V> &other)
    {
        V a,b,c,d;
        V w,x,y,z;
        V f,g,h,i;

        a = m_data[0][0];
        b = m_data[0][1];
        c = m_data[1][0];
        d = m_data[1][1];

        w = other.m_data[0][0];
        x = other.m_data[0][1];
        y = other.m_data[1][0];
        z = other.m_data[1][1];
        f = a * w + b * y;
        g = a * x + b * z;
        h = c * w + d * y;
        i = c * x + d * z;

        setValue(f,g,h,i);

    }
    void sum(const gMatrix2<V> &other)
    {
        V a,b,c,d;
        V w,x,y,z;
        V f,g,h,i;

        a = m_data[0][0];
        b = m_data[0][1];
        c = m_data[1][0];
        d = m_data[1][1];

        w = other.m_data[0][0];
        x = other.m_data[0][1];
        y = other.m_data[1][0];
        z = other.m_data[1][1];
        f = a + w;
        g = b + x;
        h = c + y;
        i = d + z;
        setValue(f,g,h,i);
    }
    void multiply(const V &sc)
    {
        m_data[0][0] *= sc;
        m_data[0][1] *= sc;
        m_data[1][0] *= sc;
        m_data[1][1] *= sc;
    }
    gVector2<V> vmultiply(const gVector2<V> &vec)
    {
        V x,nx;
        V y,ny;
        V a = m_data[0][0];
        V b = m_data[0][1];
        V c = m_data[1][0];
        V d = m_data[1][1];
        nx = vec.x();
        ny = vec.y();
        x = a * nx + b * ny;
        y = c * ny + d * ny;
        return gVector2<V>(x,y);
    }

    gMatrix2<V> &operator += (const gMatrix2<V> &ot)
    {
        sum(ot);
        return *this;
    }
    gMatrix2<V> operator * (const gMatrix2<V> &ot) const
    {
        gMatrix2<V> ret(*this);
        ret.multiply(ot);
        return ret;
    }

protected:
    V m_data[2][2];
};

typedef gMatrix2<gf32> gMatrix2f;
}
#endif // GMATRIX2_H
