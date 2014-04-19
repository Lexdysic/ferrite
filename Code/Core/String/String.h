
//=============================================================================
//
// Forwards
//
//=============================================================================


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
// CodeUnit
//
//=============================================================================

namespace String {

template <EEncoding E>  struct CodeUnit                   { typedef void   Type; };
template <>             struct CodeUnit<EEncoding::Ascii> { typedef char   Type; };
template <>             struct CodeUnit<EEncoding::Utf8>  { typedef uint8  Type; };
template <>             struct CodeUnit<EEncoding::Utf16> { typedef wchar  Type; };
template <>             struct CodeUnit<EEncoding::Utf32> { typedef uint32 Type; };
template <>             struct CodeUnit<EEncoding::Ucs2>  { typedef wchar  Type; };
template <>             struct CodeUnit<EEncoding::Ucs4>  { typedef sint32 Type; };

} // namespace String


//=============================================================================
//
// EncodingType
//
//=============================================================================

namespace String {

template <typename T> struct EncodingType         { static const EEncoding value = EEncoding::Unknown; };
template <>           struct EncodingType<char>   { static const EEncoding value = EEncoding::Ascii; };
template <>           struct EncodingType<byte>   { static const EEncoding value = EEncoding::Utf8; };
template <>           struct EncodingType<wchar>  { static const EEncoding value = EEncoding::Utf16; };
template <>           struct EncodingType<uint32> { static const EEncoding value = EEncoding::Utf32; };
template <>           struct EncodingType<uint16> { static const EEncoding value = EEncoding::Ucs2; };

} // namespace String


//=============================================================================
//
// Helpers
//
//=============================================================================

inline bool CharIsUpper (String::CodePoint code);
inline bool CharIsLower (String::CodePoint code);

inline String::CodePoint CharToUpper (String::CodePoint code);
inline String::CodePoint CharToLower (String::CodePoint code);

inline bool CharIsAlpha (String::CodePoint ch);
inline bool CharIsNumeric (String::CodePoint ch);
inline bool CharIsControl (String::CodePoint ch);

inline bool CharIsWhitespace (String::CodePoint ch);

inline uint StrLen (const wchar text[]);
inline uint StrLen (const char text[]);

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
    class Iterator;

public:
    // Construction
    inline TString ();
    inline TString (const TString<E> & rhs);
    inline TString (TString<E> && rhs);
    inline TString (const char ascii[]);
    inline ~TString ();

    template <String::EEncoding F>
    inline TString (const TString<F> & rhs); // Transcode

    template <String::EEncoding F>
    inline TString (const typename TString<F>::Iterator & begin, const typename TString<F>::Iterator & end); // Transcode range

    // Assignment
    inline TString<E> & operator= (const TString<E> & rhs);
    inline TString<E> & operator= (TString<E> && rhs);

    template <String::EEncoding F>
    inline TString<E> & operator= (const TString<F> & rhs); // Transcode

    // Data
    inline const Type * Ptr () const;
    inline const Iterator begin () const;
    inline const Iterator end () const;

    // Queries
    uint Length () const;
    inline uint Bytes () const;
    inline uint Count () const; // CodeUnits

    bool IsNull () const;
    bool IsEmpty () const;
    bool IsNullOrEmpty () const;
    bool IsValid () const;

public:

    class Iterator
    {
        friend class TString<E>;
        typedef typename TString<E>::Type Type;
    public:
        Iterator () = default;
        Iterator (const Iterator &) = default;
        const Iterator & operator= (const Iterator & rhs) const;

        const String::CodePoint operator* () const;
        const Iterator & operator++ () const;
        const Iterator operator++ (int) const;

        const Type * Ptr() const;

    private:
        Iterator (const Type * ptr);

        mutable const Type * m_curr;
    };

public:

    static const TString<E> Null;
    static const TString<E> Empty;
    static TString<E> FromData(const Type data[]);
    static TString<E> FromData(const TArray<Type> & data);
    static TString<E> FromData(const TArray<String::CodePoint> & data);

public:

    template <String::EEncoding F>
    friend bool operator== (const TString<F> & lhs, const TString<F> & rhs);
    template <String::EEncoding F>
    friend bool operator== (const TString<F> & lhs, const char rhs[]);
    template <String::EEncoding F>
    friend bool operator< (const TString<F> & lhs, const TString<F> & rhs);

private:

    TArray<Type> m_data;
};


typedef TString<String::EEncoding::Ascii>   CStringAscii;
typedef TString<String::EEncoding::Utf8>    CStringUtf8;
typedef TString<String::EEncoding::Utf16>   CStringUtf16;
typedef TString<String::EEncoding::Utf32>   CStringUtf32;
typedef TString<String::EEncoding::Ucs2>    CStringUcs2;
//typedef TString<String::EEncoding::Ucs4>    CStringUsc4;
typedef CStringUtf8 CString;

#include "String.inl"