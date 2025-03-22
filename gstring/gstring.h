#ifndef GSTRING_H
#define GSTRING_H

/***********************************************************************
        GINA Duli C++ Framework
        Author: Daniel Rios
        File: gstring.h
        Description: Full functionality of class gString.
                     Unicode and ASCII string container.
************************************************************************/

#include <gstring/impl/gstringshared.h>
#include <base/gsharedobjectmodel.h>
#include <string>
using namespace std;
namespace gcf
{

/*!
 * \brief The class gString is the main representive of the string
 *        data type of the GINA Duli C++ Framework. It encapsulates all
 *        functionality to handle strings
 */
class SHARED_GCF gString : public gSharedObjectModel<gStringShared>
{
public:
    /// Class constructor
    gString();
    /// Class copy constructor
    gString(const gString &other);
    /// Class constructor as a null terminated C string
    gString(const char *astr);
    /// Class constructor as a null terminated Wide String
    gString(const wchar_t *wstr);
    /// Class constructor as std::string from C++ STD Lib
    gString(const string &stds);
    /// Class construcotr as std::wstring from C++ STD Lib
    gString(const wstring &wstds);
    /// Class destructor
    ~gString();

    /*!
     * \brief Allocates memory for a new string. It removes and deallocates
     *        old memory to start a new one.
     * \param nsize: The size of the new string
     * \param nformat: The format of the string either GSF_ASCII or GSF_UNICODE
     * \return true if success false if failed.
     */
    bool alloc(gu32 nsize, gu32 nformat);

