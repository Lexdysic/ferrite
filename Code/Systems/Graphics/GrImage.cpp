#include "GrPch.h"

namespace Graphics
{

//=============================================================================
CImage * CImage::Create (const CPath & filename)
{
    IWICImagingFactory * pWicFactory = CContext::Get()->GetWicFactory();

    CStringUtf16 filenameUtf16 = filename.GetString();

    // Decoder
    IWICBitmapDecoder *pDecoder = null;
    HRESULT hr = pWicFactory->CreateDecoderFromFilename(
        filenameUtf16.Ptr(),
        null,
        GENERIC_READ,
        WICDecodeMetadataCacheOnLoad,
        &pDecoder
    );
    ASSERT(SUCCEEDED(hr));
    // NOTE: if no decoder is created, it is likely because of a bad filename
    if (!pDecoder)
        return null; 

    CImage * image = new CImage(filename, pDecoder);

    SafeRelease(pDecoder);

    return image;
}

//=============================================================================
CImage * CImage::Create (const Vector2u & size)
{
    CImage * image = new CImage(size);
    return image;
}

//=============================================================================
CImage::CImage () :
    m_pBitmap(null)
{

}

//=============================================================================
CImage::CImage (const CPath & filename, IWICBitmapDecoder *pDecoder) :
    m_filename(filename)
{
    HRESULT hr;

    // Frame
    IWICBitmapFrameDecode * pFrame = null;
    hr = pDecoder->GetFrame(0, &pFrame);
    ASSERT(SUCCEEDED(hr));
    ASSERT(pFrame);

    // Converter
    IWICImagingFactory * pWicFactory = CContext::Get()->GetWicFactory();
    IWICFormatConverter *pConverter = null;
    pWicFactory->CreateFormatConverter(&pConverter);
    ASSERT(pConverter);

    hr = pConverter->Initialize(
        pFrame,
        GUID_WICPixelFormat32bppPBGRA,
        WICBitmapDitherTypeNone,
        null,
        0.0f,
        WICBitmapPaletteTypeMedianCut
    );
    ASSERT(SUCCEEDED(hr));

    // Create
    ID2D1RenderTarget * pRenderTarget = CContext::Get()->GetRenderTarget();
    ASSERT(pRenderTarget);

    pRenderTarget->CreateBitmapFromWicBitmap(
        pConverter,
        null,
        &m_pBitmap
    );

    SafeRelease(pFrame);
    SafeRelease(pConverter);
}

//=============================================================================
CImage::CImage (const Vector2u & size)
{
    ID2D1RenderTarget * pRenderTarget = CContext::Get()->GetRenderTarget();
    ASSERT(pRenderTarget);

    D2D1_PIXEL_FORMAT pixelFormat = pRenderTarget->GetPixelFormat();
    //D2D1::PixelFormat(
    //    DXGI_FORMAT_B8G8R8A8_UNORM,
    //    D2D1_ALPHA_MODE_STRAIGHT
    //);

    const HRESULT hr = pRenderTarget->CreateBitmap(
        ToSizeU(size),
        D2D1::BitmapProperties(pixelFormat),
        &m_pBitmap
    );

    ASSERT(SUCCEEDED(hr));
}

//=============================================================================
CImage::CImage (ID2D1Bitmap * bitmap) :
    m_pBitmap(bitmap)
{

}

//=============================================================================
CImage::CImage (ID2D1BitmapRenderTarget * renderTarget) :
    m_pBitmap(null)
{
    renderTarget->GetBitmap(&m_pBitmap);
}

//=============================================================================
CImage::~CImage ()
{
    SafeRelease(m_pBitmap);
}

//=============================================================================
Vector2 CImage::GetSize () const
{
    return ToVector2(m_pBitmap->GetSize());
}

//=============================================================================
Vector2u CImage::GetDims () const
{
    const Vector2 & size = GetSize();
    return Vector2u(
        FloatToUint(size.x),
        FloatToUint(size.y)
    );
}


} // namespace Graphics