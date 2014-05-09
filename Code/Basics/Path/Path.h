

//=============================================================================
//
// Constants
//
//=============================================================================

namespace Path
{

extern const CString SEPARATOR;

}



//=============================================================================
//
// CPath
//
//=============================================================================

class CPath
{
public:

    CPath ();
    explicit CPath (const CString & rawPath);

    const CString & GetString () const;

    bool IsDirectory () const;
    bool IsFile () const;
    
public:

    friend CPath operator+ (const CPath & lhs, const CPath & rhs);

private:

    CString m_path;
};

CPath operator+ (const CPath & lhs, const CPath & rhs);
CPath operator+ (const CPath & lhs, const char rhs[]);





namespace Path
{

void SetCurrentDirectory(const CPath & path);
CPath GetCurrentDirectory();


//=============================================================================
//
// CListing
//
//=============================================================================

class CListing
{
public:

    CListing (const CPath & filepath);

public:

    class CIterator
    {
        friend class CListing;
    public:

        CIterator ();
        CIterator (const CIterator & rhs);
        ~CIterator ();

        CPath operator* () const;
        const CIterator & operator++ ();
        CIterator operator++ (int);
        bool operator< (const CIterator & rhs) const;
        bool operator== (const CIterator & rhs) const;
        bool operator!= (const CIterator & rhs) const;

    private:

        CIterator (const CPath & filepath);
        CIterator (void * handle);

        void * m_handle;
        CPath m_filepath;
    };

    CIterator begin ();
    CIterator end ();

private:

    CPath   m_filepath;
    void *  m_handle;
};
}