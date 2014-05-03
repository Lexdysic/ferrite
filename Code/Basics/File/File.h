 namespace File
{

namespace Internal
{

enum class EType
{
    Binary,
    Text
};

enum class EMode
{
    Write,
    Read
};

enum class EPosition
{
    Current,
    Begin,
    End,
};

class CFile;
class CReader;
class CWriter;

}



//=============================================================================
//
// CPath
//
//=============================================================================

class CPath
{
public:

    //CPath ();

private:
    CString m_path;
};

extern const String::CodePoint SEPARATOR;

void SetCurrentDirectory(const CPath & path);
CPath GetCurrentDirectory();



//=============================================================================
//
// CFile
//
//=============================================================================

class Internal::CFile
{
public:
    CFile (const CString & filepath, EType type, EMode mode);
    ~CFile ();
    
    void Close ();
    uint Position () const;
    void Seek (uint seek);
    void Seek (EPosition position, sint offset);

    bool IsEof () const;
    bool IsOpen () const;
    uint Bytes () const;

protected:
    void *  m_file;
    CString m_filepath;
    uint    m_bytes;
};



//=============================================================================
//
// CReader
//
//=============================================================================

class Internal::CReader : public Internal::CFile
{
public:
    CReader (const CString & filepath, EType type);
    ~CReader ();

protected:
};



//=============================================================================
//
// CTextReader
//
//=============================================================================

class CTextReader : public Internal::CReader
{
public:
    CTextReader (const CString & filepath);
    ~CTextReader ();

    String::EEncoding DetermineEncoding ();

    CString ReadAll ();
    CString ReadLine ();
    TArray<CString> ReadLines ();

private:
    String::EEncoding m_encoding;
};



//=============================================================================
//
// CBinaryReader
//
//=============================================================================

class CBinaryReader : public Internal::CReader
{
    CBinaryReader (const CString & filepath);
    ~CBinaryReader ();
    
    byte ReadByte ();
    TArray<byte> ReadAll ();

    template <typename T>
    T * Read ();
};



//=============================================================================
//
// CWriter
//
//=============================================================================

class Internal::CWriter : public Internal::CFile
{
public:
    CWriter (const CString & filepath);
    ~CWriter ();
};




//=============================================================================
//
// CDirectoryListing
//
//=============================================================================

class CDirectoryListing
{
public:

    CDirectoryListing (const CString & filepath);

public:

    class CIterator
    {
        friend class CDirectoryListing;
    public:

        CIterator ();
        CIterator (const CIterator & rhs);
        ~CIterator ();

        CString operator* () const;
        const CIterator & operator++ ();
        CIterator operator++ (int);
        bool operator< (const CIterator & rhs) const;
        bool operator== (const CIterator & rhs) const;
        bool operator!= (const CIterator & rhs) const;

    private:

        CIterator (const CString & filepath);
        CIterator (void * handle);

        void * m_handle;
        CString m_filepath;
    };

    CIterator begin ();
    CIterator end ();

private:

    CString m_filepath;
    void *  m_handle;
};

} // namespace File