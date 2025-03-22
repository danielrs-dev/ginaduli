#ifndef GPTRPAIR_H
#define GPTRPAIR_H
#include "gcommon.h"

namespace gcf
{
template <class A, class B>
class gPtrPair
{
public:
    gPtrPair():
        m_pairA(0),
        m_pairB(0)
    {

    }
    gPtrPair(const gPtrPair<A,B> &other):
        m_pairA(other.m_pairA),
        m_pairB(other.m_pairB)
    {

    }
    gPtrPair(A *p1, B *p2):
        m_pairA(p1),
        m_pairB(p2)
    {

    }
    ~gPtrPair()
    {

    }
    gPtrPair<A,B> &operator = (const gPtrPair<A,B> &other)
    {
        m_pairA = other.m_pairA;
        m_pairB = other.m_pairB;
        return *this;
    }

    void setPair(A *p1, B *p2)
    {
        m_pairA = p1;
        m_pairB = p2;
    }

    void setPairA(A *p1)
    {
        m_pairA = p1;
    }

    void setPairB(B *p2)
    {
        m_pairB = p2;
    }

    A *pairA()
    {
        return m_pairA;
    }
    const A *pairA() const
    {
        return m_pairA;
    }
    B *pairB()
    {
        return m_pairB;
    }
    const B *pairB() const
    {
        return m_pairB;
    }
    void remove()
    {
        delete m_pairA;
        delete m_pairB;
    }

protected:
    A *m_pairA;
    B *m_pairB;
};
}
#endif // GPTRPAIR_H
