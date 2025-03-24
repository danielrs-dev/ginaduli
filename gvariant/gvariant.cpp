#include "gvariant.h"
#include "gmath/gmath.h"

using namespace gcf;

gVariant::gVariant():
    m_data(0),
    m_type(GVARIANT_TYPE_UNASSIGNED)
{

}
gVariant::gVariant(const gVariant &other)
{
    copy(other);
}
gVariant::gVariant(gs8 cvalue):
    m_data(new gs8(cvalue)),
    m_type(GVARIANT_TYPE_CHAR)
{

}
gVariant::gVariant(gu8 cvalue):
    m_data(new gu8(cvalue)),
    m_type(GVARIANT_TYPE_UCHAR)
{

}
gVariant::gVariant(gs16 cvalue):
    m_data(new gs16(cvalue)),
    m_type(GVARIANT_TYPE_SHORT)
{

}
gVariant::gVariant(gu16 cvalue):
    m_data(new gu16(cvalue)),
    m_type(GVARIANT_TYPE_USHORT)
{

}
gVariant::gVariant(gs32 cvalue):
    m_data(new gs32(cvalue)),
    m_type(GVARIANT_TYPE_INT)
{

}
gVariant::gVariant(gu32 cvalue):
    m_data(new gu32(cvalue)),
    m_type(GVARIANT_TYPE_UINT)
{

}
gVariant::gVariant(gs64 cvalue):
    m_data(new gs32(cvalue)),
    m_type(GVARIANT_TYPE_INT64)
{

}
gVariant::gVariant(gu64 cvalue):
    m_data(new gu32(cvalue)),
    m_type(GVARIANT_TYPE_UINT64)
{

}
gVariant::gVariant(gf32 cvalue):
    m_data(new gf32(cvalue)),
    m_type(GVARIANT_TYPE_FLOAT)
{

}
gVariant::gVariant(gf64 cvalue):
    m_data(new gf32(cvalue)),
    m_type(GVARIANT_TYPE_FLOAT64)
{

}
gVariant::gVariant(const gString &str):
    m_data(new gString(str)),
    m_type(GVARIANT_TYPE_STRING)
{

}
gVariant::gVariant(const gVector2f &vec):
    m_data(new gVector2f(vec)),
    m_type(GVARIANT_TYPE_VECTOR2F)
{

}
gVariant::gVariant(const gDateTime &dtime):
    m_data(new gDateTime(dtime)),
    m_type(GVARIANT_TYPE_DATETIME)
{

}
gVariant::gVariant(const char *str):
    m_data(new gString(str)),
    m_type(GVARIANT_TYPE_STRING)
{

}
gVariant::gVariant(const wchar_t *str):
    m_data(new gString(str)),
    m_type(GVARIANT_TYPE_STRING)
{

}
gVariant::~gVariant()
{
    clear();
}

