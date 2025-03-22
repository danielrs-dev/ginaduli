#ifndef GSTRINGSHARED_H
#define GSTRINGSHARED_H
/**************************************************************************
        GINA DULI C++ Framework
        Author: Daniel Rios
        File: gstring.h
        Description: Implementation of the class gStringShared.
***************************************************************************/
#include <base/gsharedobject.h>
#include <cstdlib>
#include <stdlib.h>
#include <cstdio>
#include <cwchar>
#include <cstring>
#include <cctype>

namespace gcf
{
    /*! \brief The gStringShared class is the base for string manipulation.
               This is held as a property on the object gString. This object
               is shareable among other gString objects.
     */
    class gStringShared : public gSharedObject
    {
    public:
        /// Constructor
        gStringShared();
        /// Destructor
        ~gStringShared();
        /*! \brief Allocates memory for the string given a size and format.
            \param nsize: String size in character wide.
            \param nformat: Either GSF_ASCII or GSF_UNICODE.
            \return true if success else false.
        */
        bool alloc(gu32 nsize, gs32 nformat);
        /// Clears the string.
        void clear();
        /*! \brief Gets the string pointer in ASCII format.
            \return Pointer to string.
        */
        char *asciiData();
        /// Const version of gStringShared::asciiData().
        const char *asciiData() const;
        /*! \brief Gets the string pointer in UNICODE format.
            \return Pointer to string.
        */
        wchar_t *unicodeData();
        /// Const version of gStringShared::unicodeData().
        const wchar_t *unicodeData() const;
        /*! \brief Gets the format of the string.
            \return Either GSF_ASCII or GSF_UNICODE.
        */
        gs32 format() const;
        /*! \brief Gets the size of the string in charater wide.
            \return Size of string.
        */
        gu32 size() const;
        /*! \brief Gets the size of the string in bytes size.
            \return Size of string.
        */
        gu32 byteSize() const;
        /*! \brief Concatenates another string to this string. ASCII Version.
           \param other: ASCII String to concatenate.
           \param nsize: Size of other param string.
       */
        void concatenate(const char *other, gu32 nsize = 0);
        /*! \brief Concatenates another string to this string. UNICODE Version.
           \param other: UNICODE String to concatenate.
           \param nsize: Size of other param string.
       */
        void concatenate(const wchar_t *other, gu32 nsize = 0);
        /*! \brief Concatenates another string to this string from another
                  string object.
           \param other: String to concatenate.
       */
        void concatenate(const gStringShared *other);
        /*! \brief Sets the string value given a null terminated string.
                  ASCII version.
           \param str: NULL terminated string to set.
           \param msize: Size of str,
       */
        void setString(const char *str, gu32 msize);
        /*! \brief Sets the string value given a null terminated string.
                  UNICODE version.
           \param wstr: NULL terminated string to set.
           \param msize: Size of wstr,
       */
        void setString(const wchar_t *wstr, gu32 msize);
        /*! \brief Copies a string object to this object.
           \param other: String object to copy.
       */
        virtual void copy(const gSharedObject *other);
        /// Transforms this string to unicode format.
        void toUnicode();
        /// Transforms this string to ASCII format.
        void toAscii();
        /*! \brief Returns whether string is empty or not.
            \retur true if empty else false.
        */
        bool isEmpty() const;
        /*! \brief Compares this string to another. ASCII version.
            \param other: NULL terminated string  to compare.
            \return true if equal else false.
        */
        bool equalAscii(const char *other) const;
        /*! \brief Compares this string to another. UNICODE version.
            \param other: NULL terminated string to compare.
            \return true if equal else false.
        */
        bool equalUnicode(const wchar_t *other) const;
        /*! \brief Compares this string to another.
            \param other: String to compare.
            \return true if equal else false.
        */
        bool equal(const gStringShared *other) const;
        gs32 compareAscii(const char *other) const;
        gs32 compareUnicode(const wchar_t *other) const;
        gs32 compare(const gStringShared *other) const;
        /*! \brief Gets the hash value of the string.
            \return Hash value integer.
        */
        gu32 hash() const;
        /// Transforms this string to lower case characters.
        void toLowerCase();
        /// Transforms this string to upper case characters.
        void toUpperCase();
        /*! \brief Gets a unicode version of ASCII string.
            \param src: NULL terminated string.
            \param nsize: Size of src.
            \return Pointer to a new unicode string.
        */
        static wchar_t *getUnicodeVersion(const char *src, gu32 nsize);
        /*! \brief Gets a ASCII string from a UNICODE version.
            \param src: NULL terminated string.
            \param nsize: Size of src.
            \return Pointer to a new ASCII string.
        */
        static char *getAsciiVersion(const wchar_t *src, gu32 nsize);
        /*! \brief Deallocates or frees a string.
            \param str: String to deallocate.
        */
        static void freeString(void *str);
        /*! \brief Returns whether the string contains a number or not.
            \return true if string contains a number else false.
        */
        bool isNumeric() const;
        /*! \brief Transforms the string to an integer.
            \param ok: Set it to true if operation happens else false.
            \param base: Base of number.
            \return Integer value held by the string.
        */
        gs32 toInt(bool *ok = 0,gs32 base = 10) const;
        /*! \brief Transforms the string to an unsiged integer.
            \param ok: Set it to true if operation happens else false.
            \param base: Base of number.
            \return Unsigned integer value held by the string.
        */
        gu32 toUInt(bool *ok = 0, gs32 base = 10) const;
        /*! \brief Transforms the string to a float 32 value.
            \param ok: Set it to true if operation happens else false.
            \return Float 32 value held by the string.
        */
        gf32 toFloat(bool *ok = 0) const;
        /*! \brief Transforms the string to a float 64 value.
            \param ok: Set it to true if operation happens else false.
            \return Float 64 value held by the string.
        */
        gf64 toFloat64(bool *ok = 0) const;
        /*! \brief Sets the value of the string as a number given a 32 bit
                   integer value.
            \param value: Integer value.
            \param mformat: Format of string.
        */
        void number(gs32 value,gs32 mformat);
        /*! \brief Sets the value of the string as a number given a 32 bit
                   unsigned integer value.
            \param value: Unsigned integer value.
            \param mformat: Format of string.
        */
        void number(gu32 value,gs32 mformat);
        /*! \brief Sets the value of the string as a number given a 64 bit
                   float value.
            \param value: Float 64 value.
            \param mformat: Format of string.
        */
        void number(gf64 value,gs32 mformat,char cformat,gs32 precision);
        /*! \brief Gets if string holds numeric values.
            \param V: Type string either char or wchar_t
            \param str: NULL terminated string.
            \param nsize: Size of str.
            \return true if is numeric else false.
        */
        gs32 inString(const char *str, gu32 nsize, gu32 startpos = 0) const;
        gs32 inString(const wchar_t *str, gu32 nsize, gu32 startpos = 0) const;
        template<class V>
        bool isNumericTF(const V *str,gu32 nsize) const
        {
            gu32 i;
            gu32 count = 0;
            gu32 pc = 0;
            V val;
            for(i = 0; i < nsize; i++)
            {
                val = str[i];
                if(i == 0)
                {
                    if((val == int('.')) || (val == int('-')) || (isdigit(int(val))))
                    {
                        count++;
                    }
                    if(val == int('.'))
                    {
                        pc++;
                    }
                }
                else
                {
                    if((val == int('.')) || isdigit(int(val)))
                    {
                        count++;
                    }
                    if(val == int('.'))
                    {
                        pc++;
                    }
                }

            }
            return ((count == nsize) && (pc < 2));
        }
        /*! \brief Creates a NULL terminated ASCII string containing
                   a numeric value.
            \param I: Template parameter type of value: ej. int,float.
            \param value: Value.
            \param velt: NULL terminated string with value formating.
            \param nsize: Writable to get size of the new string.
            \return NULL terminated ASCII string with containing numeric value.
        */
        template<class I>
        char *numberAscii(I value,const char *velt, gu32 *nsize)
        {
            char *rval;
            char tval[80];
            gu32 strsize;

            strsize = sprintf(tval,velt,value);

            rval = static_cast<char *>(malloc(strsize + 1));

            copyStrings<char>(rval,tval,strsize);

            rval[strsize] = 0;

            *nsize = strsize;
            return rval;
        }
        /*! \brief Creates a NULL terminated UNICODE string containing
                   a numeric value.
            \param I: Template parameter type of value: ej. int,float.
            \param value: Value.
            \param velt: NULL terminated string with value formating.
            \param nsize: Writable to get size of the new string.
            \return NULL terminated UNICODE string with containing numeric value.
        */
        template<class I>
        wchar_t *numberUnicode(I value, const wchar_t *velt, gu32 *nsize)
        {

            wchar_t *rval;
            wchar_t tval[80];
            gu32 strsize;

            strsize = swprintf(tval,velt,value);
            rval = static_cast<wchar_t *>(malloc(strsize * sizeof(wchar_t) + sizeof(wchar_t)));

            copyStrings<wchar_t>(rval,tval,strsize);
            rval[strsize] = 0;

            *nsize = strsize;
            return rval;
        }
        /*! \brief Creates a NULL terminated ASCII string containing
                   a numeric value.
            \param F: Template parameter type of value: ej. int,float.
            \param value: Value.
            \param cformat: Format of floating point number.
            \param precision: Precision of value.
            \param nsize: Writable to get size of the new string.
            \return NULL terminated ASCII string with containing numeric value.
        */
        template<class F>
        char *floatNumberAscii(F value, char cformat, int precision, gu32 *nsize)
        {
            char *rval;
            char tval[80];
            char frmt[10];
            gu32 strsize;

            sprintf(frmt,"%c.%d%c",37,precision,cformat);
            strsize = sprintf(tval,frmt,value);

            rval = static_cast<char *>(malloc(strsize + 1));

            copyStrings<char>(rval,tval,strsize);
            rval[strsize] = 0;
            *nsize = strsize;
            return rval;
        }
        /*! \brief Creates a NULL terminated UNICODE string containing
                   a numeric value.
            \param F: Template parameter type of value: ej. int,float.
            \param value: Value.
            \param cformat: Format of floating point number.
            \param precision: Precision of value.
            \param nsize: Writable to get size of the new string.
            \return NULL terminated UNICODE string with containing numeric value.
        */
        template<class F>
        wchar_t *floatNumberUnicode(F value, char cformat, int precision, gu32 *nsize)
        {
            wchar_t *rval;
            wchar_t tval[80];
            wchar_t frmt[10];
            gu32 strsize;

            swprintf(frmt,L"%c.%d%c",37,precision,cformat);
            strsize = swprintf(tval,frmt,value);

            rval = static_cast<wchar_t *>(malloc(strsize * sizeof(wchar_t) + sizeof(wchar_t)));

            copyStrings<wchar_t>(rval,tval,strsize);
            rval[strsize] = 0;
            *nsize = strsize;
            return rval;
        }
        /*! \brief Gets the value of type T from an ASCII string containing
                   a numeric value.
            \param T: Type of value.
            \param src: NULL terminated string containing numeric value.
            \param base: Base of value.
            \return Numeric value.
        */
        template<class T>
        static T toNumberAscii(const char *src, int base)
        {
            return static_cast<T>(strtoll(src,0,base));
        }
        /*! \brief Gets the value of type T from an UNICODE string containing
                   a numeric value.
            \param T: Type of value.
            \param src: NULL terminated string containing numeric value.
            \param base: Base of value.
            \return Numeric value.
        */
        template<class T>
        static T toNumberUnicode(const wchar_t *src, int base)
        {
            return static_cast<T>(wcstoll(src,0,base));
        }
        /*! \brief Gets the value of type T from an ASCII string containing
                   a numeric value.
            \param T: Type of value.
            \param src: NULL terminated string containing numeric value.
            \param base: Base of value.
            \return Numeric value.
        */
        template<class F>
        static F toFloatNumberAscii(const char *src)
        {
            return static_cast<F>(strtod(src,0));
        }
        /*! \brief Gets the value of type T from an UNICODE string containing
                   a numeric value.
            \param T: Type of value.
            \param src: NULL terminated string containing numeric value.
            \param base: Base of value.
            \return Numeric value.
        */
        template<class F>
        static F toFloatNumberUnicode(const wchar_t *src)
        {
            return static_cast<F>(wcstod(src,0));
        }
        /*! \brief Copies a string to another.
            \param T: Type of string either char or wchar_t.
            \param dest: Destination NULL terminated string.
            \param src: Source NULL terminated string.
            \param nsize: The size of both strings.
        */
        template<class T>
        static void copyStrings(T *dest, const T *src,gu32 nsize)
        {
            gu32 i;
            for(i = 0; i < nsize; i++)
            {
                dest[i] = src[i];
            }
        }
        template <class T>
        gs32 match(const T *str, gu32 nsize, gu32 pos) const
        {
            gu32 count = pos;
            gu32 mcount = 0;
            gu32 i,j;
            bool bmatch = false;
            T *ptr = reinterpret_cast<T *>(m_data);
            for(i = count, j= 0; j < nsize; i++, j++)
            {
                if(ptr[i] == str[j])
                {
                    bmatch = true;
                    mcount++;
                }
                else
                {
                    if(bmatch)
                    {
                        break;
                    }
                }
            }
            if(mcount == nsize)
            {
                return i;
            }
            return -1;
        }


    protected:
        /// String data
        char *m_data;
        /// Size of string in character wide.
        gu32 m_size;
        /// Total size of string array.
        gu32 m_totalsize;
        /// Format of string
        gs32 m_format;
    };
}

#endif // GSTRINGSHARED_H