    /*!
     *  \brief Writes a string to the object. Old data gets replaced.
     *  \param other: String of the same kind with new data.
     */
    void setString(const gString &other);
    /*!
     *  \brief Writes a string into the object. Old data gets replaced.
     *  \param astr: Null terminated string.
     */
    void setString(const char *astr, gu32 msize = 0);
    /*!
     *  \brief Writes a string into the object. Old data gets replaced.
     *  \param wstr: Null terminated Wide String.
     */
    void setString(const wchar_t *wstr, gu32 msize = 0);
    /*! \brief Writes a string into the string object. Old data gets
               replaced.
        \param stdstr: std::string reference object.
    */
    void setString(const string &stdstr);
    /*! \brief Writes a string into the string object. Old data gets
               replaced.
        \param wsstr: std::wstring reference object.
    */
    void setString(const wstring &wsstr);
    /*! \brief Gets the string pointer in ASCII format as null terminated
               string. This basically returns the internal pointer.
        \return NULL terminated string of object data.
    */
    char *asciiData();
    /// Const version of gString::asciiData()
    const char *asciiData() const;
    /*! \brief Gets the string pointer in UNICODE format as null terminated
               string. This basically returns the internal pointer.
        \return NULL terminated string of object data.
    */
    wchar_t *unicodeData();
    /// Const version of gString::unicodeData()
    const wchar_t *unicodeData() const;
    /*! \brief Concatenates a string to this object. Notice string format
               does not change. If the another string has a different,
               the objects transforms data and applies.
        \param other: String object to concatenate.
    */
    void concatenate(const gString &other);
    /*! \brief Concatenates a NULL terminated ASCII string to this object.
               If this object format is UNICODE, the another string gets transformed
               and concatenated.
        \param astr: NULL Terminated ASCII string to concatenate.
        \param nsize: Size of the null terminated string. If 0 then
                      internally would get string size.
    */
    void concatenate(const char *astr, gu32 nsize = 0);
    /*! \brief Concatenates a NULL terminated UNICODE string to this object.
               If this object format is ASCII, the another string gets transformed
               and concatenated.
        \param wstr: NULL Terminated UNICODE string to concatenate.
        \param nsize: Size of the null terminated string. If 0 then
                      internally would get string size.
    */
    void concatenate(const wchar_t *wstr, gu32 nsize = 0);
    /*! \brief Concatenates a std::string object to this object. If this object
               format is UNICODE then data from std::string gets transfomed and
               concatenated.
        \param stdstr: std:string to concatenate.
    */
    void concatenate(const string &stdstr);
    /*! \brief Concatenates a std::wstring object to this object. If this object
               format is ASCII then data from std::wstring gets transfomed and
               concatenated.
        \param wstr: std:wstring to concatenate.
    */
    void concatenate(const wstring &wstr);
    /*! \brief Compares this string with another and determines whether they are equal or not.
               Notice format has nothing to do. Internally data gets transformed
               if necessary.
        \param other: String object to compare to.
        \return true if they contain same string or else false.
    */
    bool isEqual(const gString &other) const;
    /*! \brief Compares this string with NULL terminated ASCII string
               and determines whether they are equal or not.
               Notice format has nothing to do. Internally data gets transformed
               if necessary.
        \param  astr: NULL terminated ASCII string to compare to.
        \return true if they contain same string or else false.
    */
    bool isEqual(const char *astr) const;
    /*! \brief Compares this string with NULL terminated UNICODE string
               and determines whether they are equal or not.
               Notice format has nothing to do. Internally data gets transformed
               if necessary.
        \param  astr: NULL terminated UNCODE string to compare to.
        \return true if they contain same string or else false.
    */
    bool isEqual(const wchar_t *wstr) const;
    /*! \brief Compares this string object with a std::string object and
               determines whether they are equal or not.
               Notice that format has nothing to do with this comparison.
               Comparison happens at a character level. If necessary, data
               gets transformed internally to perform comparison.
        \param stdstr: std::string to compare to.
        \return true if both string contains same character set or else false.
    */
    bool isEqual(const string &stdstr) const;
    /*! \brief Compares this string object with a std::wstring object and
               determines whether they are equal or not.
               Notice that format has nothing to do with this comparison.
               Comparison happens at a character level. If necessary, data
               gets transformed internally to perform comparison.
        \param wstr: std::wstring to compare to.
        \return true if both string contains same character set or else false.
    */
    bool isEqual(const wstring &wstr) const;
    gs32 compare(const char *str) const;
    gs32 compare(const wchar_t *str) const;
    gs32 compare(const gString &other) const;
    gs32 compare(const string &str) const;
    gs32 compare(const wstring &str) const;
    /// Transforms this string to unicode format
    void toUnicode();
    /// Transforms this string to ASCII format
    void toAscii();
    /// Compares two strings as much as gString::isEqual(gString)
    bool operator == (const gString &other) const;
    /// Compares two strings as much as gString::isEqual(const char *)
    bool operator == (const char *astr) const;
    /// Compares two strings as much as gString::isEqual(const wchar_t *)
    bool operator == (const wchar_t *wstr) const;
    /// Compares two strings as much as gString::isEqual(std::string)
    bool operator == (const string &stdstr) const;
    /// Compares two strings as much as gString::isEqual(std::wstring)
    bool operator == (const wstring &wstr) const;
    /// Compares two strings as mucha as gString::isEqual(gString) == false
    bool operator != (const gString &other) const;
    /// Compares two strings as mucha as gString::isEqual(const char *) == false
    bool operator != (const char *astr) const;
    /// Compares two strings as mucha as gString::isEqual(const wchar_t *) == false
    bool operator != (const wchar_t *wstr) const;
    /// Compares two strings as mucha as gString::isEqual(std::string) == false
    bool operator != (const string &stdstr) const;
    /// Compares two strings as mucha as gString::isEqual(std::wstring) == false
    bool operator != (const wstring &wstr) const;
    /// Concatenates to this object a string. See gString::concatenate(gString)
    gString &operator += (const gString &other);
    /// Concatenates to this object a string. See gString::concatenate(const char*)
    gString &operator += (const char *astr);
    /// Concatenates to this object a string. See gString::concatenate(const wchar_t *)
    gString &operator += (const wchar_t *wstr);
    /// Concatenates to this object a string. See gString::concatenate(std::string)
    gString &operator += (const string &stdstr);
    /// Concatenates to this object a string. See gString::concatenate(std::wstring)
    gString &operator += (const wstring &wstr);

