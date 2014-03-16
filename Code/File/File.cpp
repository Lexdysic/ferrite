#define USES_ENGINE_FILE


#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdio>


#include "EngineDeps.h"

namespace File
{


//=============================================================================
//
// CFile
//
//=============================================================================

Internal::CFile::CFile (const CString & filepath, EType type, EMode mode) :
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


    // TODO: replace this with newer string conversion stuff
    
    // Convert the string to one comptible with the C api
    std::string fp(filepath.Ptr(), filepath.Ptr() + filepath.Length());

    // Open the file and get a handle
    m_file = fopen(fp.c_str(), options);
    ASSERT(m_file);

    // Get the length of the file
    Seek(EPosition::End, 0);
    m_bytes = Position();
    Seek(0);
}

Internal::CFile::~CFile ()
{
    Close();
}

bool Internal::CFile::IsOpen () const
{
    return m_file != null;
}

void Internal::CFile::Close ()
{
    if (!m_file)
        return;
    fclose((FILE *)m_file);
    m_file = null;
}

uint Internal::CFile::Position () const
{
    const uint pos = ftell((FILE *)m_file);
    return pos;
}

uint Internal::CFile::Bytes () const
{
    return m_bytes;
}

void Internal::CFile::Seek (uint seek)
{
    Seek(EPosition::Begin, seek);
}

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

Internal::CReader::CReader (const CString & filepath, EType type) :
    CFile(filepath, type, EMode::Read)
{
}

Internal::CReader::~CReader ()
{
}



//=============================================================================
//
// CTextReader
//
//=============================================================================

CTextReader::CTextReader (const CString & filepath) :
    CReader(filepath, Internal::EType::Text)
{
    //m_encoding = StrEncoding()
}

CTextReader::~CTextReader ()
{
}

CString CTextReader::ReadAll ()
{
    const uint bytes = Bytes();
    TArray<byte> data;
    data.Resize(bytes);
    fread(data.Ptr(), sizeof(byte), bytes, (FILE *)m_file);

    return CString::FromData(data);
}

CString CTextReader::ReadLine ()
{
    const uint pos = Position();
    CString out;

    return out;
}

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

CBinaryReader::CBinaryReader (const CString & filepath) :
    CReader(filepath, Internal::EType::Binary)
{
}

CBinaryReader::~CBinaryReader ()
{
}

byte CBinaryReader::ReadByte ()
{
    byte out;
    fread((void *)&out, 1, 1, (FILE *)m_file);
    return out;
}

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