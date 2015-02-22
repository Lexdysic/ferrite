#include "Ferrite.h"


//*****************************************************************************
//
// Constants
//
//*****************************************************************************

const uint16 UTF16_LEAD_MIN  = 0xd800;
const uint16 UTF16_LEAD_MAX  = 0xdbff;
const uint16 UTF16_TAIL_MIN  = 0xdc00;
const uint16 UTF16_TAIL_MAX  = 0xdfff;

const uint32 UTF16_LEAD_OFFSET      = UTF16_LEAD_MIN - (0x10000 >> 10);
const uint32 UTF16_SURROGATE_OFFSET = 0x10000 - (UTF16_LEAD_MIN << 10) - UTF16_TAIL_MIN;

const byte B10000000 = 0x80;
const byte B11000000 = 0xc0;
const byte B11100000 = 0xe0;
const byte B11110000 = 0xf0;
const byte B11111000 = 0xf8;
const byte B11111100 = 0xfc;
const byte B11111110 = 0xfe;



//*****************************************************************************
//
// Helpers
//
//*****************************************************************************

//=============================================================================
static bool NeedsUtf16Surrogate(String::CodePoint codepoint)
{
    return codepoint > String::CodePoint(0xffff);
}

//=============================================================================
static bool IsUtf16LeadSurrogate (uint16 codeunit)
{
    return Math::IsInRange(codeunit, UTF16_LEAD_MIN, UTF16_LEAD_MAX);
}

//=============================================================================
static bool IsUtf16TailSurrogate (uint16 codeunit)
{
    return Math::IsInRange(codeunit, UTF16_TAIL_MIN, UTF16_TAIL_MAX);
}

//=============================================================================
static bool IsValidCodePoint (String::CodePoint codepoint)
{
    const String::CodePoint CODE_POINT_MAX(0x10fff);
    return Math::IsInRange(uint32(codepoint), uint32(0), uint32(CODE_POINT_MAX));
}



//*****************************************************************************
//
// Encoding
//
//*****************************************************************************

namespace String
{

//=============================================================================
const Encoding Encoding::Unknown = { String::EEncoding::Unknown, EEndian::Unknown, 0 };

//=============================================================================
Encoding GetEncoding (const byte data[])
{
    struct Bom
    {
        Encoding encoding;
        byte bom[4];
    };

    static const Bom s_boms[] = 
    {
        { { EEncoding::Utf8,  EEndian::Unknown, 3 }, { 0xef, 0xbb, 0xbf } },
        { { EEncoding::Utf16, EEndian::Little,  2 }, { 0xff, 0xfe } },
        { { EEncoding::Utf16, EEndian::Big,     2 }, { 0xfe, 0xff } },
        { { EEncoding::Utf32, EEndian::Little,  4 }, { 0xff, 0xfe, 0x00, 0x00 } },
        { { EEncoding::Utf32, EEndian::Big,     4 }, { 0x00, 0x00, 0xfe, 0xff } },
    };

    for (const auto & bom : s_boms)
    {
        if (!MemEqual(data, bom.bom, bom.encoding.bomBytes))
            continue;

        return bom.encoding;
    }

    return Encoding::Unknown;
}

} // namespace String



//*****************************************************************************
//
// CodePoints
//
//*****************************************************************************

