
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
String::CodePoint CharToUpper (String::CodePoint code)
{
    return CharIsLower(code) ? String::CodePoint(uint32(code) + ('A' - 'a')) : code; // TODO: others
}

//=============================================================================
String::CodePoint CharToLower (String::CodePoint code)
{
    return CharIsUpper(code) ? String::CodePoint(uint32(code) + ('a' - 'A')) : code; // TODO: others
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
    if (StrFind(L" \r\u00a0\u1680", uint32(ch)) != null)
        return true;

    // explicit width space (em-space, en-space, etc...)
    if (String::CodePoint(0x2000) <= ch && ch <= String::CodePoint(0x200a))
        return true;

    // line separator, para separator, narrow nbsp, math space, ideographic space
    if (StrFind(L"\u2028\u2029\u202f\u205f\u3000", uint32(ch)) != null)
        return true;

    return false;
}

//=============================================================================
uint StrLen (const wchar text[])
{
    return uint(wcslen(text));
}

//=============================================================================
uint StrLen (const char text[])
{
    return uint(strlen(text));
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




//*****************************************************************************
//
// CodePoint
//
//*****************************************************************************

namespace String
{
////=============================================================================
//CodePoint::CodePoint () :
//    m_code(Invalid)
//{
//}
//
////=============================================================================
//CodePoint::CodePoint (uint32 code) :
//    m_code(code)
//{
//}
//
////=============================================================================
//CodePoint::operator uint32 () const
//{
//    return m_code;
//}

} // namespace String



//*****************************************************************************
//
// TString
//
//*****************************************************************************

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
    m_data(std::forward<TArray<TString<E>::CodeUnit>>(rhs.m_data))
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
    *this = rhs;
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
inline TString<E>::TString (const CStringBuilder & builder)
{
    for (auto codepoint : builder.m_data)
        String::Encode<E>(codepoint, &m_data);
        //m_data.Add(codepoint);
    

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
    m_data = rhs.m_data;
    return *this;
}

//=============================================================================
template <String::EEncoding E>
TString<E> & TString<E>::operator= (TString<E> && rhs)
{
    m_data = std::forward<TArray<TString<E>::CodeUnit>>(rhs.m_data);
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

    return *this;
}

//=============================================================================
template <String::EEncoding E>
const typename TString<E>::CodeUnit * TString<E>::Ptr () const
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
    if (IsNull())
        return TString<E>::Iterator(null);
    return TString<E>::Iterator(m_data.Ptr() + m_data.Count() - 1);
}

//=============================================================================
template <String::EEncoding E>
uint TString<E>::Length () const
{
    uint len = 0;

    const CodeUnit * ptr = Ptr();
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
uint TString<E>::Count () const
{
    return m_data.Count();
}

//=============================================================================
template <String::EEncoding E>
bool TString<E>::IsNull () const
{
    return m_data.Count() == 0;
}

//=============================================================================
template <String::EEncoding E>
bool TString<E>::IsEmpty () const
{
    return m_data.Count() && m_data[0] == 0;
}

//=============================================================================
template <String::EEncoding E>
bool TString<E>::IsNullOrEmpty () const
{
    return m_data.Count() == 0 || m_data[0] == 0;
}

//=============================================================================
template <String::EEncoding E>
bool TString<E>::IsValid () const
{
    return !IsNullOrEmpty();
}

//=============================================================================
template <String::EEncoding E>
bool TString<E>::StartsWith (const TString<E> & str) const
{
    if (this->IsNullOrEmpty())
        return false;
    if (str.IsNullOrEmpty())
        return false;
    if (str.Count() > this->Count())
        return false;

    auto lhs = this->begin();
    auto lhsEnd = this->end();

    auto rhs = str.begin();
    auto rhsEnd = this->end();

    while (lhs != lhsEnd && rhs != rhsEnd)
    {
        if (*lhs != *rhs)
            return false;

        ++lhs;
        ++rhs;
    }

    return true;
}

//=============================================================================
template <String::EEncoding E>
bool TString<E>::EndsWith (const TString<E> & str) const
{
    if (this->IsNullOrEmpty())
        return false;
    if (str.IsNullOrEmpty())
        return false;
    if (str.Count() > this->Count())
        return false;

    auto lhs = this->begin();
    auto lhsEnd = this->end();

    for (uint i = 0, n = this->Count() - str.Count(); i < n; ++i)
        ++lhs;

    auto rhs = str.begin();
    auto rhsEnd = this->end();

    while (lhs != lhsEnd && rhs != rhsEnd)
    {
        if (*lhs != *rhs)
            return false;

        ++lhs;
        ++rhs;
    }

    return true;
}

//=============================================================================
template <String::EEncoding E>
TString<E> TString<E>::FromData(const CodeUnit data[])
{
    if (!data)
        return TString<E>::Null;

    // TODO: check that the data is valid
    const CodeUnit * dataEnd = data;
    while (*dataEnd++ != 0);
    
    const uint len = uint(dataEnd - data);

    TString<E> out;
    out.m_data.Add(data, len);
    return out;
}

//=============================================================================
template <String::EEncoding E>
TString<E> TString<E>::FromData(const TArray<CodeUnit> & data)
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
template <String::EEncoding F>
TString<F> operator+ (const TString<F> & lhs, const TString<F> & rhs)
{
    TArray<typename TString<F>::CodeUnit> data;

    data.Add(lhs.m_data);
    data.RemoveOrdered(data.Count() - 1);
    data.Add(rhs.m_data);
    data.Add(0);

    return TString<F>::FromData(std::move(data));
}



//*****************************************************************************
//
// TString::Iterator
//
//*****************************************************************************

//=============================================================================
template <String::EEncoding E>
TString<E>::Iterator::Iterator (const CodeUnit * ptr) :
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
    const TString<E>::CodeUnit * curr = m_curr;
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
bool TString<E>::Iterator::operator== (const Iterator & rhs) const
{
    return this->m_curr == rhs.m_curr;
}

//=============================================================================
template <String::EEncoding E>
bool TString<E>::Iterator::operator!= (const Iterator & rhs) const
{
    return !(*this == rhs);
}

//=============================================================================
template <String::EEncoding E>
bool TString<E>::Iterator::operator< (const Iterator & rhs) const
{
    return this->m_curr < rhs.m_curr;
}

//=============================================================================
template <String::EEncoding E>
const typename TString<E>::CodeUnit * TString<E>::Iterator::Ptr() const
{
    return m_curr;
}



//*****************************************************************************
//
// CStringBuilder
//
//*****************************************************************************

//=============================================================================
template <String::EEncoding E>
const CStringBuilder & CStringBuilder::operator+= (const TString<E> & str)
{
    for (auto codepoint : str)
        m_data.AddBack(codepoint);

    return *this;
}
