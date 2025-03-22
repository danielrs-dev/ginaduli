#ifndef GMATH_H
#define GMATH_H
/**************************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File: gmath.h
        Description: Implementation of gMath class and functions.
***************************************************************************/

#include <cstdlib>
#include <cmath>
#include <ctime>
#include <base/gcommon.h>
#ifdef __SSE__
#include <emmintrin.h>
#endif


#ifndef G_PI
/// Defines the standard PI value
#define G_PI 3.14159265359
#endif
#ifndef G_DRCONST
#define G_DRCONST 0.01745329251994329576923690768489
#endif
#ifndef  G_RDCONST
#define G_RDCONST 57.295779513082320876798154814105
#endif
namespace gcf
{
/*! \brief The gMath class holds a set static math functions.
 */
struct gMath
{
    /*! \brief Gets the sine value give a scalar value.
        \param value: Value in radians.
        \return Sine value.
     */
    inline static gScalar sine(gScalar value)
    {
        return gScalar(sin(value));
    }
    /*! \brief Gets the cosine value give a scalar value.
        \param value: Value in radians.
        \return Cosine value.
     */
    inline static gScalar cosine(gScalar value)
    {
        return gScalar(cos(value));
    }
    /*! \brief Gets the tangent value give a scalar value.
        \param value: Value in radians.
        \return Tangent value.
     */
    inline static gScalar tangent(gScalar value)
    {
        return gScalar(tan(value));
    }
    /*! \brief Gets the arc tangent value give a scalar value.
        \param value: Value in radians.
        \return Arc tangent value.
     */
    inline static gScalar atangent(gScalar value)
    {
        return gScalar(atan(value));
    }
    /*! \brief Gets the arc tangent value given two coordinates.
        \param x: x value in radians.
        \param y: y value in radians.
        \return Arc tangent value.
     */
    inline static gScalar atangent2(gScalar x, gScalar y)
    {
        return gScalar(atan2(x,y));
    }
    /*! \brief Gets the arc sine value give a scalar value.
        \param value: Value in radians.
        \return Arc sine value.
     */
    inline static gScalar asine(gScalar value)
    {
        return gScalar(asin(value));
    }
    inline static gScalar acosine(gScalar value)
    {
        return gScalar(acos(value));
    }

