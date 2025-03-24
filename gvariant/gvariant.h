#ifndef GVARIANT_H
#define GVARIANT_H
/**************************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File: gvariant.h
        Description: Implementation of class gVariant
***************************************************************************/

#include <base/gcommon.h>
#include <gstring/gstring.h>
#include <gmath/gvector2.h>
#include <system/gdatetime.h>

namespace gcf
{
enum GVARIANT_TYPES
{
    GVARIANT_TYPE_CHAR,
    GVARIANT_TYPE_UCHAR,
    GVARIANT_TYPE_SHORT,
    GVARIANT_TYPE_USHORT,
    GVARIANT_TYPE_INT,
    GVARIANT_TYPE_UINT,
    GVARIANT_TYPE_INT64,
    GVARIANT_TYPE_UINT64,
    GVARIANT_TYPE_FLOAT,
    GVARIANT_TYPE_FLOAT64,
    GVARIANT_TYPE_STRING,
    GVARIANT_TYPE_VECTOR2F,
    GVARIANT_TYPE_DATETIME,
    GVARIANT_TYPE_POINTER,
    GVARIANT_TYPE_UNASSIGNED,
    //! Size of this enum
    GVARIANT_TYPE_SIZE
};
/*! \brief The class gVariant is a variable data type holder of many
           types of data.
           It can be initialized by any C++ built in data type and
           strings without the use of templates.
           This class handy to hold any data information that can be used
           as variable type.
*/
class SHARED_GCF gVariant
{
public:
    /// Standard constructor
    gVariant();
    /// Copy constructor
    gVariant(const gVariant &other);
    /// Constructor initializes a signed char value
    gVariant(gs8 cvalue);
    /// Constructor initializes a unsigned char value
    gVariant(gu8 cvalue);
    /// Constructor initializes a signed short value
    gVariant(gs16 cvalue);
    /// Constructor initializes a unsigned short value
    gVariant(gu16 cvalue);
    /// Constructor initializes a signed int value
    gVariant(gs32 cvalue);
    /// Constructor initializes a unsigned int value
    gVariant(gu32 cvalue);
    /// Constructor initializes a signed long long int value
    gVariant(gs64 cvalue);
    /// Constructor initializes a unsigne long long int value
    gVariant(gu64 cvalue);
    /// Constructor initializes a float value
    gVariant(gf32 cvalue);
    /// Constructor initializes a double value
    gVariant(gf64 cvalue);
    /// Constructor initializes a string
    gVariant(const gString &str);
    gVariant(const gVector2f &vec);
    gVariant(const gDateTime &dtime);
    gVariant(const char *str);
    gVariant(const wchar_t *str);
    /// Destructor
    virtual ~gVariant();
    /*! \brief Allocates memory for a specific type of data.
        \param mtype: Type of data to alloc. Could be any of the members
                      of enum GVARIANT_TYPES.
        \return true if success else false.
    */
    bool alloc(gs32 mtype);
    /// Deallocates and clears internal data
    void clear();
    /// Sets gVariant value from another gVariant object. Old data gets replaced.
    void setValue(const gVariant &other);
    /// Sets gVariant value as signed char or 8 bit integer. Old data gets replaced.
    void setValue(gs8 cvalue, bool setnew = false);
    /// Sets gVariant value as unsigned char or 8 bit unsigned integer. Old data gets replaced.
    void setValue(gu8 cvalue, bool setnew = false);
    /// Sets gVariant value as signed short or 16 bit integer. Old data gets replaced.
    void setValue(gs16 cvalue, bool setnew = false);
    /// Sets gVariant value as unsigned short or 16 bit unsigned integer. Old data gets replaced.
    void setValue(gu16 cvalue, bool setnew = false);
    /// Sets gVariant value as signed int or 32 bit integer. Old data gets replaced.
    void setValue(gs32 cvalue, bool setnew = false);
    /// Sets gVariant value as unsigned int or 32 bit unsigned integer. Old data gets replaced.
    void setValue(gu32 cvalue, bool setnew = false);
    /// Sets gVariant value as signed long long int or 64 bit integer. Old data gets replaced.
    void setValue(gs64 cvalue, bool setnew = false);
    /// Sets gVariant value as unsigned long long int or 64 bit unsigned integer. Old data gets replaced.
    void setValue(gu64 cvalue, bool setnew = false);
    /// Sets gVariant value as float or 32 bit floating point value. Old data gets replaced.
    void setValue(gf32 cvalue, bool setnew = false);
    /// Sets gVariant value as double or 64 bit floating point value. Old data gets replaced.
    void setValue(gf64 cvalue, bool setnew = false);
    /// Sets gVariant value as a string
    void setValue(const gString &str, bool setnew = false);
    void setValue(const gVector2f &vec, bool setnew = false);
    void setValue(const gDateTime &dtime, bool setnew = false);
    void setValue(const char *str, bool setnew = false);
    void setValue(const wchar_t *str, bool setnew = false);
    /*! \brief Sets the gVariant as a raw pointer of custom TYPE.
        \param ptr: Pointer
        \param mtype: Custom type.
    */
    void setRawPointer(void *ptr, gs32 mtype);
    /*! \brief Gets the type of data held by the object.
        \return Type of data.
    */
    gs32 type() const;
    /*! \brief Returns whether the object has not data or not.
        \return true if is empty else false.
    */
    bool isEmpty() const;
    bool isString() const;
    bool isNumeric() const;
    bool isSigned() const;
    bool isVector2f() const;
    bool isDateTime() const;
    gString asString() const;
    /// Gets the gVariant value as a 8 bit signed integer
    gs8 &toChar();
    /// Const version
    const gs8 &toChar() const;
    /// Gets the gVariant value as a 8 bit unsigned integer
    gu8 &toUChar();
    /// Const version
    const gu8 &toUChar() const;
    /// Gets the gVariant value as a 16 bit signed integer
    gs16 &toShort();
    /// Const version
    const gs16 &toShort() const;
    /// Gets the gVariant value as a 16 bit unsigned integer
    gu16 &toUShort();
    /// Const version
    const gu16 &toUShort() const;
    /// Gets the gVariant value as a 32 bit signed integer
    gs32 &toInt();
    /// Const version
    const gs32 &toInt() const;
    /// Gets the gVariant value as a 32 bit unsigned integer
    gu32 &toUInt();
    /// Const version
    const gu32 &toUInt() const;
    /// Gets the gVariant value as a 64 bit signed integer
    gs64 &toInt64();
    /// Const version
    const gs64 &toInt64() const;
    /// Gets the gVariant value as a 64 bit unsigned integer
    gu64 &toUInt64();
    /// Const version
    const gu64& toUInt64() const;
    /// Gets the gVariant value as a 32 bit floating point value.
    gf32 &toFloat();
    /// Const version
    const gf32 &toFloat() const;
    /// Gets the gVariant value as a 64 bit floating point value.
    gf64 &toFloat64();
    /// Const version
    const gf64 &toFloat64() const;
    /// Gets the gVariant value as a string
    gString &toString();
    /// Const version
    const gString &toString() const;
    gVector2f &toVector2f();
    const gVector2f &toVector2f() const;
    gDateTime &toDateTime();
    const gDateTime &toDateTime() const;
    /// Gets the internal pointer of the version
    void *toPointer();
    /// Const version
    const void *toPointer() const;
    /*! \brief Copies another variant object to this object.
        \param other: Variant object to copy data from.
    */
    void copy(const gVariant &other);
    /// Copies from data from another variant object. See gVariant::copy()
    gVariant &operator = (const gVariant &other);
    /// Performs the arithmetic operation obj = obj + avar with another gVariant.
    gVariant &operator += (const gVariant &other);
    /// Performs the arithmetic operation obj = obj - avar with another gVariant.
    gVariant &operator -= (const gVariant &other);
    /// Performs the arithmetic operation obj = obj * avar with another gVariant.
    gVariant &operator *= (const gVariant &other);
    /// Performs the arithmetic operation obj = obj / avar with another gVariant.
    gVariant &operator /= (const gVariant &other);
    /// Performs the arithmetic operation res = obj + avar
    /// with another variant object resulting a new one
    gVariant operator + (const gVariant &other) const;
    /// Performs the arithmetic operation res = obj - avar
    /// with another variant object resulting a new one
    gVariant operator - (const gVariant &other) const;
    /// Performs the arithmetic operation res = obj * avar
    /// with another variant object resulting a new one
    gVariant operator * (const gVariant &other) const;
    /// Performs the arithmetic operation res = obj / avar
    /// with another variant object resulting a new one
    gVariant operator / (const gVariant &other) const;
    /// Compares a variant with another returns true if equal.
    bool operator == (const gVariant &other) const;
    /// Compares a variant with another returns true if not equal.
    bool operator != (const gVariant &other) const;
    /// Compares a variant with another returns true if less than.
    bool operator < (const gVariant &other) const;
    /// Compares a variant with another returns true if greather than.
    bool operator > (const gVariant &other) const;
    /// Compares a variant with another returns true if equal or less than.
    bool operator <= (const gVariant &other) const;
    /// Compares a variant with another returns true if equal or greather than.
    bool operator >= (const gVariant &other) const;
    void squareRoot();
    void power(gu32 n);
    void sine();
    void cosine();
    void tangent();
    void asine();
    void acosine();
    void atangent();
    /*! \brief Performs an arithmetic operation of type
               this_obj = this_obj <operator> other_obj.
        \param obj: gVariant to perform operation with.
        \param op: Operator Identificator. This goes from 0 to 3.
                   Being 0 Sum, 1 Rest, 2 Mult, 3 Div.
    */
    void arithObject(const gVariant &obj, gs32 op);
    /*! \brief Performs a boolean comparison of this object with another
               this_obj <boolean operator> another_obj.
        \param obj: Object to perform comparison with.
        \param op: Boolean operator numeric id. From 0 to 5 where
                   0 is ==, 1 is !=, 2 is <,3 is >, 4 is <= and 5 is >=.
        \return true is matches operator or else false.
    */
    bool boolObject(const gVariant &obj, gs32 op) const;
    gu32 size() const;
    //Casts
    /// Template that casts the member m_data to any kind of type
    template <class V>
    V &cast()
    {
        return (*static_cast<V *>(m_data));
    }
    /// Const verson of gVariant::cast()
    template <class V>
    const V &cast() const
    {
        return (*static_cast<V *>(m_data));
    }
    template <class V>
    V *pcast()
    {
        return static_cast<V *>(m_data);
    }
    template <class V>
    const V *pcast() const
    {
        return static_cast<V *>(m_data);
    }

