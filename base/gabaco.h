#ifndef GABACO_H
#define GABACO_H
#include "gcommon.h"

namespace gcf
{
template <class V>
class gAbaco
{
public:
    gAbaco():
        m_min(V()),
        m_max(V())
    {

    }

    gAbaco(const gAbaco<V> &aba):
        m_min(aba.m_min),
        m_max(aba.m_max)
    {

    }
    gAbaco(const V &nmin, const V &nmax):
        m_min(nmin),
        m_max(nmax)
    {

    }
    ~gAbaco()
    {

    }
    void setValues(const V &nmin, const V &nmax)
    {
        m_min = nmin;
        m_max = nmax;
    }
    void setMin(const V &nmin)
    {
        m_min = nmin;
    }
    void setMax(const V &nmax)
    {
        m_max = nmax;
    }
    V &min()
    {
        return m_min;
    }
    const V &min() const
    {
        return m_min;
    }
    V &max()
    {
        return m_max;
    }
    const V &max() const
    {
        return m_max;
    }
protected:
    V m_min;
    V m_max;
};
typedef gAbaco<gf32> gAbacof;
}
#endif // GABACO_H