void gVariant::clear()
{
    switch(m_type)
    {
    case GVARIANT_TYPE_CHAR: variantDelete<gs8>(); break;
    case GVARIANT_TYPE_UCHAR: variantDelete<gu8>(); break;
    case GVARIANT_TYPE_SHORT: variantDelete<gs16>(); break;
    case GVARIANT_TYPE_USHORT: variantDelete<gu16>(); break;
    case GVARIANT_TYPE_INT: variantDelete<gs32>(); break;
    case GVARIANT_TYPE_UINT: variantDelete<gu32>(); break;
    case GVARIANT_TYPE_INT64: variantDelete<gs64>(); break;
    case GVARIANT_TYPE_UINT64: variantDelete<gu64>(); break;
    case GVARIANT_TYPE_FLOAT: variantDelete<gf32>(); break;
    case GVARIANT_TYPE_FLOAT64: variantDelete<gf64>(); break;
    case GVARIANT_TYPE_STRING: variantDelete<gString>(); break;
    case GVARIANT_TYPE_VECTOR2F: variantDelete<gVector2f>();break;
    case GVARIANT_TYPE_DATETIME: variantDelete<gDateTime>(); break;
    }
    m_type =GVARIANT_TYPE_UNASSIGNED;
    m_data = 0;
}
bool gVariant::alloc(gs32 mtype)
{
    switch(mtype)
    {
    case GVARIANT_TYPE_CHAR: m_data = variantNew<gs8>(); break;
    case GVARIANT_TYPE_UCHAR: m_data = variantNew<gu8>(); break;
    case GVARIANT_TYPE_SHORT: m_data = variantNew<gs16>(); break;
    case GVARIANT_TYPE_USHORT: m_data = variantNew<gu16>(); break;
    case GVARIANT_TYPE_INT: m_data = variantNew<gs32>(); break;
    case GVARIANT_TYPE_UINT: m_data = variantNew<gu32>(); break;
    case GVARIANT_TYPE_INT64: m_data = variantNew<gs64>(); break;
    case GVARIANT_TYPE_UINT64: m_data = variantNew<gu64>(); break;
    case GVARIANT_TYPE_FLOAT: m_data = variantNew<gf32>(); break;
    case GVARIANT_TYPE_FLOAT64: m_data = variantNew<gf64>(); break;
    case GVARIANT_TYPE_STRING: m_data = variantNew<gString>(); break;
    case GVARIANT_TYPE_VECTOR2F: m_data = variantNew<gVector2f>();break;
    case GVARIANT_TYPE_DATETIME: m_data = variantNew<gDateTime>(); break;
    }
    m_type = mtype;
    return m_data != 0;
}
void gVariant::copy(const gVariant &other)
{
    clear();
    switch(other.m_type)
    {
    case GVARIANT_TYPE_CHAR: m_data = variantNew<gs8>(other.toChar()); break;
    case GVARIANT_TYPE_UCHAR: m_data = variantNew<gu8>(other.toUChar()); break;
    case GVARIANT_TYPE_SHORT: m_data = variantNew<gs16>(other.toShort()); break;
    case GVARIANT_TYPE_USHORT: m_data = variantNew<gu16>(other.toUShort()); break;
    case GVARIANT_TYPE_INT: m_data = variantNew<gs32>(other.toInt()); break;
    case GVARIANT_TYPE_UINT: m_data = variantNew<gu32>(other.toUInt()); break;
    case GVARIANT_TYPE_INT64: m_data = variantNew<gs64>(other.toInt64()); break;
    case GVARIANT_TYPE_UINT64: m_data = variantNew<gu64>(other.toUInt64()); break;
    case GVARIANT_TYPE_FLOAT: m_data = variantNew<gf32>(other.toFloat()); break;
    case GVARIANT_TYPE_FLOAT64: m_data = variantNew<gf64>(other.toFloat64()); break;
    case GVARIANT_TYPE_STRING: m_data = variantNew<gString>(other.toString()); break;
    case GVARIANT_TYPE_VECTOR2F: m_data = variantNew<gVector2f>(other.toVector2f()); break;
    case GVARIANT_TYPE_DATETIME: m_data = variantNew<gDateTime>(other.toDateTime()); break;
    }
    m_type =other.m_type;
}
void gVariant::setValue(gs8 cvalue, bool setnew)
{
    if(!setnew && isNumeric())
    {
        if(diva<gs8>(cvalue))
        {
            return;
        }
    }
    clear();
    m_data = new gs8(cvalue);
    m_type = GVARIANT_TYPE_CHAR;
}
void gVariant::setValue(gu8 cvalue, bool setnew)
{
    if(!setnew && isNumeric())
    {
        if(diva<gu8>(cvalue))
        {
            return;
        }
    }
    clear();
    m_data = new gu8(cvalue);
    m_type = GVARIANT_TYPE_UCHAR;
}
void gVariant::setValue(gs16 cvalue, bool setnew)
{
    if(!setnew && isNumeric())
    {
        if(diva<gs16>(cvalue))
        {
            return;
        }
    }
    clear();
    m_data = new gs16(cvalue);
    m_type = GVARIANT_TYPE_SHORT;
}
void gVariant::setValue(gu16 cvalue, bool setnew)
{
    if(!setnew && isNumeric())
    {
        if(diva<gu16>(cvalue))
        {
            return;
        }
    }
    clear();
    m_data = new gu16(cvalue);
    m_type = GVARIANT_TYPE_USHORT;
}
void gVariant::setValue(gs32 cvalue, bool setnew)
{
    if(!setnew && isNumeric())
    {
        if(diva<gs32>(cvalue))
        {
            return;
        }
    }
    clear();
    m_data = new gs32(cvalue);
    m_type = GVARIANT_TYPE_INT;
}
void gVariant::setValue(gu32 cvalue, bool setnew)
{
    if(!setnew && isNumeric())
    {
        if(diva<gu32>(cvalue))
        {
            return;
        }
    }
    clear();
    m_data = new gu32(cvalue);
    m_type = GVARIANT_TYPE_UINT;
}
void gVariant::setValue(gs64 cvalue, bool setnew)
{
    if(!setnew && isNumeric())
    {
        if(diva<gs64>(cvalue))
        {
            return;
        }
    }
    clear();
    m_data = new gs64(cvalue);
    m_type = GVARIANT_TYPE_INT64;
}
void gVariant::setValue(gu64 cvalue, bool setnew)
{
    if(!setnew && isNumeric())
    {
        if(diva<gu64>(cvalue))
        {
            return;
        }
    }
    clear();
    m_data = new gu64(cvalue);
    m_type = GVARIANT_TYPE_UINT64;
}
void gVariant::setValue(gf32 cvalue, bool setnew)
{
    if(!setnew && isNumeric())
    {
        if(diva<gf32>(cvalue))
        {
            return;
        }
    }
    clear();
    m_data = new gf32(cvalue);
    m_type = GVARIANT_TYPE_FLOAT;
}
void gVariant::setValue(gf64 cvalue, bool setnew)
{
    if(!setnew && isNumeric())
    {
        if(diva<gf64>(cvalue))
        {
            return;
        }
    }
    clear();
    m_data = new gf64(cvalue);
    m_type = GVARIANT_TYPE_FLOAT64;
}
void gVariant::setValue(const gString &str, bool setnew)
{
    if(!setnew && isString())
    {
        toString() = str;
        return;
    }
    clear();
    m_data = new gString(str);
    m_type = GVARIANT_TYPE_STRING;
}
void gVariant::setValue(const gVector2f &vec, bool setnew)
{
    if(!setnew && isVector2f())
    {
        toVector2f() = vec;
        return;
    }
    clear();
    m_data = new gVector2f(vec);
    m_type = GVARIANT_TYPE_VECTOR2F;
}
void gVariant::setValue(const gDateTime &dtime, bool setnew)
{
    if(!setnew && isDateTime())
    {
        toDateTime() = dtime;
        return;
    }
    clear();
    m_data = new gDateTime(dtime);
    m_type = GVARIANT_TYPE_DATETIME;
}
void gVariant::setValue(const char *str, bool setnew)
{
    if(!setnew && isString())
    {
        toString() = str;
        return;
    }
    clear();
    m_data = new gString(str);
    m_type = GVARIANT_TYPE_STRING;
}
void gVariant::setValue(const wchar_t *str, bool setnew)
{
    if(!setnew && isString())
    {
        toString() = str;
        return;
    }
    clear();
    m_data = new gString(str);
    m_type = GVARIANT_TYPE_STRING;
}
void gVariant::setRawPointer(void *ptr, gs32 mtype)
{
    m_data = ptr;
    m_type = mtype;
}

