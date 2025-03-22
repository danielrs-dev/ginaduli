#ifndef GVECTOR2_H
#define GVECTOR2_H
#include <base/gcommon.h>
#include <gmath/gmath.h>
namespace gcf
{
template <class V>
class gVector2
{
public:
    gVector2():
        m_x(0),
        m_y(0)
    {

    }

    gVector2(const gVector2<V> &other):
        m_x(other.m_x),
        m_y(other.m_y)
    {

    }
    gVector2(const V &nx, const V &ny):
        m_x(nx),
        m_y(ny)
    {

    }
    gVector2<V> &operator = (const gVector2<V> &other)
    {
        m_x = other.m_x;
        m_y = other.m_y;
        return *this;
    }
    gVector2<V> &operator += (const gVector2<V> &other)
    {
        m_x += other.m_x;
        m_y += other.m_y;
        return *this;
    }
    gVector2<V> &operator -= (const gVector2<V> &other)
    {
        m_x -= other.m_x;
        m_y -= other.m_y;
        return *this;
    }
    gVector2<V> &operator *= (const gVector2<V> &other)
    {
        m_x *= other.m_x;
        m_y *= other.m_y;
        return *this;
    }
    gVector2<V> &operator /= (const gVector2<V> &other)
    {
        m_x /= other.m_x;
        m_y /= other.m_y;
        return *this;
    }
    gVector2<V> &operator += (const V &val)
    {
        m_x += val;
        m_y += val;
        return *this;
    }
    gVector2<V> &operator -= (const V &val)
    {
        m_x -= val;
        m_y -= val;
        return *this;
    }
    gVector2<V> &operator *= (const V &val)
    {
        m_x *= val;
        m_y *= val;
        return *this;
    }
    gVector2<V> &operator /= (const V &val)
    {
        m_x /= val;
        m_y /= val;
        return *this;
    }
    gVector2<V> operator + (const gVector2<V> &other) const
    {
        gVector2<V> res;
        res.m_x = m_x + other.m_x;
        res.m_y = m_y + other.m_y;
        return res;
    }
    gVector2<V> operator - (const gVector2<V> &other) const
    {
        gVector2<V> res;
        res.m_x = m_x - other.m_x;
        res.m_y = m_y - other.m_y;
        return res;
    }
    gVector2<V> operator * (const gVector2<V> &other) const
    {
        gVector2<V> res;
        res.m_x = m_x * other.m_x;
        res.m_y = m_y * other.m_y;
        return res;
    }
    gVector2<V> operator / (const gVector2<V> &other) const
    {
        gVector2<V> res;
        res.m_x = m_x / other.m_x;
        res.m_y = m_y / other.m_y;
        return res;
    }
    gVector2<V> operator + (const V &val) const
    {
        gVector2<V> res;
        res.m_x = m_x + val;
        res.m_y = m_y + val;
        return res;
    }
    gVector2<V> operator - (const V &val) const
    {
        gVector2<V> res;
        res.m_x = m_x - val;
        res.m_y = m_y - val;
        return res;
    }
    gVector2<V> operator * (const V &val) const
    {
        gVector2<V> res;
        res.m_x = m_x * val;
        res.m_y = m_y * val;
        return res;
    }
    gVector2<V> operator / (const V &val) const
    {
        gVector2<V> res;
        res.m_x = m_x / val;
        res.m_y = m_y / val;
        return res;
    }
    bool operator == (const gVector2<V> &other) const
    {
        bool eqx = (m_x == other.m_x);
        bool eqy = (m_y == other.m_y);
        return (eqx && eqy);
    }
    bool operator != (const gVector2<V> &other) const
    {
        bool eqx = (m_x != other.m_x);
        bool eqy = (m_y != other.m_y);
        return (eqx || eqy);
    }
    bool operator < (const gVector2<V> &other) const
    {
        bool eqx = (m_x < other.m_x);
        bool eqy = (m_y < other.m_y);
        return (eqx && eqy);
    }
    bool operator > (const gVector2<V> &other) const
    {
        bool eqx = (m_x > other.m_x);
        bool eqy = (m_y > other.m_y);
        return (eqx && eqy);
    }
    bool operator <= (const gVector2<V> &other) const
    {
        bool eqx = (m_x <= other.m_x);
        bool eqy = (m_y <= other.m_y);
        return (eqx && eqy);
    }
    bool operator >= (const gVector2<V> &other) const
    {
        bool eqx = (m_x >= other.m_x);
        bool eqy = (m_y >= other.m_y);
        return (eqx && eqy);
    }
    V magnitude() const
    {
        V fact = (m_x * m_x) + (m_y * m_y);
        return gMath::fastSquareRoot(gScalar(fact));
    }
    V distance(const gVector2<V> &other) const
    {
        V a = other.m_x - m_x;
        V b = other.m_y - m_y;
        V fact = (a * a) + (b * b);
        return gMath::fastSquareRoot(gScalar(fact));
    }
    V dot(const gVector2<V> &other) const
    {
        return m_x * other.m_x + m_y *other.m_y;
    }
    void normalize()
    {
        V mag = magnitude();
        m_x = m_x / mag;
        m_y = m_y / mag;
    }
    gVector2<V> normalized() const
    {
        gVector2<V> v(m_x,m_y);
        v.normalize();
        return v;
    }
    void setX(const V &nx)
    {
        m_x = nx;
    }
    void setY(const V &ny)
    {
        m_y = ny;
    }
    void setValues(const V &nx, const V &ny)
    {
        m_x = nx;
        m_y = ny;
    }
    V angle() const
    {
        V ang;
        if(m_x == 0)
        {
            return V(90);
        }
        if(m_y == 0)
        {
            return V(0);
        }
        ang = m_y / m_x;
        ang = (V)gMath::atangent(ang);
        return (V)gMath::radtodeg(ang);
    }
    V angle(const gVector2<V> &ov) const
    {
        gVector2<V> r  = (*this) - ov;
        return r.angle();
    }

    inline V &x()
    {
        return m_x;
    }

    inline const V &x() const
    {
        return m_x;
    }
    inline V &y()
    {
        return m_y;
    }

    inline const V &y() const
    {
        return m_y;
    }
    static gVector2<V> absolute(const gVector2<V> &other)
    {
        V nx,ny;
        nx = (V)gMath::absValue(other.m_x);
        ny = (V)gMath::absValue(other.m_y);
        return gVector2<V>(nx,ny);
    }

protected:
    V m_x;
    V m_y;
};

typedef gVector2<gf32> gVector2f;
typedef gVector2<gs32> gVector2i;
}
#endif // GVECTOR2_H