    /*! \brief Gets the square root value give a scalar value.
        \param value: Value.
        \return Square root value.
     */
    inline static gScalar squareRoot(gScalar value)
    {
        if(value < 0)
        {
            return 0;
        }
#ifdef __SSE__
        double _res[2];
        __m128d val = _mm_set1_pd(value);
        __m128d res = _mm_sqrt_sd(0,val);
        _mm_store_sd(_res,res);
        return _res[0];
#else
        return sqrt(value);
#endif
    }
    /*! \brief Gets the reciprocal square root value give a scalar value.
        \param value: Value.
        \return Reciprocal square root value.
     */
    inline static gScalar reciprocalSquareRoot(gScalar value)
    {
        gScalar val = squareRoot(value);
#ifdef __SSE__
        gf32 ret[4];
        __m128 res;

        res = _mm_set1_ps(val);
        res = _mm_rcp_ss(res);
        _mm_storeu_ps(ret,res);
        return (gScalar)ret[0];

#else
        return (gScalar)1.0f / val;
#endif
    }
    /*! \brief Gets the square root value give a scalar value. Using the
               magic number method.
               This is a fast version.
        \param value: Value.
        \return Square root value.
     */
    inline static gScalar fastSquareRoot(gScalar value)
    {
        const gf32 half = value * 0.5f;
        if(value < 0)
        {
            return 0;
        }
        union
        {
            gs32 i;
            gf32 f;
        } u;
        u.f = value;
        u.i = 0x5f3759df - (u.i >> 1);
        return (value *  u.f)  * (1.5f - half * u.f * u.f);
    }
    /*! \brief Gets the reciprocal square root value give a scalar value. Using the
               magic number method.
               This is a fast version.
        \param value: Value.
        \return Square root value.
     */
    inline static gf32 fastReciprocalSquareRoot32(gScalar value)
    {
        const gf32 half = value * 0.5f;
        union
        {
            gs32 i;
            gf32 f;
        } u;
        u.f = value;
        u.i = 0x5f3759df - (u.i >> 1);
        return (u.f)  * (1.5f - half * u.f * u.f);
    }
    /*! \brief Gets the Absolute value give a scalar value.
        \param value: Value.
        \return Absolute value.
     */
    inline static gScalar absValue(gScalar value)
    {
        return value < 0 ? -value : value;
    }
    /*! \brief Clamps a value and return it given a scalar value.
        \param value: Value.
        \param low: Low threshold.
        \param high: High threshold.
        \return Clamped value.
     */
    template <typename T>
    inline static const T clamp(const T &value, const T &low, const  T &high)
    {
        return GDMIN(GDMAX(value,low),high);
    }
    /*! \brief Initializes the random seed generator to generate random numbers.
        \param seed: Base seed value.
     */
    inline static void randomSeed(gs32 seed = 0)
    {
        if(seed)
        {
            srand(seed);
        }
        else
        {
            srand(time(0));
        }
    }
    /*! \brief Gets a random integer given a minimum and a maximum.
        \param min: Minimal random value.
        \param max: Maximum randome value.
        \return Random value.
    */
    inline static gs32 randomInteger(gs32 min,gs32 max)
    {
        gs32 val = rand();
        GDRAND_RANGE(val,min,max,RAND_MAX);
        return val;
    }
    /*! \brief Gets a random float value given a minimum and a maximum.
        \param min: Minimal random value.
        \param max: Maximum randome value.
        \return Random value.
    */
    inline static gScalar randomFloat(gScalar min,gScalar max)
    {
        gs32 val= rand();
        gScalar tmin;
        //Normalize values
        tmin = min / max;
        //transform values to integer to work with rand
        gs32 maxVal = RAND_MAX;
        gs32 minVal = (gs32)(RAND_MAX * tmin);
        GDRAND_RANGE(val,minVal,maxVal,RAND_MAX);

        gScalar ret = gScalar(gScalar(val) / gScalar(RAND_MAX)) * max;

        return ret;
    }
    inline static gScalar randomSign()
    {
        gScalar rsign = (gScalar)randomInteger(0,5);
        return (rsign < 5) ? -1 : 1;
    }
    inline static gScalar sign(gScalar val)
    {
        return (val < 0) ? -1: 1;
    }

    /*! \brief Gets the linear interpolation of two values given a factor.
        \param v1: Value 1.
        \param v2: Value 2:
        \param fact: Factor value.
        \return Interpolated value.
    */
    inline static gScalar lerp(const gScalar v1,const gScalar v2, const gScalar fact)
    {
        return ((1 - fact) * v1) + (fact * v2);
    }
    /*! \brief Transforms a binary value to its polar version.
        \param value: Value to transform.
        \return Polar value.
    */
    inline static gScalar bin2polar(gScalar value)
    {
        return (2.0f * value) - 1.0f;
    }
    /*! \brief Transforms a polar value to its binary version.
        \param value: Value to transform.
        \return Binary value.
    */
    inline static gScalar polar2bin(gScalar value)
    {
        //polar = 2v -1
        //v = (polar + 1) / 2
        return (value + 1.0f) * 0.5f;
    }
    /*! \brief Gets the reciprocal number of a value.
        \param value: Value to get reciprocal.
        \return Reciprocal value.
    */
    inline static gScalar reciprocal(gScalar value)
    {
        //this might be ending the same with sse funcs or not
        // the compiler may optimize it for it anyway
#ifdef __SSE__
        float result[4];
        __m128 val = _mm_set1_ps(value);
        __m128 ret = _mm_rcp_ss(val);
        _mm_store_ss(result,ret);
        return result[0];
#else
        return 1.0f / value;
#endif
    }
    /*! \brief Normalizes a numeric value given a maximum.
        \param value: Numeric value to normalize.
        \param max: Maximum value.
        \return Normalized value.
    */
    inline static gScalar normalize(gScalar value, gScalar max)
    {
        return reciprocal(max) * value;
    }
    inline static gScalar power(gScalar value, gu32 npow)
    {
        gu32 i;
        gScalar res = 1;
        for(i = 0; i < npow; i++)
        {
            res *=value;
        }
        return res;
    }
    inline static gScalar degtorad(gScalar deg)
    {
        return deg * G_DRCONST;
    }
    inline static gScalar radtodeg(gScalar rad)
    {
        return rad * G_RDCONST;
    }
    inline static gScalar round(gScalar val)
    {
        return floor(val);
    }
};

}

#endif // GMATH_H