gs8 &gVariant::toChar()
{
    return cast<gs8>();
}
const gs8 &gVariant::toChar() const
{
    return cast<gs8>();
}
gu8 &gVariant::toUChar()
{
    return cast<gu8>();
}
const gu8 &gVariant::toUChar() const
{
    return cast<gu8>();
}
gs16 &gVariant::toShort()
{
    return cast<gs16>();
}
const gs16 &gVariant::toShort() const
{
    return cast<gs16>();
}
gu16 &gVariant::toUShort()
{
    return cast<gu16>();
}
const gu16 &gVariant::toUShort() const
{
    return cast<gu16>();
}
gs32 &gVariant::toInt()
{
    return cast<gs32>();
}
const gs32 &gVariant::toInt() const
{
    return cast<gs32>();
}
gu32 &gVariant::toUInt()
{
    return cast<gu32>();
}
const gu32 &gVariant::toUInt() const
{
    return cast<gu32>();
}
gs64 &gVariant::toInt64()
{
    return cast<gs64>();
}
const gs64 &gVariant::toInt64() const
{
    return cast<gs64>();
}
gu64 &gVariant::toUInt64()
{
    return cast<gu64>();
}
const gu64 &gVariant::toUInt64() const
{
    return cast<gu64>();
}
gf32 &gVariant::toFloat()
{
    return cast<gf32>();
}
const gf32 &gVariant::toFloat() const
{
    return cast<gf32>();
}
gf64 &gVariant::toFloat64()
{
    return cast<gf64>();
}
const gf64 &gVariant::toFloat64() const
{
    return cast<gf64>();
}
gString &gVariant::toString()
{
    return cast<gString>();
}
const gString &gVariant::toString() const
{
    return cast<gString>();
}
gVector2f &gVariant::toVector2f()
{
    return cast<gVector2f>();
}
const gVector2f &gVariant::toVector2f() const
{
    return cast<gVector2f>();
}
gDateTime &gVariant::toDateTime()
{
    return cast<gDateTime>();
}
const gDateTime &gVariant::toDateTime() const
{
    return cast<gDateTime>();
}
void *gVariant::toPointer()
{
    return m_data;
}
const void *gVariant::toPointer() const
{
    return m_data;
}
void gVariant::arithObject(const gVariant &other, gs32 op)
{

    switch(other.m_type)
    {
    case GVARIANT_TYPE_CHAR: arithOp<gs8>(other.toChar(),op); break;
    case GVARIANT_TYPE_UCHAR: arithOp<gu8>(other.toUChar(),op); break;
    case GVARIANT_TYPE_SHORT: arithOp<gs16>(other.toShort(),op); break;
    case GVARIANT_TYPE_USHORT: arithOp<gu16>(other.toUShort(),op); break;
    case GVARIANT_TYPE_INT: arithOp<gs32>(other.toInt(),op); break;
    case GVARIANT_TYPE_UINT: arithOp<gu32>(other.toUInt(),op); break;
    case GVARIANT_TYPE_INT64: arithOp<gs64>(other.toInt64(),op); break;
    case GVARIANT_TYPE_UINT64: arithOp<gu64>(other.toUInt64(),op); break;
    case GVARIANT_TYPE_FLOAT: arithOp<gf32>(other.toFloat(),op); break;
    case GVARIANT_TYPE_FLOAT64: arithOp<gf64>(other.toFloat64(),op); break;
    case GVARIANT_TYPE_VECTOR2F:arithOp<gf32>(other.toVector2f(),op); break;
    case GVARIANT_TYPE_STRING:
        if(op == 0)
        {
            gString *str = pcast<gString>();
            (*str)+=other.toString();
        }
    }
}
bool gVariant::boolObject(const gVariant &other, gs32 op) const
{
    switch(other.m_type)
    {
    case GVARIANT_TYPE_CHAR: return opBool<gs8>(other.toChar(),op); break;
    case GVARIANT_TYPE_UCHAR: return opBool<gu8>(other.toUChar(),op); break;
    case GVARIANT_TYPE_SHORT: return opBool<gs16>(other.toShort(),op); break;
    case GVARIANT_TYPE_USHORT: return opBool<gu16>(other.toUShort(),op); break;
    case GVARIANT_TYPE_INT: return opBool<gs32>(other.toInt(),op); break;
    case GVARIANT_TYPE_UINT: return opBool<gu32>(other.toUInt(),op); break;
    case GVARIANT_TYPE_INT64: return opBool<gs64>(other.toInt64(),op); break;
    case GVARIANT_TYPE_UINT64: return opBool<gu64>(other.toUInt64(),op); break;
    case GVARIANT_TYPE_FLOAT: return opBool<gf32>(other.toFloat(),op); break;
    case GVARIANT_TYPE_FLOAT64: return opBool<gf64>(other.toFloat64(),op); break;
    case GVARIANT_TYPE_VECTOR2F: return opBool<gf32>(other.toVector2f(),op); break;
    case GVARIANT_TYPE_DATETIME: return opBool(other.toDateTime(),op); break;
    case GVARIANT_TYPE_STRING:
        const gString *str = pcast<gString>();
        switch(op)
        {
        case 0: return str->isEqual(other.toString());break;
        case 1: return str->isEqual(other.toString()) == false; break;
        }

    }
    return false;
}
gu32 gVariant::size() const
{
    gu32 retsize;
    switch(m_type)
    {
    case GVARIANT_TYPE_CHAR:
    case GVARIANT_TYPE_UCHAR:
        retsize = sizeof(gs8);
        break;
    case GVARIANT_TYPE_SHORT:
    case GVARIANT_TYPE_USHORT:
        retsize = sizeof(gs16);
        break;
    case GVARIANT_TYPE_INT:
    case GVARIANT_TYPE_UINT:
        retsize = sizeof(gs32);
        break;
    case GVARIANT_TYPE_INT64:
    case GVARIANT_TYPE_UINT64:
        retsize = sizeof(gs64);
        break;
    case GVARIANT_TYPE_FLOAT:
        retsize = sizeof(gf32);
        break;
    case GVARIANT_TYPE_FLOAT64:
        retsize = sizeof(gf64);
        break;
    case GVARIANT_TYPE_STRING:
        retsize = toString().size();
        break;
    case GVARIANT_TYPE_VECTOR2F:
        retsize = sizeof(gf32) * 2;
        break;
    default:
        retsize = 0;
    }
    return retsize;
}
gVariant &gVariant::operator = (const gVariant &other)
{
    copy(other);
    return *this;
}
gVariant &gVariant::operator += (const gVariant &other)
{
    arithObject(other,0);
    return *this;
}
gVariant &gVariant::operator -= (const gVariant &other)
{
    arithObject(other,1);
    return *this;
}
gVariant &gVariant::operator *= (const gVariant &other)
{
    arithObject(other,2);
    return *this;
}
gVariant &gVariant::operator /= (const gVariant &other)
{
    arithObject(other,3);
    return *this;
}
gVariant gVariant::operator + (const gVariant &other) const
{
    gVariant ret;
    ret.copy(*this);
    ret += other;
    return ret;
}
gVariant gVariant::operator - (const gVariant &other) const
{
    gVariant ret;
    ret.copy(*this);
    ret -= other;
    return ret;
}
gVariant gVariant::operator * (const gVariant &other) const
{
    gVariant ret;
    ret.copy(*this);
    ret *= other;
    return ret;
}
gVariant gVariant::operator / (const gVariant &other) const
{
    gVariant ret;
    ret.copy(*this);
    ret /= other;
    return ret;
}

