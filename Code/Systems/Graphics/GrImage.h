
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
    CLASS_CONVERSION(CImage, IImage);
public: // Internal

    CImage ();
    CImage (ID2D1BitmapRenderTarget * renderTarget);
    ~CImage ();

    ID2D1Bitmap * GetBitmap () const { return m_pBitmap; }

public: // Static

    static CImage * Create (const CPath & filename);
    static CImage * Create (const Vector2u & size);


public: // IImage

    Vector2 GetSize () const override;
    Vector2u GetDims () const override;
    const CPath & GetFilename () const override { return m_filename; }

private: //

    CImage (const CPath & filename, IWICBitmapDecoder *pDecoder);
    CImage (const Vector2u & size);
    CImage (ID2D1Bitmap * bitmap);

    // Data
    ID2D1Bitmap * m_pBitmap;
    CPath         m_filename;
};

} // namespace Graphics