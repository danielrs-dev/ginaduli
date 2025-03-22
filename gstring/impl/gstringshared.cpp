#include "gstringshared.h"

using namespace gcf;
using namespace std;
gStringShared::gStringShared():
    m_data(0),
    m_size(0),
    m_totalsize(0),
    m_format(GSF_ASCII)
{

}

gStringShared::~gStringShared()
{
    clear();
}

bool gStringShared::alloc(gu32 nsize, gs32 nformat)
{
    gs32 multiplier;
    gu32 i;
    if(m_data)
    {
        clear();
    }
    if(nsize == 0)
    {
        return false;
    }

    if(nformat == GSF_ASCII)
    {
        multiplier = sizeof(char);
    }
    else
    {
        multiplier = sizeof(wchar_t);
    }

    m_totalsize = multiplier * nsize;
    m_size = nsize;
    m_format = nformat;
    m_data = static_cast<char *>(malloc(m_totalsize + multiplier));

    if(m_data == 0)
    {
        return false;
    }

    for(i = 0; i <= (m_totalsize);i++)
    {
        m_data[i] = 0;
    }


    return true;
}

void gStringShared::clear()
{
    if(m_data == 0)
    {
        return;
    }
    free(m_data);
    m_size = 0;
    m_format = GSF_ASCII;
    m_totalsize = 0;
    m_data = 0;
}

char *gStringShared::asciiData()
{
    return m_data;
}
const char *gStringShared::asciiData() const
{
    return m_data;
}
wchar_t *gStringShared::unicodeData()
{
    return reinterpret_cast<wchar_t *>(m_data);
}
const wchar_t *gStringShared::unicodeData() const
{
    return reinterpret_cast<const wchar_t *>(m_data);
}
gs32 gStringShared::format() const
{
    return m_format;
}
gu32 gStringShared::size() const
{
    return m_size;
}
gu32 gStringShared::byteSize() const
{
    return m_totalsize;
}
void gStringShared::copy(const gSharedObject *other)
{
    gu32 i;
    const gStringShared *others = static_cast<const gStringShared *>(other);
    if(others->isEmpty())
    {
        return;
    }

    alloc(others->m_size,others->m_format);

    for(i = 0; i < m_totalsize;i++)
    {
        m_data[i] = others->m_data[i];
    }
}

void gStringShared::concatenate(const char *other, gu32 nsize)
{
    gu32 i,j;
    gu32 newsize;
    if(other == 0)
    {
        return;
    }
    if(nsize == 0)
    {
        nsize = strlen(other);
    }
    if(m_data == 0)
    {
        alloc(nsize,GSF_ASCII);
        copyStrings<char>(m_data,other,nsize);
        return;
    }
    newsize = nsize + m_size;
    //if this string is UNICODE then we convert other string to unicode

    if(m_format == GSF_UNICODE)
    {
        wchar_t *ubuffer;
        wchar_t *rbuffer;

        ubuffer = getUnicodeVersion(other,nsize);


        m_totalsize = newsize * sizeof(wchar_t);
        m_data = static_cast<char *>(realloc(m_data, m_totalsize + sizeof(wchar_t)));
        rbuffer = unicodeData();

        for(i = m_size, j = 0; i < newsize; i++, j++)
        {
            rbuffer[i] = ubuffer[j];
        }
        m_size = newsize;
        rbuffer[m_size] = 0;

        freeString(ubuffer);

    }
    else
    {
        m_totalsize = newsize;
        m_data = static_cast<char *>(realloc(m_data,m_totalsize + 1));

        for(i = m_size, j = 0; i < newsize;i++, j++)
        {
            m_data[i] = other[j];
        }
        m_size = newsize;
        m_data[m_size] = 0;

    }

}