namespace String
{

//=============================================================================
const CodePoint CodePoint::Invalid(0xffffffff);
const CodePoint CodePoint::Null(0x0);
const CodePoint CodePoint::Max(0x10ffff);

//=============================================================================
template <>
CodePoint Decode<String::EEncoding::Ascii> (const char * data[])
{
    ASSERT(((**data) & 0x80) == 0);
    return CodePoint(*(*data)++);
}

//=============================================================================
template <>
CodePoint Decode<String::EEncoding::Utf8> (const byte * data[])
{
    uint32 code;
    
    uint len = 0;
    const byte lead = *(*data)++;
    if ((lead & B10000000) == 0)
    {
        len = 1;
        code = lead & ~B10000000;
    }
    else if ((lead & B11100000) == B11000000)
    {
        len = 2;
        code = lead & ~B11100000;
    }
    else if ((lead & B11110000) == B11100000)
    {
        len = 3;
        code = lead & ~B11110000;
    }
    else if ((lead & B11111000) == B11110000)
    {
        len = 4;
        code = lead & ~B11111000;
    }
    else if ((lead & B11111100) == B11111000)
    {
        len = 5;
        code = lead & ~B11111100;
    }
    else if ((lead & B11111110) == B11111100)
    {
        len = 6;
        code = lead & ~B11111110;
    }
    else
    {
        return CodePoint::Invalid;
    }

    for (uint i = 1; i < len; ++i)
    {
        const byte value = *(*data)++;
        if ((value & B11000000) != B10000000)
            return CodePoint::Invalid;
        code = (code << 6) | (value & ~B11000000);
    }

    return String::CodePoint(code);
}

//=============================================================================
template <>
CodePoint Decode<String::EEncoding::Utf16> (const wchar * data[])
{
    const uint16 lead = *(*data)++;

    if (!IsUtf16LeadSurrogate(lead))
        return CodePoint(lead);

    const uint16 tail = *(*data)++;

    if (!IsUtf16TailSurrogate(tail))
        return CodePoint::Invalid;

    const uint32 x = (lead & ((1 << 6) - 1)) << 10 | tail & ((1 << 10) - 1);
    const uint32 w = ((tail >> 6) & ((1 << 5) - 1)) + 1;

    return CodePoint(w << 16 | x);
}

//=============================================================================
template <>
void Encode<EEncoding::Ascii> (CodePoint code, TArray<CodeUnit<EEncoding::Ascii>::Type> * data)
{
    ASSERT(IsValidCodePoint(code));

    if (code < CodePoint(0x80))
    {
        data->Add(char(uint32(code)));
    }
    else
    {
        FATAL_EXIT("Encountered code unit that is out of range for ascii encoding.");
    }
}

//=============================================================================
template <>
void Encode<EEncoding::Utf8> (CodePoint codepoint, TArray<byte> * data)
{
    ASSERT(IsValidCodePoint(codepoint));

    const uint32 code = uint32(codepoint);

    if (code < 0x80)
    {
        data->Add((byte)code);
    }
    else if (code < 0x800)
    {
        data->Add((code >> 6) | B11000000);
        data->Add((code & ~B11000000) | B10000000);
    }
    else if (code < 0x10000)
    {
        data->Add((code >> 12) | B11100000);
        data->Add(((code >> 6) & ~B11000000) | B10000000);
        data->Add((code & ~B11000000) | B10000000);
    }
    else if (code <= 0x10ffff)
    {
        data->Add((code >> 18) | 0xf0);
        data->Add(((code >> 12) & 0x3f) | 0x80);
        data->Add(((code >> 6) & 0x3f) | 0x80);
        data->Add((code & 0x3f) | 0x80);
    }
    else
    {
        FATAL_EXIT("Encountered code unit that is out of range for utf8 encoding.");
    }
}

//=============================================================================
template <>
void Encode<EEncoding::Utf16> (CodePoint codepoint, TArray<wchar> * data)
{
    ASSERT(IsValidCodePoint(codepoint));

    if (NeedsUtf16Surrogate(codepoint))
    {
        const uint32 code  = uint32(codepoint);
        const uint16 lead  = (code >> 10) + 0xd7c0;
        const uint16 trail = (code & 0x3ff) | UTF16_TAIL_MIN;
        data->Add(lead);
        data->Add(trail);
    }
    else
    {
        data->Add(uint16(uint32(codepoint)));
    }
}

} // namespace String



//*****************************************************************************
//
// CStringBuilder
//
//*****************************************************************************

//=============================================================================
void CStringBuilder::Clear ()
{
    m_data.Clear();
}

//=============================================================================
CString CStringBuilder::GetString () const
{
    return CString(*this);
}

//=============================================================================
const CStringBuilder & CStringBuilder::operator+= (String::CodePoint codepoint)
{
    m_data.AddBack(codepoint);

    return *this;
}

//=============================================================================
const CStringBuilder & CStringBuilder::operator+= (char ch)
{
    return *this += String::CodePoint(ch);
}



//*****************************************************************************
//
// Functions
//
//*****************************************************************************

//=============================================================================
float32 StrDistance (const CString & lhs, const CString & rhs)
{
    using namespace String;

    // TODO: test strings are equal?

    if (lhs.Count() == 0)
        return 0;
    if (rhs.Count() == 0)
        return 0;

    // Create distance data enough for a row of the matrix
    const uint lhsLen = lhs.Length();
    const uint rhsLen = rhs.Length();

    // Create two rows of the matrix
    TArray<uint> row0;
    TArray<uint> row1;
    row0.Resize(rhsLen + 1);
    row1.Resize(rhsLen + 1);

    // Initialize the previous row distance
    for (uint i = 0; i < row0.Count(); ++i)
        row0[i] = i;

    // Keep track of current and previous with pointers so we can avoid copies 
    TArray<uint> * prevPtr = &row0;
    TArray<uint> * currPtr = &row1;

    CodePoint lhsCurr;
    CodePoint lhsLast = CodePoint::Invalid;
    CString::Iterator lhsIt = lhs.begin();
    for (uint i = 0; i < lhsLen; lhsLast = lhsCurr, ++i, ++lhsIt, std::swap(prevPtr, currPtr))
    {
        // Make the code more readable using references
        TArray<uint> & prev = *prevPtr;
        TArray<uint> & curr = *currPtr;

        lhsCurr = *lhsIt;

        // Fill the current row
        curr[0] = i + 1;

        CodePoint rhsCurr;
        CodePoint rhsLast = CodePoint::Invalid;
        CString::Iterator rhsIt = rhs.begin();
        for (uint j = 0; j < rhsLen; rhsLast = rhsCurr, ++j, ++rhsIt)
        {
            rhsCurr = *rhsIt;

            const uint cost = (lhsCurr == rhsCurr) ? 0 : 1;

            // TODO: may want to take into account transpositions

            curr[j + 1] = Min(
                curr[j] + 1,        // deletion
                prev[j + 1] + 1,    // insersion
                prev[j] + cost      // substitution
            );
        }       
    }

    // Since we did one last swap before ending the loop, undo that here
    currPtr = prevPtr;

    const uint totalDist = (*currPtr)[rhsLen];
    const uint compareLen = Max(lhsLen, rhsLen);
    return totalDist / (float32)compareLen;
}