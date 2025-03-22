#ifndef GPATSELMACHINESAND_H
#define GPATSELMACHINESAND_H

#include <base/gcommon.h>
#include <containers/galignedlist.h>
#include "gvector2.h"
#include "qpatselsolvers.h"
#define GPATSEL_SWEEP_SIZE 22
namespace gcf
{
enum GPATEL_EQL_SWEEPS
{
    GPATEL_LSWP_SIN,
    GPATEL_LSWP_COS,
    GPATEL_LSWP_SIZE
};
enum GPATEL_EQP_SWEEPS
{
    GPATEL_PSWP_A,
    GPATEL_PSWP_B,
    GPATEL_PSWP_H,
    GPATEL_PSWP_K,
    GPATEL_PSWP_VANGEL,
    GPATEL_PSWP_SIZE
};
enum GPATEL_EQC_SWEEPS
{
    GPATEL_CSWP_RADIUS,
    GPATEL_CSWP_CENTERX,
    GPATEL_CSWP_CENTERY,
    GPATEL_CSWP_SIZE
};
enum GPATEL_EQQ_SWEEPS
{
    GPATEL_QSWP_MAYER,
    GPATEL_QSWP_SIZE
};

class gPatselMachineSand
{
public:
    gPatselMachineSand();
    ~gPatselMachineSand();
    void setLineEquation(const gVector2f &start,
                         const gVector2f &end);
    void setParaboleEquation(const gVector2f &start,
                             const gVector2f &end,
                             gf32 height,
                             gf32 vangel);
    void setCircleEquation(const gVector2f &start,
                           const gVector2f &end);
    void setQuadraticEquation(gf32 mayer);
    void setSweep(gu32 index, gf32 value);
    gf32 sweep(gu32 index) const;
    gVector2f solveLine(const gVector2f &pos,
                        const gVector2f &inc); // y = mx + b
    gVector2f solveParabole(const gVector2f &pos,
                            const gVector2f &inc);
    gVector2f solveCircle(const gVector2f &pos,
                          const gVector2f &inc);
    gVector2f solveQuadratic(const gVector2f &pos,
                             const gVector2f &inc);

    gs32 solverType() const;
protected:
    gAlignedList<gf32> m_sweepline;
    gs32 m_solvertype;
};
}
#endif // GPATSELMACHINESAND_H