    /// Casts and delete the object held by this object.
    template<class V>
    void variantDelete()
    {
        delete static_cast<V *>(m_data);
    }
    /// Creates a object of type V using operator new
    template <class V>
    void *variantNew()
    {
        return new V();
    }
    /*! \brief Creates a object of type V using operator new.
        \param val: Object class V to copy data from.
    */
    template <class V>
    void *variantNew(const V &val)
    {
        return new V(val);
    }
    /*! \brief Template function that performs an arithmetic operation.
               with this object with another object of type V.
        \param val: Object or value to perform arithmetic operation with.
        \param op: Operator that performs operation. It can be:
                   0 to 3.
                   Where:
                   0 means sum
                   1 means rest
                   2 means multiplication
                   4 means division.
    */
    template <class V>
    void arithOp(const V &val, gs32 op)
    {
        V nval;
        if(m_data == 0)
        {
            setValue(val);
            return;
        }
        nval = deva<V>();
        switch(op)
        {
        case 0: nval += (val); break;
        case 1: nval -= (val); break;
        case 2: nval *= (val); break;
        case 3: nval /= (val); break;
        }
        diva<V>(nval);

    }
    template <class V>
    void arithOp(const gVector2<V> &vec, gs32 op)
    {
        switch(m_type)
        {
        case GVARIANT_TYPE_VECTOR2F:
            break;
        default:
            return;
        }

        gVector2<V> &lvec = cast<gVector2<V> >();
        switch(op)
        {
        case 0: lvec += vec; break;
        case 1: lvec -= vec; break;
        case 2: lvec *= vec; break;
        case 3: lvec /= vec; break;
        }
    }

