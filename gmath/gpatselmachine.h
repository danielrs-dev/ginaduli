#ifndef GPATSELMACHINE_H
#define GPATSELMACHINE_H
#include <base/gcommon.h>
#include "gvector2.h"
#include "qpatselsolvers.h"
namespace gcf
{


class gPatselMachineSand;
class SHARED_GCF gPatselMachine
{
public:
    gPatselMachine();
    virtual ~gPatselMachine();

    void setLineEquation(const gVector2f &start,
                         const gVector2f &end);
    void setParaboleEquation(const gVector2f &start,
                             const gVector2f &end,
                             gf32 height,
                             gf32 vangel);
    void setCircleEquation(const gVector2f &start,
                           const gVector2f &end);
    void setQuadraticEquation(gf32 mayer);
    gVector2f solve(const gVector2f &position,
                    const gVector2f &increment);
protected:
    gPatselMachineSand *d;
};
}
#endif // GPATSELMACHINE_H
