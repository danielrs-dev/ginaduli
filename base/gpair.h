#ifndef GPAIR_H
#define GPAIR_H
#include "gcommon.h"

namespace gcf
{
template <class A, class B>
class gPair
{
public:
    gPair()
    {

    }
    gPair(const gPair<A,B> &p):
        m_pairA(p.m_pairA),
        m_pairB(p.m_pairB)
    {

    }
    gPair(const A &p1, const B &p2):
        m_pairA(p1),
        m_pairB(p2)
    {

    }
    ~gPair()
    {

    }
    gPair<A,B> &operator = (const gPair<A,B> &p)
    {
        m_pairA = p.m_pairA;
        m_pairB = p.m_pairB;
        return *this;
    }
    void setPairA(const A &pA)
    {
        m_pairA = pA;
    }
    void setPairB(const B &pB)
    {
        m_pairB = pB;
    }
    void setPair(const A &p1, const B &p2)
    {
        m_pairA = p1;
        m_pairB = p2;
    }

    A &pairA()
    {
        return m_pairA;
    }
    const A &pairA() const
    {
        return m_pairA;
    }

    B &pairB()
    {
        return m_pairB;
    }
    const B &pairB() const
    {
        return m_pairB;
    }
protected:
    A m_pairA;
    B m_pairB;
};
}
#endif // GPAIR_H