void gStringShared::concatenate(const wchar_t *other, gu32 nsize)
{
    wchar_t *rbuffer;
    gu32 newsize;
    gu32 i,j;
    if(other == 0)
    {
        return;
    }
    if(nsize == 0)
    {
        nsize = wcslen(other);
    }
    if(m_data == 0)
    {
        alloc(nsize,GSF_UNICODE);
        rbuffer = unicodeData();
        copyStrings<wchar_t>(rbuffer,other,nsize);
        return;
    }
    newsize = nsize + m_size;

    if(m_format == GSF_ASCII)
    {
        char *abuffer;

        abuffer = getAsciiVersion(other,nsize);
        m_totalsize = newsize;

        m_data = static_cast<char *>(realloc(m_data,m_totalsize + 1));

        for(i = m_size, j = 0; i < newsize; i++, j++)
        {
            m_data[i] = abuffer[j];
        }
        m_size = newsize;
        m_data[m_size] = 0;

        freeString(abuffer);


    }
    else
    {
        m_totalsize = newsize * sizeof(wchar_t);
        m_data = static_cast<char *>(realloc(m_data,m_totalsize + sizeof(wchar_t)));
        rbuffer = unicodeData();

        for(i = m_size, j=0; i < newsize;i++,j++)
        {
            rbuffer[i] = other[j];
        }
        m_size = newsize;
        rbuffer[m_size] = 0;



    }

}
void gStringShared::concatenate(const gStringShared *other)
{
    if(other == 0)
    {
        return;
    }
    if(m_data == 0)
    {
        copy(other);
        return;

    }
    if(m_format == other->format())
    {
        switch(m_format)
        {
        case GSF_ASCII: concatenate(other->m_data,other->m_size); return;
        case GSF_UNICODE: concatenate(other->unicodeData(),other->m_size); return;
        }
    }
    if(m_format == GSF_ASCII)
    {
        char *adata = getAsciiVersion(other->unicodeData(),other->m_size);
        concatenate(adata,other->m_size);
        freeString(adata);
    }
    else
    {
        wchar_t *wdata = getUnicodeVersion(other->m_data,other->m_size);
        concatenate(wdata,other->m_size);
        freeString(wdata);
    }
}

void gStringShared::setString(const char *str, gu32 msize)
{

    gu32 nsize;
    if(str == 0)
    {
        return;
    }
    if(msize == 0)
    {
        nsize = strlen(str);
    }
    else
    {
        nsize = msize;
    }

    clear();

    alloc(nsize,GSF_ASCII);

    copyStrings<char>(m_data,str,nsize);
}
void gStringShared::setString(const wchar_t *wstr, gu32 msize)
{

    gu32 nsize;
    if(wstr == 0)
    {
        return;
    }
    if(msize == 0)
    {
        nsize = wcslen(wstr);
    }
    else
    {
        nsize = msize;
    }
    wchar_t *wbuff;
    clear();

    alloc(nsize,GSF_UNICODE);
    wbuff = unicodeData();
    copyStrings<wchar_t>(wbuff,wstr,nsize);
}

void gStringShared::toUnicode()
{
    wchar_t *ucode;
    if(m_format == GSF_UNICODE)
    {
        return;
    }
    if(m_data == 0)
    {
        return;
    }

    ucode = getUnicodeVersion(m_data,m_size);
    free(m_data);

    m_data = reinterpret_cast<char *>(ucode);
    m_totalsize = m_totalsize * sizeof(wchar_t);
    m_format = GSF_UNICODE;
}

void gStringShared::toAscii()
{
    char *acode;
    wchar_t *ucode;
    if(m_format == GSF_ASCII)
    {
        return;
    }
    if(m_data == 0)
    {
        return;
    }
    ucode = reinterpret_cast<wchar_t *>(m_data);
    acode = getAsciiVersion(ucode,m_size);
    free(m_data);
    m_data = acode;
    m_totalsize = m_size;
    m_format = GSF_ASCII;
}

