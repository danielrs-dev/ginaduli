#include "gpatselmachinesand.h"

using namespace gcf;

gPatselMachineSand::gPatselMachineSand():
    m_solvertype(0)
{
    m_sweepline.alloc(GPATSEL_SWEEP_SIZE);
    m_sweepline.setUsed(GPATSEL_SWEEP_SIZE);
}
gPatselMachineSand::~gPatselMachineSand()
{

}
void gPatselMachineSand::setLineEquation(const gVector2f &start,
                                        const gVector2f &end)
{
    gVector2f vec = end - start;
    gf32 mag = vec.magnitude();
    gf32 a = gMath::absValue(vec.x());
    gf32 b = gMath::absValue(vec.y());
    gf32 ncos = a / mag;
    gf32 nsin = b / mag;

    setSweep(GPATEL_LSWP_COS,ncos);
    setSweep(GPATEL_LSWP_SIN,nsin);
    m_solvertype = GPATEL_LINE_EQ;

}
void gPatselMachineSand::setParaboleEquation(const gVector2f &start,
                                            const gVector2f &end,
                                            gf32 height,
                                            gf32 vangel)
{
//y = sqrt((1-(x-h)2/a2)*b2) + k
    gf32 sqa;
    gf32 sqb;
    gVector2f vertex = end - start;

    vertex = vertex * 0.5f;
    vertex += start;
    sqa = start.distance(end) * 0.5f;
    sqb = height * 0.5f;

    sqa = sqa * sqa;
    sqb = sqb * sqb;

    setSweep(GPATEL_PSWP_A, sqa);
    setSweep(GPATEL_PSWP_B, sqb);
    setSweep(GPATEL_PSWP_H, vertex.x());
    setSweep(GPATEL_PSWP_K, vertex.y());
    setSweep(GPATEL_PSWP_VANGEL, vangel);
    m_solvertype = GPATEL_PARABOLE_EQ;
}

void gPatselMachineSand::setCircleEquation(const gVector2f &start, const gVector2f &end)
{
    gf32 radius;
    gVector2f center = end - start;
    center = center * 0.5f;
    center += start;
    radius = start.distance(end) * 0.5f;

    radius = radius * radius;
    //circle res = sqrt(r^2 - (x-a)^2) + b
    setSweep(GPATEL_CSWP_CENTERX, center.x());
    setSweep(GPATEL_CSWP_CENTERY, center.y());
    setSweep(GPATEL_CSWP_RADIUS, radius);
    m_solvertype = GPATEL_CIRCLE_EQ;
}
void gPatselMachineSand::setQuadraticEquation(gf32 mayer)
{
    setSweep(GPATEL_QSWP_MAYER,mayer);
    m_solvertype = GPATEL_QUADRATIC_EQ;
}

void gPatselMachineSand::setSweep(gu32 index, gf32 value)
{
    m_sweepline.setValue(value,index);
}
gf32 gPatselMachineSand::sweep(gu32 index) const
{
    return m_sweepline.value(index);
}

gVector2f gPatselMachineSand::solveLine(const gVector2f &pos, const gVector2f &inc)
{
    gf32 ncos = sweep(GPATEL_LSWP_COS);
    gf32 nsin = sweep(GPATEL_LSWP_SIN);
    gf32 rx,ry;

    rx = pos.x() + (inc.x() * ncos);
    ry = pos.y() + (inc.y() * nsin);
    return gVector2f(rx,ry);
}
gVector2f gPatselMachineSand::solveParabole(const gVector2f &pos,
                                           const gVector2f &inc)
{
    gf32 sqa = sweep(GPATEL_PSWP_A);
    gf32 sqb = sweep(GPATEL_PSWP_B);
    gf32 h = sweep(GPATEL_PSWP_H);
    gf32 k = sweep(GPATEL_PSWP_K);
    gf32 v = sweep(GPATEL_PSWP_VANGEL);
    gf32 ry,rx;
    gf32 factxh, factrem;
    gf32 fact;

    //y = sqrt((1-(x-h)2/a2)*b2) + k

    rx = pos.x() + inc.x();
    factxh = rx - h;
    factxh = factxh * factxh;
    factrem = factxh / sqa;
    factrem = 1 - factrem;
    fact = factrem * sqb;
    ry = (v * gMath::fastSquareRoot(fact)) + k;

    return gVector2f(rx,ry);
}

gVector2f gPatselMachineSand::solveCircle(const gVector2f &pos,
                                         const gVector2f &inc)
{
    //circle res = sqrt(r^2 - (x-a)^2) + b
    gf32 radius = sweep(GPATEL_CSWP_RADIUS);
    gf32 a = sweep(GPATEL_CSWP_CENTERX);
    gf32 b = sweep(GPATEL_CSWP_CENTERY);
    gf32 rx,ry;
    gf32 factxa;
    gf32 fact;

    rx = pos.x() + inc.x();
    factxa = rx - a;
    factxa = factxa * factxa;
    fact = radius - factxa;
    ry = gMath::fastSquareRoot(fact) + b;
    return gVector2f(rx,ry);


}
gVector2f gPatselMachineSand::solveQuadratic(const gVector2f &pos,
                                            const gVector2f &inc)
{
    gf32 rx = pos.x() + inc.x();
    gf32 ry;
    gf32 mayer = sweep(GPATEL_QSWP_MAYER);
    gf32 fact;

    fact = rx * rx;
    ry = mayer * fact;

    return gVector2f(rx,ry);
}
gs32 gPatselMachineSand::solverType() const
{
    return m_solvertype;
}
