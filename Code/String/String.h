
//=============================================================================
//
// Forwards
//
//=============================================================================

class CString;


namespace String {
    enum class EEncoding;
}

namespace String {
    template <EEncoding E> struct CodeUnit;
} // namespace String



//=============================================================================
//
// Encoding
//
//=============================================================================

namespace String
{

enum class EEncoding
{
    Ascii,
    Utf8,
    Utf16,
    Utf32,
    Ucs2,
    Ucs4,
    Unknown
};


struct Encoding
{
    EEncoding   encoding;
    EEndian     endian;

    static const Encoding Unknown;
};

Encoding GetEncoding (const byte data[]);

} // namespace String


//=============================================================================
//
// CodePoints
//
//=============================================================================

namespace String
{

typedef uint32 CodePoint;

const CodePoint CODE_POINT_INVALID = (CodePoint)~0;

template <EEncoding E>
CodePoint Decode (const typename CodeUnit<E>::Type * data[]);

template <EEncoding E>
void Encode (CodePoint code, typename CodeUnit<E>::Type data[], uint len);

template <EEncoding E>
void Encode (CodePoint code, TArray<typename CodeUnit<E>::Type> * data);

} // namespace String



//=============================================================================
//
// Internal
//
//=============================================================================

namespace String {

template <EEncoding E>  struct CodeUnit                   { typedef void   Type; };
template <>             struct CodeUnit<EEncoding::Ascii> { typedef char   Type; };
template <>             struct CodeUnit<EEncoding::Utf8>  { typedef uint8  Type; };
template <>             struct CodeUnit<EEncoding::Utf16> { typedef uint16 Type; };
template <>             struct CodeUnit<EEncoding::Utf32> { typedef uint32 Type; };
template <>             struct CodeUnit<EEncoding::Ucs2>  { typedef wchar  Type; };
template <>             struct CodeUnit<EEncoding::Ucs4>  { typedef sint32 Type; };

} // namespace String



//=============================================================================
//
// Helpers
//
//=============================================================================

inline bool CharIsUpper (String::CodePoint code);
inline bool CharIsLower (String::CodePoint code);

inline wchar CharToUpper (String::CodePoint code);
inline wchar CharToLower (String::CodePoint code);

inline bool CharIsAlpha (wchar ch);
inline bool CharIsNumeric (wchar ch);
inline bool CharIsControl (wchar ch);

inline bool CharIsWhitespace (wchar ch);

inline uint StrLen (const wchar text[]);
inline uint StrLen (const char text[]);

inline uint StrBytes (const wchar text[]);
inline uint StrBytes (const char text[]);

inline const wchar * StrFind (const wchar text[], wchar ch);
inline const char *  StrFind (const char text[], char ch);

template <typename C, uint N>
inline int StrPrintf (C (& buffer)[N], const C format[], ...);
inline int StrPrintf (wchar buffer[], uint bufferCount, const wchar format[], ...);
inline int StrPrintf (char buffer[], uint bufferCount, const char format[], ...);

template <typename C, uint N>
inline int StrPrintfV (C (& buffer)[N], const C format[], va_list args);
inline int StrPrintfV (wchar buffer[], uint bufferCount, const wchar format[], va_list args);
inline int StrPrintfV (char buffer[], uint bufferCount, const char format[], va_list args);

bool StrConvertUtf16ToUtf8 (byte utf8[], uint utf8Bytes, const wchar utf16[], const uint utf16Count);



//=============================================================================
//
// TString
//
//=============================================================================

template <String::EEncoding E>
class TString
{
public:

    static const String::EEncoding ENCODING = E;
    typedef typename String::CodeUnit<E>::Type Type;

public:
    inline TString ();
    inline TString (const TString<E> & rhs);
    inline TString (TString<E> && rhs);
    template <typename C>
    inline TString (const C str[], String::EEncoding encoding);
    template <String::EEncoding F>
    inline TString (const TString<F> & rhs);
    inline ~TString ();

    inline TString<E> & operator= (const TString<E> & rhs);
    inline TString<E> & operator= (TString<E> && rhs);

    inline const Type * Ptr () const;

    uint Length () const;
    inline uint Bytes () const;

    inline void Clear ();
    inline void Reserve (uint count);
    inline void ReserveAdditional (uint additionalCount);

public:

    class Iterator
    {
    public:
        Iterator (Type * ptr);

        String::CodePoint operator* () const;
        const Iterator & operator++ ();

    private:
        Type * m_curr;
    };

public:

    static const TString<E> Null;
    static const TString<E> Empty;

private:

    TArray<Type> m_data;
};



//typedef TString<String::EEncoding::Ascii>   CStringAscii;
typedef TString<String::EEncoding::Utf8>    CStringUtf8;
typedef TString<String::EEncoding::Utf16>   CStringUtf16;
//typedef TString<String::EEncoding::Utf32>   CStringUtf32;
//typedef TString<String::EEncoding::Ucs2>    CStringUcs2;
//typedef TString<String::EEncoding::Ucs4>    CStringUsc4;
//typedef CStringUtf8 CString;


//=============================================================================
//
// CString
//
//=============================================================================

class CString
{
public:
    inline CString ();
    inline CString (const CString & rhs);
    inline CString (CString && rhs);
    inline CString (const wchar str[]);
    inline ~CString ();

    inline CString & operator= (const CString & rhs);
    inline CString & operator= (CString && rhs);

    inline wchar & operator[] (uint index);
    inline wchar operator[] (uint index) const;
    
    inline const wchar * Ptr () const;

    inline uint Length () const;
    inline uint Bytes () const;

    inline void Clear ();
    inline void Reserve (uint count);
    inline void ReserveAdditional (uint additionalCount);

    inline void operator+= (const CString & rhs);
    inline void operator+= (wchar ch);

public:

    static CString Null;
    static CString Empty;

public:

    friend bool operator== (const CString & lhs, const CString & rhs);
    friend bool operator< (const CString & lhs, const CString & rhs);

private:

    std::wstring m_data;
};

inline bool operator== (const CString & lhs, const CString & rhs);
inline bool operator< (const CString & lhs, const CString & rhs);

#include "String.inl"