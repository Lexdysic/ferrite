
#include <Windows.h>

#include "Ferrite.h"
#include "Basics/Path/Path.h"


//*****************************************************************************
//
// Constants
//
//*****************************************************************************

namespace Path
{

const CString SEPARATOR = "/";

} // namespace Path



//*****************************************************************************
//
// CPath
//
//*****************************************************************************

//=============================================================================
CPath::CPath ()
{
}

//=============================================================================
CPath::CPath (const CString & rawPath)
{
    CStringBuilder builder;
    for (auto codepoint : rawPath)
    {
        if (codepoint == '\\')
            codepoint = String::CodePoint('/');
        builder += codepoint;
    }

    m_path = builder.GetString();
}

//=============================================================================
const CString & CPath::GetString () const
{
    return m_path;
}

//=============================================================================
bool CPath::IsDirectory () const
{
    return m_path.EndsWith(Path::SEPARATOR);
}

//=============================================================================
bool CPath::IsFile () const
{
    return !IsDirectory() && m_path.IsValid();
}

//=============================================================================
CPath operator+ (const CPath & lhs, const CPath & rhs)
{
    CStringBuilder builder;
    builder += lhs.m_path;

    const bool lhsHasSep = lhs.m_path.EndsWith(Path::SEPARATOR);
    const bool rhsHasSep = rhs.m_path.StartsWith(Path::SEPARATOR);
    if (lhsHasSep && rhsHasSep)
        NO_OP; // TODO: Remove separator
    if (!lhsHasSep && !rhsHasSep)
        builder += Path::SEPARATOR;
    builder += rhs.m_path;
    
    CPath out;
    out.m_path = builder.GetString();
    return out;
}

//=============================================================================
CPath operator+ (const CPath & lhs, const char rhs[])
{
    return lhs + CPath(rhs);
}



//*****************************************************************************
//
// CListing
//
//*****************************************************************************

namespace Path
{

//=============================================================================
CListing::CListing (const CPath & filepath) :
    m_filepath(filepath + "*")
{
}

//=============================================================================
CListing::CIterator CListing::begin ()
{
    return CIterator(m_filepath);
}

//=============================================================================
CListing::CIterator CListing::end ()
{
    return CIterator((void *)INVALID_HANDLE_VALUE);
}



//*****************************************************************************
//
// CListing::CIterator
//
//*****************************************************************************

//=============================================================================
CListing::CIterator::CIterator () :
    m_handle((void *)INVALID_HANDLE_VALUE)
{
}

//=============================================================================
CListing::CIterator::CIterator (const CIterator & rhs) :
    m_handle(rhs.m_handle)
{
}

//=============================================================================
CListing::CIterator::CIterator (const CPath & filepath)
{
    CStringUtf16 filepathUtf16 = filepath.GetString();

    WIN32_FIND_DATAW findData;
    HANDLE handle = ::FindFirstFileW(filepathUtf16.Ptr(), &findData);

    if (handle != INVALID_HANDLE_VALUE)
    {
        BOOL rv = true;
        while (rv && (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            rv = ::FindNextFileW(handle, &findData);
        }

        if (!rv)
            handle = INVALID_HANDLE_VALUE;
    }

    m_handle = (void *)handle;
    if (handle != INVALID_HANDLE_VALUE)
        m_filepath = CPath(CStringUtf16::FromData(findData.cFileName));
}

//=============================================================================
CListing::CIterator::CIterator (void * handle) :
    m_handle(handle)
{
}

//=============================================================================
CListing::CIterator::~CIterator ()
{
    ::FindClose((HANDLE)m_handle);
}

//=============================================================================
CPath CListing::CIterator::operator* () const
{
    return m_filepath;
}

//=============================================================================
const CListing::CIterator & CListing::CIterator::operator++ ()
{
    WIN32_FIND_DATAW findData;
    BOOL rv = false;
    do
    {
        rv = ::FindNextFileW((HANDLE)m_handle, &findData);
    }
    while (rv && findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);

    if (rv)
        m_filepath = CPath(CStringUtf16::FromData(findData.cFileName));
    else
        m_handle = (void *)INVALID_HANDLE_VALUE;

    return *this;
}

//=============================================================================
CListing::CIterator CListing::CIterator::operator++ (int)
{
    CIterator ret = *this;

    WIN32_FIND_DATAW findData;
    BOOL rv = false;
    do
    {
        rv = ::FindNextFileW((HANDLE)m_handle, &findData);
    }
    while (rv && findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);

    if (rv)
        m_filepath = CPath(CStringUtf16::FromData(findData.cFileName));
    else
        m_handle = (void *)INVALID_HANDLE_VALUE;

    return ret;
}

//=============================================================================
bool CListing::CIterator::operator< (const CIterator & rhs) const
{
    return this->m_handle < rhs.m_handle;
}

//=============================================================================
bool CListing::CIterator::operator== (const CIterator & rhs) const
{
    return this->m_handle == rhs.m_handle;
}

//=============================================================================
bool CListing::CIterator::operator!= (const CIterator & rhs) const
{
    return !(*this == rhs);
}

} //namespace Path