    /*! \brief Performs a boolean comparison of this object with another
               this_obj <boolean operator> another_obj.
        \param obj: Object to perform comparison with.
        \param op: Boolean operator numeric id. From 0 to 5 where
                   0 is ==, 1 is !=, 2 is <,3 is >, 4 is <= and 5 is >=.
        \return true is matches operator or else false.
    */
    template <class V>
    bool opBool(const V &val, gs32 op) const
    {
        V cval = deva<V>();
        switch(op)
        {
        case 0: return cval == (val); break;
        case 1: return cval != (val); break;
        case 2: return cval < (val); break;
        case 3: return cval > (val); break;
        case 4: return cval <= (val); break;
        case 5: return cval >= (val); break;
        }
        return false;
    }
    template <class V>
    bool opBool(const gVector2<V> &vec, gs32 op) const
    {
        switch(m_type)
        {
        case GVARIANT_TYPE_VECTOR2F:
            break;
        default:
            return false;
        }

        const gVector2<V> &cvec = cast<gVector2<V> >();
        switch(op)
        {
        case 0: return cvec == (vec); break;
        case 1: return cvec != (vec); break;
        case 2: return cvec < (vec); break;
        case 3: return cvec > (vec); break;
        case 4: return cvec <= (vec); break;
        case 5: return cvec >= (vec); break;
        }
        return false;
    }
    bool opBool(const gDateTime &dt, gs32 op) const;


