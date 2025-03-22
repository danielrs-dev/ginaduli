#include "gstring.h"


using namespace gcf;


gString::gString()
{

}

gString::gString(const gString &other):
    gSharedObjectModel<gStringShared>(other)
{

}

gString::gString(const char *astr):
    gSharedObjectModel<gStringShared>(true)
{
    setString(astr);
}
gString::gString(const wchar_t *wstr):
    gSharedObjectModel<gStringShared>(true)
{
    setString(wstr);
}
gString::gString(const string &stdstr):
    gSharedObjectModel<gStringShared>(true)
{
    setString(stdstr);
}
gString::gString(const wstring &wstds):
    gSharedObjectModel<gStringShared>(true)
{
    setString(wstds);
}
gString::~gString()
{

}

bool gString::alloc(gu32 nsize, gu32 nformat)
{
    clear();
    d = new gStringShared();
    return d->alloc(nsize,nformat);
}
void gString::setString(const char *astr, gu32 msize)
{
    if(d == 0)
    {
        d = new gStringShared();
    }
    d->setString(astr, msize);
}
void gString::setString(const wchar_t *wstr, gu32 msize)
{
    if(d == 0)
    {
        d = new gStringShared();
    }
    d->setString(wstr,msize);
}
void gString::setString(const gString &other)
{
    if(other.isEmpty())
    {
        return;
    }
    if(d == 0)
    {
        d = new gStringShared();
    }
    d->copy(other.d);
}

void gString::setString(const string &stdstr)
{
    setString(stdstr.c_str(),stdstr.size());
}
void gString::setString(const wstring &wsstr)
{
    setString(wsstr.c_str(),wsstr.size());
}

void gString::concatenate(const char *astr, gu32 nsize)
{
    if(d == 0)
    {
        d = new gStringShared();
    }
    d->concatenate(astr,nsize);
}
void gString::concatenate(const wchar_t *wstr, gu32 nsize)
{
    if(d == 0)
    {
        d = new gStringShared();
    }
    d->concatenate(wstr, nsize);
}
void gString::concatenate(const gString &other)
{
    if(d == 0)
    {
        d = new gStringShared();
    }
    d->concatenate(other.d);

}
void gString::concatenate(const string &stdstr)
{
   concatenate(stdstr.c_str());
}
void gString::concatenate(const wstring &stdstr)
{
   concatenate(stdstr.c_str());
}

void gString::toLowerCase()
{
    if(d == 0)
    {
        return;
    }
    d->toLowerCase();
}
void gString::toUpperCase()
{
    if(d == 0)
    {
        return;
    }
    d->toUpperCase();
}
void gString::toUnicode()
{
    if(d == 0)
    {
        return;
    }
    d->toUnicode();
}
void gString::toAscii()
{
    if(d == 0)
    {
        return;
    }
    d->toAscii();
}

