
//*****************************************************************************
//
// Forwards
//
//*****************************************************************************

namespace String {
    enum class EEncoding;
}

namespace String {
    template <EEncoding E> struct CodeUnit;
}

class CStringBuilder;



//*****************************************************************************
//
// Encoding
//
//*****************************************************************************

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
    uint        bomBytes;

    static const Encoding Unknown;
};

Encoding GetEncoding (const byte data[]);

} // namespace String



//*****************************************************************************
//
// CodePoints
//
//*****************************************************************************

namespace String
{

struct CodePoint
{
public: // Construction

    inline CodePoint ();
    inline CodePoint (const CodePoint & rhs) = default;
    inline explicit CodePoint (uint32 code);

    inline explicit operator uint32 () const;

public: // Statics

    static const CodePoint Invalid;
    static const CodePoint Null;
    static const CodePoint Max;

private:

    SIMPLE_TYPE_DATA(uint32, m_code);
    SIMPLE_TYPE_EQUATABLE(CodePoint);
    SIMPLE_TYPE_EQUATABLE_TO(CodePoint, char);
    SIMPLE_TYPE_COMPARABLE(CodePoint);
    SIMPLE_TYPE_COMPARABLE_TO(CodePoint, char);

};

template <EEncoding E>
CodePoint Decode (const typename CodeUnit<E>::Type * data[]);

template <EEncoding E>
void Encode (CodePoint code, typename CodeUnit<E>::Type data[], uint len);

template <EEncoding E>
void Encode (CodePoint code, TArray<typename CodeUnit<E>::Type> * data);

} // namespace String



//*****************************************************************************
//
// CodeUnit
//
//*****************************************************************************

namespace String
{

template <EEncoding E>  struct CodeUnit                   { typedef void   Type; };
template <>             struct CodeUnit<EEncoding::Ascii> { typedef char   Type; };
template <>             struct CodeUnit<EEncoding::Utf8>  { typedef uint8  Type; };
template <>             struct CodeUnit<EEncoding::Utf16> { typedef wchar  Type; };
template <>             struct CodeUnit<EEncoding::Utf32> { typedef uint32 Type; };
template <>             struct CodeUnit<EEncoding::Ucs2>  { typedef uint16 Type; };
template <>             struct CodeUnit<EEncoding::Ucs4>  { typedef uint32 Type; };

} // namespace String



//*****************************************************************************
//
// EncodingType
//
//*****************************************************************************

namespace String
{

template <typename T> struct EncodingType         { static const EEncoding value = EEncoding::Unknown; };
template <>           struct EncodingType<char>   { static const EEncoding value = EEncoding::Ascii; };
template <>           struct EncodingType<byte>   { static const EEncoding value = EEncoding::Utf8; };
template <>           struct EncodingType<wchar>  { static const EEncoding value = EEncoding::Utf16; };
template <>           struct EncodingType<uint32> { static const EEncoding value = EEncoding::Utf32; };
template <>           struct EncodingType<uint16> { static const EEncoding value = EEncoding::Ucs2; };

} // namespace String



//*****************************************************************************
//
// TString
//
//*****************************************************************************

template <String::EEncoding E>
class TString
{
public:

    static const String::EEncoding ENCODING = E;
    typedef typename String::CodeUnit<E>::Type CodeUnit;
    class Iterator;

public:
    // Construction
    inline TString ();
    inline TString (const TString<E> & rhs);
    inline TString (TString<E> && rhs);
    inline TString (const char ascii[]);
    inline TString (const CStringBuilder & builder);
    inline ~TString ();
    // ... transcode
    template <String::EEncoding F>
    inline TString (const TString<F> & rhs);
    // ... transcode range
    template <String::EEncoding F>
    inline TString (const typename TString<F>::Iterator & begin, const typename TString<F>::Iterator & end);


    // Assignment
    // ... copy
    inline TString<E> & operator= (const TString<E> & rhs);
    // ... move
    inline TString<E> & operator= (TString<E> && rhs);
    // ... transcode
    template <String::EEncoding F>
    inline TString<E> & operator= (const TString<F> & rhs);


    // Data
    inline const CodeUnit * Ptr () const;
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

    bool StartsWith (const TString<E> & str) const;
    bool EndsWith (const TString<E> & str) const;

public:

    class Iterator : public std::iterator<std::forward_iterator_tag, String::CodePoint>
    {
        friend class TString<E>;
        typedef typename TString<E>::CodeUnit CodeUnit;
    public:
        Iterator () = default;
        Iterator (const Iterator &) = default;
        const Iterator & operator= (const Iterator & rhs) const;

        const String::CodePoint operator* () const;
        const Iterator & operator++ () const;
        const Iterator operator++ (int) const;

        bool operator== (const Iterator & rhs) const;
        bool operator!= (const Iterator & rhs) const;
        bool operator< (const Iterator & rhs) const;

        const CodeUnit * Ptr() const;

    private:
        Iterator (const CodeUnit * ptr);

        mutable const CodeUnit * m_curr;
    };

public:

    static const TString<E> Null;
    static const TString<E> Empty;
    static TString<E> FromData(const CodeUnit data[]);
    static TString<E> FromData(const TArray<CodeUnit> & data);
    static TString<E> FromData(const TArray<String::CodePoint> & data);

public:

    template <String::EEncoding F>
    friend bool operator== (const TString<F> & lhs, const TString<F> & rhs);
    template <String::EEncoding F>
    friend bool operator== (const TString<F> & lhs, const char rhs[]);
    template <String::EEncoding F>
    friend bool operator< (const TString<F> & lhs, const TString<F> & rhs);
    template <String::EEncoding F>
    friend TString<F> operator+ (const TString<F> & lhs, const TString<F> & rhs);

private:

    TArray<CodeUnit> m_data;
};

typedef TString<String::EEncoding::Ascii>   CStringAscii;
typedef TString<String::EEncoding::Utf8>    CStringUtf8;
typedef TString<String::EEncoding::Utf16>   CStringUtf16;
typedef TString<String::EEncoding::Utf32>   CStringUtf32;
typedef TString<String::EEncoding::Ucs2>    CStringUcs2;
typedef TString<String::EEncoding::Ucs4>    CStringUcs4;

typedef CStringUtf8 CString;



//*****************************************************************************
//
// CStringBuilder
//
//*****************************************************************************

class CStringBuilder
{
    template <String::EEncoding E>
    friend class TString;

public:

    void Clear ();

    CString GetString () const;
    
    template <String::EEncoding E>
    const CStringBuilder & operator+= (const TString<E> & str);
    const CStringBuilder & operator+= (String::CodePoint codepoint);
    const CStringBuilder & operator+= (char ch);

private:

    TQueue<String::CodePoint> m_data;
};



//*****************************************************************************
//
// Helpers
//
//*****************************************************************************

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

float32 StrDistance (const CString & lhs, const CString & rhs);


#include "String.inl"