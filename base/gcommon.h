#ifndef COMMON_H
#define COMMON_H
/**************************************************************/
/*          GINA Duli C++ Framework
 *
 *          Author: Daniel Rios
 *          File: gcommon.h
 *          Description: Common types and routines.
 **************************************************************/
//Header libs
#include <stdint.h>
#include <assert.h>
//Macros and definitions

#ifdef WIN32
#ifdef SHARED_LIBRARY

#ifdef SHARED_EXPORT
#define SHARED_GCF __declspec(dllexport)
#else
#define SHARED_GCF __declspec(dllimport)
#endif

#else
#define SHARED_GCF
#endif

#else
#define SHARED_GCF
#endif

#ifndef GDMAX
/*! \brief Compares to numerical values to find the maximum
           beetween both
*/
#define GDMAX(a,b) a > b  ? a : b
#endif

#ifndef GDMIN
/*! \brief Compares two numerical values for finding the minimal */
#define GDMIN(a,b) a < b ? a : b
#endif

#ifndef GDRAND_RANGE
/*! \brief Gets the random value between two given values
    \param _n Return value
    \param __min Minimal value from range
    \param __max Maximum value from range
    \param __tmax Floor max value
 */
#define GDRAND_RANGE(__n, __min, __max, __tmax) \
    (__n) = (__min) + (long) ((double) ( (double) (__max) - (__min) + 1.0) * ((__n) / ((__tmax) + 1.0)))
#endif
#ifndef GDRAND_RANGEF
/*! \brief Gets the random value between two given float values
    \param _n Return value
    \param __min Minimal value from range
    \param __max Maximum value from range
    \param __tmax Floor max value
 */
#define GDRAND_RANGEF(__n, __min, __max, __tmax) \
    (__n) = (__min) + ((double) ( (double) (__max) - (__min) + 1.0) * ((__n) / ((__tmax) + 1.0)))
#endif

#ifndef GDUNUSED
/*! \brief Avoids warnings and errors for unused parameters or variables*/
#define GDUNUSED(param) (void)param
#endif

#ifndef GASSERT
/*! \brief Assertion routing
 *  \param cond Conditional to test
 *  \param msg Message to send
 */
#define GASSERT(cond,msg) assert(cond && msg)
#endif
//Defines namespace
namespace gcf
{
   /// Type definition of a signed 8 bit integer
   typedef int8_t gs8;
   /// Type definition of a unsigned 8 bit integer
   typedef uint8_t gu8;
   /// Type definition of a signed 16 bit integer
   typedef int16_t gs16;
   /// Type definition of an unsigned 16 bit integer
   typedef uint16_t gu16;
   /// Type definition of a signed 32 bit integer
   typedef int32_t gs32;
   /// Type definition of an unsigned 32 bit integer
   typedef uint32_t gu32;
   /// Type definition of a signed 64 bit integer
   typedef int64_t gs64;
   /// Type definition of an unsigned 64 bit integer
   typedef uint64_t gu64;
   /// Type definition of a 32 bit floating point numeric value
   typedef float gf32;
   /// Type definition of a 64 bit floating point numeric value
   typedef double gf64;
   /// Type definition of a generic pointer
   typedef void *gpointer;
   /// Type definition of an integer capable to store a memory location
   typedef uintptr_t guptr;
   typedef gf64 gScalar;

    enum GSTRING_FORMAT
    {
        GSF_ASCII,
        GSF_UNICODE
    };

}


#endif // COMMON_H
