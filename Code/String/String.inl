
#include <cstdarg>

//=============================================================================
bool CharIsUpper (String::CodePoint code)
{
    return 'A' <= code && code <= 'Z'; // TODO: other tests for accented characters
}

//=============================================================================
bool CharIsLower (String::CodePoint code)
{
    return 'a' <= code && code <= 'z'; // TODO: other tests for accented characters
}

//=============================================================================
wchar CharToUpper (String::CodePoint code)
{
    return CharIsLower(code) ? (code + ('A' - 'a')) : code; // TODO: others
}

//=============================================================================
wchar CharToLower (String::CodePoint code)
{
    return CharIsUpper(code) ? (code + ('a' - 'A')) : code; // TODO: others
}

//=============================================================================
bool CharIsAlpha (wchar ch)
{
    return CharIsUpper(ch) || CharIsLower(ch);
}

//=============================================================================
bool CharIsNumeric (wchar ch)
{
    return L'0' <= ch && ch <= L'9';
}

//=============================================================================
bool CharIsControl (wchar ch)
{
    return ch < 32;
}

//=============================================================================
bool CharIsWhitespace (wchar ch)
{
    // control
    if (0x09 <= ch && ch <= 0x0d)
        return true;

    // space, carriage return, nbsp, Ogham space
    if (StrFind(L" \r\u00a0\u1680", ch) != null)
        return true;

    // explicit width space (em-space, en-space, etc...)
    if (0x2000 <= ch && ch <= 0x200a)
        return true;

    // line separator, para separator, narrow nbsp, math space, ideographic space
    if (StrFind(L"\u2028\u2029\u202f\u205f\u3000", ch) != null)
        return true;

    return false;
}

//=============================================================================
uint StrLen (const wchar text[])
{
    return wcslen(text);
}

//=============================================================================
uint StrLen (const char text[])
{
    return strlen(text);
}

//=============================================================================
uint StrBytes (const wchar text[])
{
    return StrLen(text) * sizeof(wchar);
}

//=============================================================================
uint StrBytes (const char text[])
{
    return StrLen(text) * sizeof(char);
}

//=============================================================================
const wchar * StrFind (const wchar text[], wchar ch)
{
    while (*text != L'\0' && *text != ch)
        text++;

    if (*text == ch)
        return text;
    else
        return null;
}

//=============================================================================
const char * StrFind (const char text[], char ch)
{
    while (*text != L'\0' && *text != ch)
        text++;

    if (*text == ch)
        return text;
    else
        return null;
}

//=============================================================================
template <typename C, uint N>
int StrPrintf (C (& buffer)[N], const C format[], ...)
{
    va_list args;
    va_start(args, format);
    const uint ret = StrPrintfV(buffer, N, format, args);
    va_end(args);
    return ret;
}

//=============================================================================
int StrPrintf (wchar buffer[], uint bufferCount, const wchar format[], ...)
{
    va_list args;
    va_start(args, format);
    const uint ret = StrPrintfV(buffer, bufferCount, format, args);
    va_end(args);
    return ret;
}

//=============================================================================
int StrPrintf (char buffer[], uint bufferCount, const char format[], ...)
{
    va_list args;
    va_start(args, format);
    const uint ret = StrPrintfV(buffer, bufferCount, format, args);
    va_end(args);
    return ret;
}

//=============================================================================
template <typename C, uint N>
int StrPrintfV (C (& buffer)[N], const C format[], va_list args)
{
    return StrPrintfV(buffer, N, format, args);
}

//=============================================================================
int StrPrintfV (wchar buffer[], uint bufferCount, const wchar format[], va_list args)
{
    const int len = vswprintf_s(buffer, bufferCount-1, format, args);
    buffer[len] = '\0';
    return len;
}

//=============================================================================
int StrPrintfV (char buffer[], uint bufferCount, const char format[], va_list args)
{
    const int len = vsprintf_s(buffer, bufferCount-1, format, args);
    buffer[len] = '\0';
    return len;
}




//=============================================================================
//
// TString
//
//=============================================================================

//=============================================================================
template <String::EEncoding E>
const TString<E> TString<E>::Null("", E);

//=============================================================================
template <String::EEncoding E>
const TString<E> TString<E>::Empty(null, E);


//=============================================================================
template <String::EEncoding E>
TString<E>::TString ()
{
}