char *gString::asciiData()
{
    if(d == 0)
    {
        return 0;
    }
    return d->asciiData();
}
const char *gString::asciiData() const
{
    if(d == 0)
    {
        return 0;
    }
    return d->asciiData();
}
wchar_t *gString::unicodeData()
{
    if(d == 0)
    {
        return 0;
    }
    return d->unicodeData();
}
const wchar_t *gString::unicodeData() const
{
    if(d == 0)
    {
        return 0;
    }
    return d->unicodeData();
}
bool gString::isEqual(const char *astr) const
{
    if(d == 0)
    {
        return false;
    }
    return d->equalAscii(astr);
}
bool gString::isEqual(const wchar_t *wstr) const
{
    if(d == 0)
    {
        return false;
    }
    return d->equalUnicode(wstr);
}
bool gString::isEqual(const gString &other) const
{
    if(d == 0)
    {
        return false;
    }
    return d->equal(other.d);
}
bool gString::isEqual(const string &stdstr) const
{
    return isEqual(stdstr.c_str());
}
bool gString::isEqual(const wstring &wstr) const
{
    return isEqual(wstr.c_str());
}
gs32 gString::compare(const char *str) const
{
    if(d == 0)
    {
        if(str)
        {
            return -1;
        }
        return 0;
    }
    return d->compareAscii(str);
}
gs32 gString::compare(const wchar_t *str) const
{
    if(d == 0)
    {
        if(str)
        {
            return -1;
        }
        return 0;
    }
    return d->compareUnicode(str);
}
gs32 gString::compare(const gString &other) const
{
    if(d == 0)
    {
        if(other.isEmpty())
        {
            return 0;
        }
        return -1;
    }
    return d->compare(other.d);
}
gs32 gString::compare(const string &str) const
{
    return compare(str.c_str());
}
gs32 gString::compare(const wstring &str) const
{
    return compare(str.c_str());
}
gString gString::lowerCase() const
{
    gString other;
    other.setString(*this);
    other.toLowerCase();
    other.setShared(true);
    return other;
}
gString gString::upperCase() const
{
    gString other;
    other.setString(*this);
    other.toUpperCase();
    other.setShared(true);
    return other;
}
gu32 gString::size() const
{
    if(d == 0)
    {
        return 0;
    }
    return d->size();
}
gu32 gString::byteSize() const
{
    if(d == 0)
    {
        return 0;
    }
    return d->byteSize();
}
gs32 gString::format() const
{
    if(d == 0)
    {
        return 0;
    }
    return d->format();
}
//Numbers
gs32 gString::toInt(bool *ok, gs32 base) const
{
    if(d == 0)
    {
        if(ok)
        {
            *ok = false;
        }
        return 0;
    }
    return d->toInt(ok,base);
}
gu32 gString::toUInt(bool *ok, gs32 base) const
{
    if(d == 0)
    {
        if(ok)
        {
            *ok = false;
        }
        return 0;
    }
    return d->toUInt(ok,base);
}
gf32 gString::toFloat(bool *ok) const
{
    if(d == 0)
    {
        if(ok)
        {
            *ok = false;
        }
        return 0;
    }
    return d->toFloat(ok);
}
gf64 gString::toFloat64(bool *ok) const
{
    if(d == 0)
    {
        if(ok)
        {
            *ok = false;
        }
        return 0;
    }
    return d->toFloat64(ok);
}
bool gString::isNumeric() const
{
    if(d == 0)
    {
        return false;
    }
    return d->isNumeric();
}
void gString::toNumber(gs32 value, gs32 mformat)
{
    if(d == 0)
    {
        d = new gStringShared();
    }
    d->number(value,mformat);
}
void gString::toNumber(gu32 value, gs32 mformat)
{
    if(d == 0)
    {
        d = new gStringShared();
    }
    d->number(value,mformat);
}
void gString::toNumber(gf64 value, gs32 mformat, char cformat,gs32 precision)
{
    if(d == 0)
    {
        d = new gStringShared();
    }
    d->number(value,mformat,cformat,precision);
}
gs32 gString::inString(const char *str, gu32 len, gu32 startpos) const
{
    if(d == 0)
    {
        return -1;
    }

    return d->inString(str,len, startpos);
}
gs32 gString::inString(const wchar_t *str, gu32 len, gu32 startpos) const
{
    if(d == 0)
    {
        return -1;
    }
    return d->inString(str,len, startpos);

}
gs32 gString::inString(const gString &str,gu32 startpos) const
{
    if(d == 0 || str.isEmpty())
    {
        return -1;
    }
    if(str.format() == GSF_ASCII)
    {
        return d->inString(str.asciiData(), str.size(),startpos);
    }
    else
    {
        return d->inString(str.unicodeData(), str.size());
    }
}
gs32 gString::inString(const string &str,gu32 startpos) const
{
    if(d == 0 || str.empty())
    {
        return -1;
    }
    return d->inString(str.c_str(), str.size(),startpos);
}
gs32 gString::inString(const wstring &str,gu32 startpos) const
{
    if(d == 0 || str.empty())
    {
        return -1;
    }
    return d->inString(str.c_str() , str.size(),startpos);
}
bool gString::isEmpty() const
{
    if(d == 0)
    {
        return true;
    }
    return d->isEmpty();
}
gu32 gString::hash() const
{
    if(d == 0)
    {
        return 0;
    }
    return d->hash();
}
//Static versions
gString gString::number(gs32 value, gs32 mformat)
{
    gString reval;
    reval.toNumber(value,mformat);
    reval.setShared(true);
    return reval;
}
gString gString::number(gu32 value, gs32 mformat)
{
    gString reval;
    reval.toNumber(value,mformat);
    reval.setShared(true);
    return reval;
}
gString gString::number(gf64 value, gs32 mformat, char cformat, gs32 precision)
{
    gString reval;
    reval.toNumber(value,mformat,cformat,precision);
    reval.setShared(true);
    return reval;
}
//Moving on to operators
//Operator assign
gString &gString::operator =(const gString &other)
{
    assign(other);
    return *this;
}
gString &gString::operator =(const char *astr)
{
    setString(astr);
    return *this;
}
gString &gString::operator =(const wchar_t *wstr)
{
    setString(wstr);
    return *this;
}
gString &gString::operator =(const string &stdstr)
{
    setString(stdstr);
    return *this;
}
gString &gString::operator=(const wstring &wstr)
{
    setString(wstr);
    return *this;
}
//Operator comparison ==
bool gString::operator ==(const gString &other) const
{
    return isEqual(other);
}
bool gString::operator ==(const char *astr) const
{
    return isEqual(astr);
}
bool gString::operator ==(const wchar_t *wstr) const
{
    return isEqual(wstr);
}
bool gString::operator ==(const string &stdstr) const
{
    return isEqual(stdstr);
}
bool gString::operator ==(const wstring &stdwstr) const
{
    return isEqual(stdwstr);
}