//Numbers
bool gStringShared::isNumeric() const
{
    if(m_data == 0)
    {
        return false;
    }
    if(m_format == GSF_ASCII)
    {
        return isNumericTF<char>(m_data,m_size);
    }
    else
    {
        return isNumericTF<wchar_t>(unicodeData(),m_size);
    }
}
gs32 gStringShared::toInt(bool *ok, gs32 base) const
{
    bool isNumber;
    gs32 retval = -1;
    if(m_data == 0)
    {
        if(ok)
        {
            *ok = false;
        }
        return retval;
    }
    isNumber = isNumeric();
    if(ok)
    {
        *ok = isNumber;
    }
    if(isNumber)
    {
        if(m_format == GSF_ASCII)
        {
            retval = gs32(strtol(m_data,0,base));
        }
        else
        {
            retval = gs32(wcstol(unicodeData(),0,base));
        }
    }
    return retval;
}
gu32 gStringShared::toUInt(bool *ok, gs32 base) const
{
    return gu32(toInt(ok,base));
}
gf32 gStringShared::toFloat(bool *ok) const
{
    return gf32(toFloat64(ok));
}
gf64 gStringShared::toFloat64(bool *ok) const
{
    gf64 retval = -1.0;
    bool isNumber;
    if(m_data == 0)
    {
        if(ok)
        {
            *ok = false;
        }
        return retval;
    }
    isNumber = isNumeric();
    if(ok)
    {
        *ok = isNumber;
    }
    if(isNumber)
    {
        if(m_format == GSF_ASCII)
        {
            retval = strtod(m_data,0);
        }
        else
        {
            retval = wcstod(unicodeData(),0);
        }
    }
    return retval;
}
void gStringShared::number(gs32 value, gs32 mformat)
{
    clear();

    if(mformat == GSF_ASCII)
    {
        m_data = numberAscii<gs32>(value,"%d",&m_size);

    }
    else
    {
        m_data = reinterpret_cast<char*>(numberUnicode<gs32>(value,L"%d",&m_size));
    }
    m_totalsize = m_size;
    m_format = mformat;
}
void gStringShared::number(gu32 value, gs32 mformat)
{
    clear();
    if(mformat == GSF_ASCII)
    {
        m_data = numberAscii<gu32>(value,"%u",&m_size);
    }
    else
    {
        m_data= reinterpret_cast<char *>(numberUnicode<gu32>(value,L"%u",&m_size));
    }
    m_totalsize = m_size;
    m_format = mformat;
}
void gStringShared::number(gf64 value, gs32 mformat, char cformat, gs32 precision)
{
    clear();
    if(mformat == GSF_ASCII)
    {
        m_data = floatNumberAscii<gf64>(value,cformat,precision,&m_size);
    }
    else
    {
        m_data = reinterpret_cast<char *>(floatNumberUnicode<gf64>(value,cformat,precision,&m_size));
    }
    m_totalsize = m_size;
    m_format = mformat;
}

wchar_t *gStringShared::getUnicodeVersion(const char *src, gu32 nsize)
{
    wchar_t *news;
    if(src == 0)
    {
        return 0;
    }
    if(nsize == 0)
    {
        return 0;
    }
    news = static_cast<wchar_t *>(malloc(nsize * sizeof(wchar_t) + sizeof(wchar_t)));
    news[nsize] = 0;
    mbstowcs(news,src,nsize);

    return news;
}

char *gStringShared::getAsciiVersion(const wchar_t *src, gu32 nsize)
{
    char *retval;
    if(src == 0)
    {
        return 0;
    }
    if(nsize == 0)
    {
        return 0;
    }
    retval = static_cast<char *>(malloc(nsize + 1));
    retval[nsize] = 0;
    wcstombs(retval,src,nsize);

    return retval;
}

void gStringShared::freeString(void *str)
{
    if(str)
    {
        free(str);
    }
}