//=============================================================================
template <String::EEncoding E>
TString<E>::TString (const TString<E> & rhs) :
    m_data(rhs.m_data)
{
}

//=============================================================================
template <String::EEncoding E>
TString<E>::TString (TString<E> && rhs) :
    m_data(std::forward(rhs.m_data))
{
}

//=============================================================================
template <String::EEncoding E>
template <typename C>
TString<E>::TString (const C str[], String::EEncoding encoding)
{
    m_data.Clear();

    if (str)
    {
        while (CodePoint codepoint = Decode<encoding>(str))
        {
            Encode<E>(codepoint);
            m_data.Add(codepoint);
        }
        m_data.Add(0);
    }
}

//=============================================================================
template <String::EEncoding E>
template <String::EEncoding F>
TString<E>::TString (const TString<F> & rhs)
{
    m_data.Clear();
    ASSERT(false); // TODO: transcode
}

//=============================================================================
template <String::EEncoding E>
TString<E>::~TString ()
{
}

//=============================================================================
template <String::EEncoding E>
TString<E> & TString<E>::operator= (const TString<E> & rhs)
{
    m_data = rhs;
    return *this;
}

//=============================================================================
template <String::EEncoding E>
TString<E> & TString<E>::operator= (TString<E> && rhs)
{
    m_data = std::forward(rhs.m_data);
}

//=============================================================================
template <String::EEncoding E>
const typename TString<E>::Type * TString<E>::Ptr () const
{
    return m_data.Ptr();
}

//=============================================================================
template <String::EEncoding E>
uint TString<E>::Length () const
{
}

//=============================================================================
template <String::EEncoding E>
uint TString<E>::Bytes () const
{
    return sizeof(T) * m_data.Count();
}

//=============================================================================
template <String::EEncoding E>
void TString<E>::Clear ()
{
    m_data.Clear();
}



//=============================================================================
//
// TString::Iterator
//
//=============================================================================

template <String::EEncoding E>
TString<E>::Iterator::Iterator (Type * ptr) :
    m_curr(ptr)
{
}

template <String::EEncoding E>
String::CodePoint TString<E>::Iterator::operator* () const
{
    T * curr = m_curr;
    return String::Decode<T, E>(&curr);
}

template <String::EEncoding E>
const typename TString<E>::Iterator & TString<E>::Iterator::operator++ ()
{
    String::Decode(&m_curr);
    return *this;
}














//=============================================================================
//
// CString
//
//=============================================================================

//=============================================================================
CString::CString () :
    m_data()
{
}

//=============================================================================
CString::CString (const CString & rhs) :
    m_data(rhs.m_data)
{
}

//=============================================================================
CString::CString (CString && rhs) :
    m_data(rhs.m_data)
{
}

//=============================================================================
CString::CString (const wchar str[]) :
    m_data(str)
{
}

//=============================================================================
CString::~CString ()
{
}

//=============================================================================
CString & CString::operator= (const CString & rhs)
{
    m_data = rhs.m_data;
    return *this;
}

//=============================================================================
CString & CString::operator= (CString && rhs)
{
    m_data = rhs.m_data;
    return *this;
}

//=============================================================================
wchar & CString::operator[] (uint index)
{
    return m_data[index];
}

//=============================================================================
wchar CString::operator[] (uint index) const
{
    return m_data[index];
}

//=============================================================================
const wchar * CString::Ptr () const
{
    return m_data.c_str();
}

//=============================================================================
uint CString::Length () const
{
    return m_data.length();
}

//=============================================================================
uint CString::Bytes () const
{
    return sizeof(wchar) * (Length() + 1);
}

//=============================================================================
void CString::Clear ()
{
    m_data.clear();
}

//=============================================================================
void CString::Reserve (uint count)
{
    m_data.reserve(count);
}

//=============================================================================
void CString::ReserveAdditional (uint additionalCount)
{
    m_data.reserve(Length() + additionalCount);
}

//=============================================================================
void CString::operator+= (const CString & rhs)
{
    m_data += rhs.m_data;
}

//=============================================================================
void CString::operator+= (wchar ch)
{
    m_data += ch;
}

//=============================================================================
bool operator== (const CString & lhs, const CString & rhs)
{
    return lhs.m_data == rhs.m_data;
}

//=============================================================================
bool operator< (const CString & lhs, const CString & rhs)
{
    return lhs.m_data < rhs.m_data;
}