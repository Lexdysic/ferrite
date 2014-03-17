
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
bool CharIsAlpha (String::CodePoint ch)
{
    return CharIsUpper(ch) || CharIsLower(ch);
}

//=============================================================================
bool CharIsNumeric (String::CodePoint ch)
{
    return L'0' <= ch && ch <= L'9';
}

//=============================================================================
bool CharIsControl (String::CodePoint ch)
{
    return ch < 32;
}

//=============================================================================
bool CharIsWhitespace (String::CodePoint ch)
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
const TString<E> TString<E>::Null("");

//=============================================================================
template <String::EEncoding E>
const TString<E> TString<E>::Empty(null);


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
    m_data(std::forward<TArray<TString<E>::Type>>(rhs.m_data))
{
}

//=============================================================================
template <String::EEncoding E>
TString<E>::TString (const char ascii[])
{
    //CStringAscii s = CStringAscii::FromData(ascii);
    //*this = s;

    const uint len = StrLen(ascii);
    m_data.Reserve(len + 1);
    while (String::CodePoint codepoint = String::Decode<String::EEncoding::Ascii>(&ascii))
    {
        String::Encode<E>(codepoint, &m_data);
    }
    m_data.Add(0);
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
template <String::EEncoding F>
TString<E>::TString (const typename TString<F>::Iterator & begin, const typename TString<F>::Iterator & end)
{
    // TODO: validate input

    while (begin < end)
        String::Encode<E>(*begin, &m_data);
    m_data.Add(0);
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
    m_data = std::forward<TArray<TString<E>::Type>>(rhs.m_data);
    return *this;
}


//=============================================================================
template <String::EEncoding E>
template <String::EEncoding F>
TString<E> & TString<E>::operator= (const TString<F> & rhs)
{
    m_data.Clear();

    const TString<F>::Iterator read = rhs.begin();
    while (String::CodePoint codepoint = *read++)
        String::Encode<E>(codepoint, &m_data);

    m_data.Add(0);
}

//=============================================================================
template <String::EEncoding E>
const typename TString<E>::Type * TString<E>::Ptr () const
{
    return m_data.Ptr();
}


//=============================================================================
template <String::EEncoding E>
const typename TString<E>::Iterator TString<E>::begin () const
{
    return TString<E>::Iterator(Ptr());
}

//=============================================================================
template <String::EEncoding E>
const typename TString<E>::Iterator TString<E>::end () const
{
    return TString<E>::Iterator(null);
}

//=============================================================================
template <String::EEncoding E>
uint TString<E>::Length () const
{
    uint len = 0;

    const Type * ptr = Ptr();
    while (String::Decode<E>(&ptr) != 0)
        len++;

    return len;
}

//=============================================================================
template <String::EEncoding E>
uint TString<E>::Bytes () const
{
    return sizeof(T) * m_data.Count();
}

//=============================================================================
template <String::EEncoding E>
TString<E> TString<E>::FromData(const Type data[])
{
    // TODO: check that the data is valid
    const Type * dataEnd = data;
    while (*dataEnd++ != 0);
    
    const uint len = dataEnd - data;

    TString<E> out;
    out.m_data.Add(data, len);
    return out;
}

//=============================================================================
template <String::EEncoding E>
TString<E> TString<E>::FromData(const TArray<Type> & data)
{
    // TODO: check that the data is valid
    TString<E> out;
    out.m_data = data;
    return out;
}

//=============================================================================
template <String::EEncoding E>
TString<E> TString<E>::FromData(const TArray<String::CodePoint> & data)
{
    TString<E> out;
    out.m_data.Reserve(data.Count()); // TODO: better way to estimate needed space by encoding

    for (auto codepoint : data)
        String::Encode<E>(codepoint, &out.m_data);

    return out;
}

//=============================================================================
template <String::EEncoding E>
bool operator== (const TString<E> & lhs, const TString<E> & rhs)
{
    return lhs.m_data == rhs.m_data;
}

//=============================================================================
template <String::EEncoding E>
bool operator== (const TString<E> & lhs, const char rhs[])
{
    return lhs == TString<E>(rhs);
}

//=============================================================================
template <String::EEncoding E>
bool operator< (const TString<E> & lhs, const TString<E> & rhs)
{
    return lhs.m_data < rhs.m_data;
}



//=============================================================================
//
// TString::Iterator
//
//=============================================================================

//=============================================================================
template <String::EEncoding E>
TString<E>::Iterator::Iterator (const Type * ptr) :
    m_curr(ptr)
{
}

//=============================================================================
template <String::EEncoding E>
const typename TString<E>::Iterator & TString<E>::Iterator::operator= (const Iterator & rhs) const
{
    m_curr = rhs.m_curr;
    return *this;
}

//=============================================================================
template <String::EEncoding E>
const String::CodePoint TString<E>::Iterator::operator* () const
{
    const TString<E>::Type * curr = m_curr;
    return String::Decode<E>(&curr);
}

//=============================================================================
template <String::EEncoding E>
const typename TString<E>::Iterator & TString<E>::Iterator::operator++ () const
{
    String::Decode<E>(&m_curr);
    return *this;
}

//=============================================================================
template <String::EEncoding E>
const typename TString<E>::Iterator TString<E>::Iterator::operator++ (int) const
{
    TString<E>::Iterator it = *this;
    String::Decode<E>(&m_curr);
    return it;
}

//=============================================================================
template <String::EEncoding E>
const typename TString<E>::Type * TString<E>::Iterator::Ptr() const
{
    return m_curr;
}