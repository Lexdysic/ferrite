#include "EngineDeps.h"
#include <Windows.h>

//=============================================================================
//
// Constants
//
//=============================================================================

const uint16            UTF16_LEAD_MIN  = 0xd800;
const uint16            UTF16_LEAD_MAX  = 0xdbff;
const uint16            UTF16_TAIL_MIN  = 0xdc00;
const uint16            UTF16_TAIL_MAX  = 0xdfff;
const String::CodePoint UTF16_RANGE_MIN = 0x0000;
const String::CodePoint UTF16_RANGE_MAX = 0x10ffff;

const uint32 UTF16_LEAD_OFFSET      = UTF16_LEAD_MIN - (0x10000 >> 10);
const uint32 UTF16_SURROGATE_OFFSET = 0x10000 - (UTF16_LEAD_MIN << 10) - UTF16_TAIL_MIN;

const byte B10000000 = 0x80;
const byte B11000000 = 0xc0;
const byte B11100000 = 0xe0;
const byte B11110000 = 0xf0;
const byte B11111000 = 0xf8;
const byte B11111100 = 0xfc;
const byte B11111110 = 0xfe;

const String::CodePoint CODE_POINT_MAX = 0x10ffff;


//=============================================================================
//
// Helpers
//
//=============================================================================

static bool NeedsUtf16Surrogate(String::CodePoint codepoint)
{
    return codepoint > 0xffff;
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
    return Math::IsInRange(codepoint, (String::CodePoint)0, CODE_POINT_MAX);
}


//=============================================================================
//
// Encoding
//
//=============================================================================

namespace String
{

const Encoding Encoding::Unknown = { String::EEncoding::Unknown, EEndian::Unknown };

//=============================================================================
Encoding GetEncoding (const byte data[])
{
    struct Bom
    {
        Encoding encoding;
        uint bytes;
        byte bom[4];
    };

    static const Bom s_boms[] = 
    {
        { { EEncoding::Utf8,  EEndian::Unknown }, 3, { 0xff, 0xbb, 0xbf } },
        { { EEncoding::Utf16, EEndian::Little },  2, { 0xff, 0xfe } },
        { { EEncoding::Utf16, EEndian::Big },     2, { 0xfe, 0xff } },
        { { EEncoding::Utf32, EEndian::Little },  4, { 0xff, 0xfe, 0x00, 0x00 } },
        { { EEncoding::Utf32, EEndian::Big },     4, { 0x00, 0x00, 0xfe, 0xff } },
    };

    for (const auto & bom : s_boms)
    {
        if (!MemEqual(data, bom.bom, bom.bytes))
            continue;

        return bom.encoding;
    }

    return Encoding::Unknown;
}

} // namespace String



//=============================================================================
//
// CodePoints
//
//=============================================================================

namespace String
{

//=============================================================================
template <>
CodePoint Decode<String::EEncoding::Ascii> (const char * data[])
{
    ASSERT(((**data) & 0x80) == 0);
    return *(*data)++;
}

//=============================================================================
template <>
CodePoint Decode<String::EEncoding::Utf8> (const byte * data[])
{
    CodePoint code;
    
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
        return CODE_POINT_INVALID;
    }

    for (uint i = 1; i < len; ++i)
    {
        const byte value = *(*data)++;
        if ((value & B11000000) != B10000000)
            return CODE_POINT_INVALID;
        code = (code << 6) | (value & ~B11000000);
    }

    return code;
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
        return CODE_POINT_INVALID;

    const uint32 x = (lead & ((1 << 6) - 1)) << 10 | tail & ((1 << 10) - 1);
    const uint32 w = ((tail >> 6) & ((1 << 5) - 1)) + 1;

    return CodePoint(w << 16 | x);
}

//=============================================================================
template <>
void Encode<EEncoding::Utf8> (CodePoint code, TArray<byte> * data)
{
    ASSERT(IsValidCodePoint(code));

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
        ASSERT(false); // ERROR: out of range
    }
}

//=============================================================================
template <>
void Encode<EEncoding::Utf16> (CodePoint c, TArray<wchar> * data)
{
    ASSERT(IsValidCodePoint(c));

    if (NeedsUtf16Surrogate(c))
    {
        const uint16 lead = (c >> 10) + 0xd7c0;
        const uint16 trail = (c & 0x3ff) | UTF16_TAIL_MIN;
        data->Add(lead);
        data->Add(trail);
    }
    else
    {
        data->Add(uint16(c));
    }
}

} // namespace String



//=============================================================================
CString CStringBuilder::GetString () const
{
    return CString(*this);
}

//=============================================================================
template <String::EEncoding E>
const CStringBuilder & CStringBuilder::operator+= (const TString<E> & str)
{
    for (auto codepoint : str)
        m_data.AddBack(*codepoint);

    return *this;
}

//=============================================================================
const CStringBuilder & CStringBuilder::operator+= (String::CodePoint codepoint)
{
    m_data.AddBack(codepoint);

    return *this;
}