bool gStringShared::equalAscii(const char *other) const
{
    if(m_data)
    {
        if(other)
        {
            return strcmp(m_data,other) == 0;
        }
        else
        {
            return false;
        }
    }
    if(other == 0)
    {
        return true;
    }
    return false;

}
bool gStringShared::equalUnicode(const wchar_t *other) const
{
    const wchar_t *rbuff = unicodeData();
    if(m_data)
    {
        if(other)
        {
            return wcscmp(rbuff,other) == 0;
        }
        else
        {
            return false;
        }
    }
    if(other == 0)
    {
        return true;
    }
    return false;


}
bool gStringShared::equal(const gStringShared *other) const
{
    bool retval;

    if(other)
    {
        if(other->format() == m_format)
        {
            switch(m_format)
            {
            case GSF_ASCII: return equalAscii(other->m_data);
            case GSF_UNICODE:
            {
                const wchar_t *buff = other->unicodeData();
                return equalUnicode(buff);
            }
            }
        }

        switch(m_format)
        {
        case GSF_ASCII:
        {
            char *odata = getAsciiVersion(other->unicodeData(),other->size());
            retval = equalAscii(odata);
            freeString(odata);
        }
        case GSF_UNICODE:
        {
            wchar_t *odata = getUnicodeVersion(other->asciiData(),other->size());
            retval = equalUnicode(odata);
            freeString(odata);
        }

        }
        return retval;
    }
    // both are null then they are equals
    if(m_data == 0)
    {
        return true;
    }
    return false;
}
gs32 gStringShared::compareAscii(const char *other) const
{
    if(m_data)
    {
        if(other)
        {
            return strcmp(m_data,other);
        }
        else
        {
            return 1;
        }
    }
    if(other == 0)
    {
        return 0;
    }
    return -1;
}
gs32 gStringShared::compareUnicode(const wchar_t *other) const
{
    if(m_data)
    {
        if(other)
        {
            const wchar_t *wcdata = unicodeData();
            return wcscmp(wcdata,other);
        }
        else
        {
            return 1;
        }
    }
    if(other == 0)
    {
        return 0;
    }
    return -1;
}
gs32 gStringShared::compare(const gStringShared *other) const
{
    bool retval;

    if(other)
    {
        if(other->format() == m_format)
        {
            switch(m_format)
            {
            case GSF_ASCII: return compareAscii(other->m_data);
            case GSF_UNICODE:
            {
                const wchar_t *buff = other->unicodeData();
                return compareUnicode(buff);
            }
            }
        }

        switch(m_format)
        {
        case GSF_ASCII:
        {
            char *odata = getAsciiVersion(other->unicodeData(),other->size());
            retval = compareAscii(odata);
            freeString(odata);
        }
        case GSF_UNICODE:
        {
            wchar_t *odata = getUnicodeVersion(other->asciiData(),other->size());
            retval = compareUnicode(odata);
            freeString(odata);
        }

        }
        return retval;
    }
    // both are null then they are equals
    if(m_data == 0)
    {
        return 0;
    }
    return 1;
}
gu32 gStringShared::hash() const
{
    gu32 hashvalue = 5381;
    gu32 i;
    if(m_data == 0)
    {
        return 0;
    }
    if(m_format == GSF_ASCII)
    {
        const char *sdata = m_data;
        for(i = 0; i < m_size; i++)
        {
            hashvalue = ((hashvalue << 5) + hashvalue) + gu32(sdata[i]);
        }
    }
    else
    {
        const wchar_t *sdata = unicodeData();
        for(i = 0; i < m_size; i++)
        {
            hashvalue = ((hashvalue << 5) + hashvalue) + gu32(sdata[i]);
        }
    }
    return hashvalue;

}

void gStringShared::toLowerCase()
{
    gu32 i;
    if(m_data == 0)
    {
        return;
    }
    if(m_format == GSF_ASCII)
    {
        for(i = 0; i < m_size; i++)
        {
            m_data[i] = char(tolower(m_data[i]));
        }
    }
    else
    {
        wchar_t *wcdata = unicodeData();
        for(i = 0; i < m_size; i++)
        {
            wcdata[i] = wchar_t(towlower(wcdata[i]));
        }
    }
}
void gStringShared::toUpperCase()
{
    gu32 i;
    if(m_data == 0)
    {
        return;
    }
    if(m_format == GSF_ASCII)
    {
        for(i = 0; i < m_size; i++)
        {
            m_data[i] = char(toupper(m_data[i]));
        }
    }
    else
    {
        wchar_t *wcdata = unicodeData();
        for(i = 0; i < m_size; i++)
        {
            wcdata[i] = wchar_t(towupper(wcdata[i]));
        }
    }
}
bool gStringShared::isEmpty() const
{
    return m_data == 0;
}

gs32 gStringShared::inString(const char *str, gu32 nsize, gu32 startpos) const
{
    gu32 i;
    gu32 vr;
    if(m_format == GSF_UNICODE)
    {
        return -1;
    }
    if(nsize == 0)
    {
        nsize = strlen(str);
    }
    for(i = startpos; i < m_size; i++)
    {
        vr = match<char>(str,nsize,i);
        if(vr != -1)
        {
            return i;
        }
    }
    return -1;
}
gs32 gStringShared::inString(const wchar_t *str, gu32 nsize, gu32 startpos) const
{
    gu32 i;
    gu32 vr;
    if(m_format == GSF_ASCII)
    {
        return -1;
    }
    if(nsize == 0)
    {
        nsize = wcslen(str);
    }
    for(i = startpos; i < m_size; i++)
    {
        vr = match<wchar_t>(str,nsize,i);
        if(vr != -1)
        {
            return i;
        }
    }
    return -1;
}