    /*! \brief Concatenates this is string with another resuting a new string.
        \param other: String to concatenate.
        \return New string result of concatenation.
    */
    gString operator + (const gString &other) const;
    /*! \brief Concatenates this is string with NULL terminated
               ASCII string resulting new string.
        \param astr: String to concatenate.
        \return New string result of concatenation.
    */
    gString operator + (const char *astr) const;
    /*! \brief Concatenates this is string with NULL terminated
               UNICODE string resulting new string.
        \param wstr: String to concatenate.
        \return New string result of concatenation.
    */
    gString operator + (const wchar_t *wstr) const;
    /*! \brief Concatenates this is string with another resuting a new string.
        \param other: String to concatenate.
        \return New string result of concatenation.
    */
    gString operator + (const string &other) const;
    /*! \brief Concatenates this is string with another resuting a new string.
        \param other: String to concatenate.
        \return New string result of concatenation.
    */
    gString operator + (const wstring &other) const;
    /// Sets the string by another string \code string = anothestring \code
    gString &operator = (const gString &other);
     /// Sets the string by another string \code string = anothestring \code
    gString &operator = (const char *astr);
     /// Sets the string by another string \code string = anothestring \code
    gString &operator = (const wchar_t *wstr);
     /// Sets the string by another string \code string = anothestring \code
    gString &operator = (const string &stdstr);
     /// Sets the string by another string \code string = anothestring \code
    gString &operator = (const wstring &wstr);
    /// Transforms the characters of the string to upper case.
    void toUpperCase();
    /// Transforms the characters of the string to lower case.
    void toLowerCase();
    /*! \brief Gets a transformed version of the string upper cased.
        \return Upper cased string.
    */
    gString upperCase() const;
    /*! \brief Gets a transformed version of the string lower cased.
        \return Lower cased string.
    */
    gString lowerCase() const;
    /*! \brief Gets the hash value of the string.
        \return Integer hasg value.
    */
    gu32 hash() const;
    /*! \brief Gets the size of the string in character wide.
        \return Size of string.
    */
    gu32 size() const;
    /*! \brief Gets the size of the string in byte size.
        \return Byte size of string.
    */
    gu32 byteSize() const;
    /*! \brief Gets the format of the string.
        \return Either GSF_ASCII or GSF_UNICODE.
    */
    gs32 format() const;
    //Numbers
    /*! \brief Gets a numeric integer value from the string
               containing a numeric value.
        \param ok: Written ok internally if function string data
                   contains numeric data and could be transformed.
        \param base: The numeric base of the returning value.
        \return Value of numeric value by string.
    */
    gs32 toInt(bool *ok = 0, gs32 base = 10) const;
    /*! \brief Gets a numeric unsigned integer value from the string
               containing a numeric value.
        \param ok: Written ok internally if function string data
                   contains numeric data and could be transformed.
        \param base: The numeric base of the returning value.
        \return Value of numeric value by string.
    */
    gu32 toUInt(bool *ok = 0, gs32 base = 10) const;
    /*! \brief Gets a numeric float 32 value from the string
               containing a numeric value.
        \param ok: Written ok internally if function string data
                   contains numeric data and could be transformed.
        \return Value of numeric value by string.
    */
    gf32 toFloat(bool *ok = 0) const;
    /*! \brief Gets a numeric float 64 value from the string
               containing a numeric value.
        \param ok: Written ok internally if function string data
                   contains numeric data and could be transformed.
        \return Value of numeric value by string.
    */
    gf64 toFloat64(bool *ok = 0) const;
    /*! \brief Returns whether data contained by the string is numeric or not.
        \return true if data is numeric else false.
    */
    bool isNumeric() const;
    /*! \brief Writes this string as a integer numeric value given a value.
               Old data gets replaced.
        \param value: Value to write.
        \param mformat: Format of string either GSF_ASCII or GSF_UNICODE.
    */
    void toNumber(gs32 value, gs32 mformat);
    /*! \brief Writes this string as a unsigned integer numeric value given a value.
               Old data gets replaced.
        \param value: Value to write.
        \param mformat: Format of string either GSF_ASCII or GSF_UNICODE.
    */
    void toNumber(gu32 value, gs32 mformat);
    /*! \brief Writes this string as a float numeric value given a value.
               Old data gets replaced.
        \param value: Value to write.
        \param mformat: Format of string either GSF_ASCII or GSF_UNICODE.
        \param cformat: Numeric format.
        \param precision: Decimal precision.
    */
    void toNumber(gf64 value, gs32 mformat, char cformat = 'g', gs32 precision = 6);
    //Searching

    gs32 inString(const char *str, gu32 len = 0, gu32 startpos = 0) const;
    gs32 inString(const wchar_t *str, gu32 len = 0, gu32 startpos = 0) const;
    gs32 inString(const std::string &str, gu32 startpos = 0) const;
    gs32 inString(const std::wstring &str, gu32 startpos = 0) const;
    gs32 inString(const gString &str, gu32 startpos = 0) const;
    virtual bool isEmpty() const;
    //Static Members
    /*! \brief Writes a string as a integer numeric value given a value.
               Old data gets replaced.
        \param value: Value to write.
        \param mformat: Format of string either GSF_ASCII or GSF_UNICODE.
        \return New string.
    */
    static gString number(gs32 value, gs32 mformat);
    /*! \brief Writes a string as a unsigned integer numeric value given a value.
               Old data gets replaced.
        \param value: Value to write.
        \param mformat: Format of string either GSF_ASCII or GSF_UNICODE.
        \return New string.
    */
    static gString number(gu32 value, gs32 mformat);
    /*! \brief Writes a string as a float numeric value given a value.
               Old data gets replaced.
        \param value: Value to write.
        \param mformat: Format of string either GSF_ASCII or GSF_UNICODE.
        \param cformat: Float format.
        \param precision: Decimal precision.
        \return New string.
    */
    static gString number(gf64 value, gs32 mformat,char cfloatformat = 'g', gs32 precision = 6);
};
}

#endif // GSTRING_H