bool gVariant::operator == (const gVariant &other) const
{
    return boolObject(other, 0);
}
bool gVariant::operator != (const gVariant &other) const
{
    return boolObject(other, 1);
}
bool gVariant::operator < (const gVariant &other) const
{
    return boolObject(other, 2);
}
bool gVariant::operator > (const gVariant &other) const
{
    return boolObject(other, 3);
}
bool gVariant::operator <= (const gVariant &other) const
{
    return boolObject(other, 4);
}
bool gVariant::operator >= (const gVariant &other) const
{
    return boolObject(other, 5);
}
void gVariant::squareRoot()
{
    gScalar val;
    val = deva<gScalar>();
    val = gMath::fastSquareRoot(val);
    diva<gScalar>(val);
}
void gVariant::power(gu32 n)
{
    gScalar val;
    val = deva<gScalar>();
    val = gMath::power(val,n);
    diva<gScalar>(val);
}
void gVariant::sine()
{
    gScalar val = deva<gScalar>();
    val = gMath::sine(val);
    diva<gScalar>(val);
}
void gVariant::cosine()
{
    gScalar val = deva<gScalar>();
    val = gMath::cosine(val);
    diva<gScalar>(val);;
}
void gVariant::tangent()
{
    gScalar val = deva<gScalar>();
    val = gMath::tangent(val);
    diva<gScalar>(val);
}
void gVariant::asine()
{
    gScalar val = deva<gScalar>();
    val = gMath::asine(val);
    diva<gScalar>(val);;
}
void gVariant::acosine()
{
    gScalar val = deva<gScalar>();
    val = gMath::acosine(val);
    diva<gScalar>(val);
}
void gVariant::atangent()
{
    gScalar val = deva<gScalar>();
    val = gMath::atangent(val);
    diva<gScalar>(val);
}
gs32 gVariant::type() const
{
    return m_type;
}
bool gVariant::isEmpty() const
{
    return (m_data == 0);
}
bool gVariant::isString() const
{
    return (m_type == GVARIANT_TYPE_STRING);
}
bool gVariant::isNumeric() const
{
    bool ret = (m_type >= 0 && m_type <= GVARIANT_TYPE_FLOAT64);
    return ret;
}
bool gVariant::isSigned() const
{
    bool ret;
    switch(m_type)
    {
    case GVARIANT_TYPE_CHAR:
    case GVARIANT_TYPE_SHORT:
    case GVARIANT_TYPE_INT:
    case GVARIANT_TYPE_INT64:
    case GVARIANT_TYPE_FLOAT:
    case GVARIANT_TYPE_FLOAT64:
        ret = true;
        break;
    default:
        ret = false;

    }
    return ret;
}
bool gVariant::isVector2f() const
{
    return (m_type == GVARIANT_TYPE_VECTOR2F);
}
bool gVariant::isDateTime() const
{
    return (m_type == GVARIANT_TYPE_DATETIME);
}
gString gVariant::asString() const
{
    gString ret;

    if(m_type >= 0 && m_type <= GVARIANT_TYPE_UINT64)
    {
        gs32 vali;
        gs32 valu;
        if(isSigned())
        {
            vali = deva<gs32>();
            ret.toNumber(vali,GSF_ASCII);
        }
        else
        {
            valu = deva<gu32>();
            ret.toNumber(valu,GSF_ASCII);
        }

    }
    else if(m_type >= GVARIANT_TYPE_FLOAT && m_type <= GVARIANT_TYPE_FLOAT64)
    {
        gf64 val = deva<gf64>();
        ret.toNumber(val,GSF_ASCII);
    }
    else if(m_type == GVARIANT_TYPE_STRING)
    {
        ret = toString();
    }
    ret.setShared(true);
    return ret;
}
bool gVariant::opBool(const gDateTime &dt, gs32 op) const
{
    if(!isDateTime())
    {
        return false;
    }
    const gDateTime &dtime = toDateTime();
    switch(op)
    {
    case 0: return (dtime == dt);
    case 1: return (dtime != dt);
    case 2: return (dtime < dt);
    case 3: return (dtime > dt);
    case 4: return (dtime <= dt);
    case 5: return (dtime >= dt);
    default: return false;
    }

}