//Operator !=
bool gString::operator !=(const gString &other) const
{
    return isEqual(other) == false;
}
bool gString::operator !=(const char *astr) const
{
    return isEqual(astr) == false;
}
bool gString::operator !=(const wchar_t *wstr) const
{
    return isEqual(wstr) == false;
}
bool gString::operator !=(const string &stdstr) const
{
    return isEqual(stdstr) == false;
}
bool gString::operator !=(const wstring &stdwstr) const
{
    return isEqual(stdwstr) == false;
}

//Now operator +=
gString &gString::operator += (const  gString &other)
{
    concatenate(other);
    return *this;
}
gString &gString::operator += (const char *astr)
{
    concatenate(astr);
    return *this;
}
gString &gString::operator += (const  wchar_t *wstr)
{
    concatenate(wstr);
    return *this;
}
gString &gString::operator += (const string &stdstr)
{
    concatenate(stdstr);
    return *this;
}
gString &gString::operator += (const wstring &stdwstr)
{
    concatenate(stdwstr);
    return *this;
}
//Now operator +
gString gString::operator + (const gString &other) const
{
    gString ret;
    ret.setString(*this);
    ret.concatenate(other);
    ret.setShared(true);
    return ret;
}
gString gString::operator + (const char *astr) const
{
    gString ret;
    ret.setString(*this);
    ret.concatenate(astr);
    ret.setShared(true);
    return ret;
}
gString gString::operator + (const wchar_t *wstr) const
{
    gString ret;
    ret.setString(*this);
    ret.concatenate(wstr);
    ret.setShared(true);
    return ret;
}
gString gString::operator + (const string &stdstr) const
{
    gString ret;
    ret.setString(*this);
    ret.concatenate(stdstr);
    ret.setShared(true);
    return ret;
}
gString gString::operator + (const wstring &stdwstr) const
{
    gString ret;
    ret.setString(*this);
    ret.concatenate(stdwstr);
    ret.setShared(true);
    return ret;
}