    template <class V>
    V deva() const
    {
        V val;
        switch(m_type)
        {
        case GVARIANT_TYPE_CHAR: val = (V)toChar(); break;
        case GVARIANT_TYPE_UCHAR: val = (V)toUChar(); break;
        case GVARIANT_TYPE_SHORT: val = (V)toShort(); break;
        case GVARIANT_TYPE_USHORT: val = (V)toUShort(); break;
        case GVARIANT_TYPE_INT: val = (V)toInt(); break;
        case GVARIANT_TYPE_UINT: val = (V)toUInt(); break;
        case GVARIANT_TYPE_INT64: val = (V)toInt64(); break;
        case GVARIANT_TYPE_UINT64: val = (V)toUInt64(); break;
        case GVARIANT_TYPE_FLOAT: val = (V)toFloat(); break;
        case GVARIANT_TYPE_FLOAT64: val = (V)toFloat64(); break;

        }
        return val;
    }
    template <class V>
    bool diva(const V &val)
    {
        bool ret = true;
        switch(m_type)
        {
        case GVARIANT_TYPE_CHAR: toChar() = (gs8)val; break;
        case GVARIANT_TYPE_UCHAR: toUChar() = (gu8)val; break;
        case GVARIANT_TYPE_SHORT: toShort() = (gs16)val; break;
        case GVARIANT_TYPE_USHORT: toUShort() = (gu16)val; break;
        case GVARIANT_TYPE_INT: toInt() = (gs32)val; break;
        case GVARIANT_TYPE_UINT: toUInt() = (gu32)val; break;
        case GVARIANT_TYPE_INT64: toInt64() = (gs64)val; break;
        case GVARIANT_TYPE_UINT64: toUInt64() = (gu64)val; break;
        case GVARIANT_TYPE_FLOAT: toFloat()  = (gf32)val; break;
        case GVARIANT_TYPE_FLOAT64: toFloat64() = (gf64)val; break;
        default:
            ret = false;

        }
        return true;
    }

protected:
    /// Data pointer
    void *m_data;
    /// Type of data held by data pointer
    gs32 m_type;
};
}

#endif // GVARIANT_H
