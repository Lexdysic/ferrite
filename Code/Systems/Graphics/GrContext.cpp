
#include "GrPch.h"

#pragma comment(lib, "Dwrite.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib")


namespace Graphics
{



//*****************************************************************************
//
// CContext
//
//*****************************************************************************

//=============================================================================
CContext CContext::s_context;

//=============================================================================
CContext::CContext ()
{
}

//=============================================================================
CContext::~CContext ()
{
}

//=============================================================================
void CContext::Initialize (System::IWindow * window)
{
    ASSERT(window);

    CoInitialize(null);

    m_pWindow = window;

    // Create the factory
    D2D1CreateFactory(
        D2D1_FACTORY_TYPE_SINGLE_THREADED,
        &m_pD2DFactory
    );
    ASSERT(m_pD2DFactory);

    // Direct Write Factory
    DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(IDWriteFactory),
        reinterpret_cast<IUnknown **>(&m_pDWriteFactory)
    );
    ASSERT(m_pDWriteFactory);

    // WIC Factory
    CoCreateInstance(
        CLSID_WICImagingFactory1,
        null,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&m_pWicFactory)
    );
    ASSERT(m_pWicFactory);

    // Debug Font
    TextRegisterStyle(Token("Debug"), "Courier New", 10);

    // Create the render target
    {
        const Vector2u & clientSize = m_pWindow->GetClientSize();
        m_pD2DFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(
                D2D1_RENDER_TARGET_TYPE_HARDWARE
            ),
            D2D1::HwndRenderTargetProperties(
                (HWND)window->GetHwnd(),
                ToSizeU(clientSize)
            ),
            &m_pRenderTarget
        );
        ASSERT(m_pRenderTarget);
    }

    // Create a solid color brush to reuse
    {
        D2D1::ColorF color(D2D1::ColorF::Black);
        m_pRenderTarget->CreateSolidColorBrush(color, &m_pSolidBrush);
    }


    m_backbuffer.SetRenderTarget(m_pRenderTarget);

    m_pWindow->NotifyRegister(this);

}

//=============================================================================
void CContext::Uninitialize ()
{
    m_pWindow->NotifyUnregister(this);

    SafeRelease(m_pD2DFactory);
    SafeRelease(m_pDWriteFactory);
    SafeRelease(m_pWicFactory);
    SafeRelease(m_pRenderTarget);
    SafeRelease(m_pSolidBrush);
    SafeRelease(m_pBitmapBrush);

    for (const auto & pair : m_textFormats)
    {
        pair.second->Release();
    }

    m_pWindow = null;

    CoUninitialize();
}

//=============================================================================
Vector2 CContext::GetScreenSize () const
{
    return ToVector2(m_pRenderTarget->GetSize());
}

//=============================================================================
void CContext::Render ()
{
    for (auto comp : m_compList)
    {
        comp->Render(&m_backbuffer);
    }
}

//=============================================================================
void CContext::OnCreate (CRenderComponent * comp)
{
    m_compList.InsertTail(comp);
}

//=============================================================================
void CContext::DebugRender ()
{
    m_notify.Call(&CContextNotify::OnGraphicsDebugRender, Backbuffer());
}

//=============================================================================
void CContext::DebugText (const CString & text, const Point2 & pos, const Vector2 & size)
{
    const CStringUtf16 textUtf16 = text;

    IDWriteTextFormat * textFormat = CContext::Get()->FindTextFormat(Token("Debug"));

    m_pSolidBrush->SetColor(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
    m_pRenderTarget->DrawText(
        textUtf16.Ptr(),
        textUtf16.Count(),
        textFormat,
        D2D1::RectF(pos.x, pos.y, pos.x + size.x, pos.y + size.y),
        m_pSolidBrush
    );
}

//=============================================================================
Vector2 CContext::DebugTextMeasure (const CString & text, const Vector2 & size)
{
    const CStringUtf16 textUtf16 = text;

    IDWriteTextFormat * textFormat = CContext::Get()->FindTextFormat(Token("Debug"));

    IDWriteTextLayout * textLayout;
    m_pDWriteFactory->CreateTextLayout(
        textUtf16.Ptr(),
        textUtf16.Count(),
        textFormat,
        size.x,
        size.y,
        &textLayout
    );

    DWRITE_TEXT_METRICS metrics;
    textLayout->GetMetrics(&metrics);

    SafeRelease(textLayout);

    return Vector2(
        metrics.width,
        metrics.height
    );
}

//=============================================================================
void CContext::OnWindowSize (const Vector2u & size)
{
    m_pRenderTarget->Resize(ToSizeU(size));
}

//=============================================================================
IImage * CContext::ImageLoad (const CString & filename)
{
    ASSERT(!filename.IsNullOrEmpty());

    CImage * pImage = CImage::Create(filename);
    if (!pImage)
        return null;

    m_images.push_back(pImage);

    return pImage;
}

//=============================================================================
IImage * CContext::ImageCreate (uint width, uint height)
{
    return ImageCreate(Vector2u(width, height));
}

//=============================================================================
IImage * CContext::ImageCreate (const Vector2u & size)
{
    ASSERT(size.x && size.y);
    CImage * pImage = CImage::Create(size);
    if (!pImage)
        return null;
    m_images.push_back(pImage);
    return pImage;
}

//=============================================================================
void CContext::ImageDestroy (IImage * image_)
{
    CImage * image = CImage::From(image_);
    auto it = std::find(m_images.begin(), m_images.end(), image);
    ASSERT(it != m_images.end());

    m_images.erase(it);

    delete image;
}

//=============================================================================
void CContext::TextRegisterStyle(Token name, const CString & font, float32 size)
{
    ASSERT(!m_textFormats.Contains(name));
    ASSERT(m_pDWriteFactory);

    const CStringUtf16 fontUtf16 = font;

    IDWriteTextFormat * textFormat;
    m_pDWriteFactory->CreateTextFormat(
        fontUtf16.Ptr(),
        null,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        size,
        L"", // locale
        &textFormat
    );
    ASSERT(textFormat);

    textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
    textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

    m_textFormats.Set(name, textFormat);
}

//=============================================================================
IRenderTarget * CContext::RenderTargetCreate (const Vector2u & size)
{
    ID2D1BitmapRenderTarget * d2dRenderTarget;
    m_pRenderTarget->CreateCompatibleRenderTarget(
        ToSizeF(size),
        &d2dRenderTarget
    );
    CRenderTarget * renderTarget = new CRenderTarget(d2dRenderTarget);

    return renderTarget;
}

//=============================================================================
void CContext::RenderTargetDestroy (IRenderTarget * renderTarget)
{
    delete CRenderTarget::From(renderTarget);
}




//=============================================================================
//
// Functions
//
//=============================================================================

//=============================================================================
IContext * GetContext ()
{
    return CContext::Get();
}

} // namespace Graphics