#include "GrPch.h"

namespace Graphics
{

//=============================================================================
CImage * CImage::Create (const wchar filename[])
{
    IWICImagingFactory * pWicFactory = CContext::Get()->GetWicFactory();

    // Decoder
    IWICBitmapDecoder *pDecoder = null;
    pWicFactory->CreateDecoderFromFilename(
        filename,
        null,
        GENERIC_READ,
        WICDecodeMetadataCacheOnLoad,
        &pDecoder
    );
    // NOTE: if no decoder is created, it is likely because of a bad filename
    if (!pDecoder)
        return nullptr; 

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
    m_pBitmap(nullptr)
{

}

//=============================================================================
CImage::CImage (const wchar filename[], IWICBitmapDecoder *pDecoder) :
    m_filename(filename)
{
    // Frame
    IWICBitmapFrameDecode * pFrame = null;
    pDecoder->GetFrame(0, &pFrame);
    ASSERT(pFrame);

    // Converter
    IWICImagingFactory * pWicFactory = CContext::Get()->GetWicFactory();
    IWICFormatConverter *pConverter = null;
    pWicFactory->CreateFormatConverter(&pConverter);
    ASSERT(pConverter);

    pConverter->Initialize(
        pFrame,
        GUID_WICPixelFormat32bppPBGRA,
        WICBitmapDitherTypeNone,
        null,
        0.0f,
        WICBitmapPaletteTypeMedianCut
    );

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