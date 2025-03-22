#include "gpatselmachine.h"
#include "gpatselmachinesand.h"

using namespace gcf;

gPatselMachine::gPatselMachine():
    d(new gPatselMachineSand())
{

}
gPatselMachine::~gPatselMachine()
{
    delete d;
}

void gPatselMachine::setLineEquation(const gVector2f &start,
                                    const gVector2f &end)
{
    d->setLineEquation(start,end);
}
void gPatselMachine::setParaboleEquation(const gVector2f &start,
                                        const gVector2f &end,
                                        gf32 height,
                                        gf32 vangel)
{
    d->setParaboleEquation(start,end,height,vangel);
}
void gPatselMachine::setCircleEquation(const gVector2f &start,
                                      const gVector2f &end)
{
    d->setCircleEquation(start,end);
}
void gPatselMachine::setQuadraticEquation(gf32 mayer)
{
    d->setQuadraticEquation(mayer);
}
gVector2f gPatselMachine::solve(const gVector2f &position,
                               const gVector2f &increment)
{
    switch(d->solverType())
    {
    case GPATEL_LINE_EQ:
        return d->solveLine(position,increment);
        break;
    case GPATEL_PARABOLE_EQ:
        return d->solveParabole(position,increment);
        break;
    case GPATEL_CIRCLE_EQ:
        return d->solveCircle(position,increment);
        break;
    case GPATEL_QUADRATIC_EQ:
        return d->solveQuadratic(position,increment);
        break;
    default:
        return gVector2f();
    }
}
