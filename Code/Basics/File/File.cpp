#define USES_ENGINE_FILE


#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <Windows.h>

#include "EngineDeps.h"

namespace File
{



//=============================================================================
//
// CFile
//
//=============================================================================
    
//=============================================================================
Internal::CFile::CFile (const CPath & filepath, EType type, EMode mode) :
    m_file(null)
{
    // Get the mode specifier
#define INDEX(t, m) (int(t) + int(m) * 2)
    const char * options = null;
    switch (INDEX(type, mode))
    {
        case INDEX(EType::Binary, EMode::Read):     options = "rb"; break;
        case INDEX(EType::Binary, EMode::Write):    options = "wb"; break;
        case INDEX(EType::Text, EMode::Read):       options = "r"; break;
        case INDEX(EType::Text, EMode::Write):      options = "w"; break;
    }
#undef INDEX

    // Open the file and get a handle
    m_file = fopen((const char *)filepath.GetString().Ptr(), options);
    ASSERT(m_file);

    // Get the length of the file
    Seek(EPosition::End, 0);
    m_bytes = Position();
    Seek(0);
}

//=============================================================================
Internal::CFile::~CFile ()
{
    Close();
}

//=============================================================================
bool Internal::CFile::IsOpen () const
{
    return m_file != null;
}

//=============================================================================
void Internal::CFile::Close ()
{
    if (!m_file)
        return;
    fclose((FILE *)m_file);
    m_file = null;
}

//=============================================================================
uint Internal::CFile::Position () const
{
    const uint pos = ftell((FILE *)m_file);
    return pos;
}

//=============================================================================
uint Internal::CFile::Bytes () const
{
    return m_bytes;
}

//=============================================================================
void Internal::CFile::Seek (uint seek)
{
    Seek(EPosition::Begin, seek);
}

//=============================================================================
void Internal::CFile::Seek (EPosition position, sint offset)
{
    int origin;
    switch (position)
    {
        case EPosition::Begin: origin = SEEK_SET; break;
        case EPosition::Current: origin = SEEK_SET; break;
        case EPosition::End: origin = SEEK_END; break;
    }

    fseek((FILE *)m_file, offset, origin);
}



//=============================================================================
//
// CReader
//
//=============================================================================

//=============================================================================
Internal::CReader::CReader (const CPath & filepath, EType type) :
    CFile(filepath, type, EMode::Read)
{
}

//=============================================================================
Internal::CReader::~CReader ()
{
}



//=============================================================================
//
// CTextReader
//
//=============================================================================

//=============================================================================
CTextReader::CTextReader (const CPath & filepath) :
    CReader(filepath, Internal::EType::Text)
{
    //m_encoding = StrEncoding()
}

//=============================================================================
CTextReader::~CTextReader ()
{
}

//=============================================================================
CString CTextReader::ReadAll ()
{
    const uint bytes = Bytes();
    TArray<byte> data;
    data.Resize(bytes);
    fread(data.Ptr(), sizeof(byte), bytes, (FILE *)m_file);

    const String::Encoding encoding = String::GetEncoding(data.Ptr());

    const byte * dataStart = data.Ptr() + encoding.bomBytes;

    switch (encoding.encoding)
    {
        default:
        case String::EEncoding::Utf8:
            return CStringUtf8::FromData(dataStart);

        case String::EEncoding::Utf16:
            if (encoding.endian == EEndian::Big)
                return CStringUtf16::FromData((const CStringUtf16::CodeUnit *)dataStart);
            else
                FATAL_EXIT("Do not support reading utf16-LE");

        //case String::EEncoding::Utf32:
        //    if (encoding.endian == EEndian::Big)
        //        return CStringUtf32::FromData((const CStringUtf32::CodeUnit *)dataStart);
        //    else
        //        FATAL_EXIT("Do not support reading utf32-LE");

        //case String::EEncoding::Ucs2:
        //    if (encoding.endian == EEndian::Big)
        //        return CStringUcs2::FromData((const CStringUcs2::CodeUnit *)dataStart);
        //    else
        //        FATAL_EXIT("Do not support reading ucs2-LE");

        //case String::EEncoding::Ucs4:
        //    if (encoding.endian == EEndian::Big)
        //        return CStringUcs4::FromData((const CStringUcs4::CodeUnit *)dataStart);
        //    else
        //        FATAL_EXIT("Do not support reading ucs4-LE");

        case String::EEncoding::Ascii:
            return CStringAscii::FromData((const CStringAscii::CodeUnit *)dataStart);
    }
}

//=============================================================================
CString CTextReader::ReadLine ()
{
    const uint pos = Position();
    CString out;

    return out;
}

//=============================================================================
TArray<CString> CTextReader::ReadLines ()
{
    TArray<CString> out;

    return out;
}



//=============================================================================
//
// CBinaryReader
//
//=============================================================================

//=============================================================================
CBinaryReader::CBinaryReader (const CPath & filepath) :
    CReader(filepath, Internal::EType::Binary)
{
}

//=============================================================================
CBinaryReader::~CBinaryReader ()
{
}

//=============================================================================
byte CBinaryReader::ReadByte ()
{
    byte out;
    Read(&out);
    return out;
}

//=============================================================================
TArray<byte> CBinaryReader::ReadAll ()
{
    const uint bytes = CFile::Bytes();

    TArray<byte> out;
    out.Reserve(bytes);

    Seek(0);
    fread((void *)out.Ptr(), 1, bytes, (FILE *)m_file);

    return out;
}


} // namespace File