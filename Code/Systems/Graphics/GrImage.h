
namespace Graphics
{


//=============================================================================
//
// CImage
//
//=============================================================================

class CImage :
    public IImage
{
public: // Internal

    CImage ();
    CImage (ID2D1BitmapRenderTarget * renderTarget);
    ~CImage ();

    ID2D1Bitmap * GetBitmap () const { return m_pBitmap; }

public: // Static

    static CImage * Create (const CString & filename);
    static CImage * Create (const Vector2u & size);

    static CImage * From (IImage * ptr) { return (CImage *)ptr; }
    static const CImage * From (const IImage * ptr) { return (const CImage *)ptr; }

public: // IImage

    Vector2 GetSize () const override;
    Vector2u GetDims () const override;
    const CString & GetFilename () const override { return m_filename; }

private: //

    CImage (const CString & filename, IWICBitmapDecoder *pDecoder);
    CImage (const Vector2u & size);
    CImage (ID2D1Bitmap * bitmap);

    // Data
    ID2D1Bitmap * m_pBitmap;
    CString       m_filename;
};

} // namespace Graphics