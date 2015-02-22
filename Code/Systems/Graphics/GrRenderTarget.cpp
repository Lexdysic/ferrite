#include "GrPch.h"

namespace Graphics
{

const float32 CURVE_COLLINEARITY_EPSILON = 1.0f;

//=============================================================================
CRenderTarget::CRenderTarget () :
    m_renderTarget(null),
    m_transformWorld(Matrix23::Identity),
    m_transformView(Matrix23::Identity)
{
}

//=============================================================================
CRenderTarget::CRenderTarget (ID2D1RenderTarget * renderTarget) :
    m_renderTarget(renderTarget),
    m_transformWorld(Matrix23::Identity),
    m_transformView(Matrix23::Identity),
    m_image((ID2D1BitmapRenderTarget *)renderTarget)
{
}

//=============================================================================
void CRenderTarget::SetRenderTarget (ID2D1RenderTarget * renderTarget)
{
    m_renderTarget = renderTarget;
}

//=============================================================================
Vector2 CRenderTarget::GetSize () const
{
    return m_image.GetSize();
}

//=============================================================================
Vector2u CRenderTarget::GetDims () const
{
    return m_image.GetDims();
}

//=============================================================================
IImage * CRenderTarget::GetImage ()
{
    return &m_image;
}

//=============================================================================
void CRenderTarget::Begin ()
{
    m_renderTarget->BeginDraw();
}

//=============================================================================
void CRenderTarget::End ()
{
    m_renderTarget->EndDraw();
}

//=============================================================================
void CRenderTarget::Clear (const Color & color)
{
    m_renderTarget->Clear(ToColorF(color));
}

//=============================================================================
void CRenderTarget::SetView (const Matrix23 & mat)
{
    m_transformView = mat;
    UpdateTransform();
}

//=============================================================================
void CRenderTarget::SetWorld (const Matrix23 & mat)
{
    m_transformWorld = mat;
    UpdateTransform();
}

//=============================================================================
void CRenderTarget::UpdateTransform ()
{
    const Vector2 & screenSize = CContext::Get()->GetScreenSize();

    const Matrix23 flipWindow(
        1.0f, 0.0f, 0.0f,
        0.0f, -1.0f, screenSize.y
    );
    const Matrix23 & transform = m_transformWorld * m_transformView;
    m_renderTarget->SetTransform(ToD2DMatrix23(transform));
}

//=============================================================================
void CRenderTarget::Line (
    const Point2 & a,
    const Point2 & b,
    const Color &  color,
    float32        width
) {
    ID2D1SolidColorBrush * brush = CContext::Get()->GetColorBrush();
    brush->SetColor(ToColorF(color));

    m_renderTarget->DrawLine(
        ToD2DPoint2F(a),
        ToD2DPoint2F(b),
        brush,
        width
    );
}

//=============================================================================
void CRenderTarget::Line (
    const TArray<Point2> & points,
    const Color & color,
    float32 width,
    ELoop loop
) {
    if (points.Count() < 2)
        return;

    ID2D1SolidColorBrush * brush = CContext::Get()->GetColorBrush();
    brush->SetColor(ToColorF(color));

    for (uint i = 1; i < points.Count(); ++i)
    {
        const Point2 & a = points[i-1];
        const Point2 & b = points[i];
        m_renderTarget->DrawLine(
            ToD2DPoint2F(a),
            ToD2DPoint2F(b),
            brush,
            width
        );
    }

    if (loop == ELoop::Closed)
    {
        const Point2 & a = points[0];
        const Point2 & b = points[points.Count() - 1];
        m_renderTarget->DrawLine(
            ToD2DPoint2F(a),
            ToD2DPoint2F(b),
            brush,
            width
        );
    }
}

//=============================================================================
void CRenderTarget::Rectangle (
    const Point2 & a,
    const Point2 & b, 
    const Color &  color,
    EDrawStyle     style
) {
    ID2D1SolidColorBrush * brush = CContext::Get()->GetColorBrush();
    brush->SetColor(ToColorF(color));

    if (style == EDrawStyle::Filled)
        m_renderTarget->FillRectangle(D2D1::RectF(a.x, a.y, b.x, b.y), brush);
    else
        m_renderTarget->DrawRectangle(D2D1::RectF(a.x, a.y, b.x, b.y), brush);
}

//=============================================================================
void CRenderTarget::Arrow (
    const Point2 &  a,
    const Point2 &  b,
    const Color &   color,
    float32         width
) {
    float length;
    const Vector2 & forward = Normalize(b - a, &length);
    if (length < 0.01f)
        return;

    const Vector2 & left = Vector2(-forward.y, forward.x);

    const float32 headSize = Min(5.0f, length * 0.5f);

    const Point2 & headBase = b - forward * headSize;
    const Point2 & headLeft = headBase + left * headSize * 0.5f;
    const Point2 & headRight = headBase - left * headSize * 0.5f;

    Line(a, b, color, width);
    Line(b, headLeft, color, width);
    Line(b, headRight, color, width);
    Line(headLeft, headRight, color, width);
}

//=============================================================================
void CRenderTarget::Arrow (
    const Point2 &  p,
    const Vector2 & v,
    const Color &   color,
    float32         width
) {
    Arrow(p, p+v, color, width);
}

//=============================================================================
void CRenderTarget::Circle(const Point2 & p, float32 r, const Color & color, EDrawStyle style)
{
    ID2D1SolidColorBrush * brush = CContext::Get()->GetColorBrush();
    brush->SetColor(ToColorF(color));

    if (style == EDrawStyle::Filled)
    {
        m_renderTarget->FillEllipse(
            D2D1::Ellipse(ToD2DPoint2F(p), r, r),
            brush
        );
    }
    else
    {
        m_renderTarget->DrawEllipse(
            D2D1::Ellipse(ToD2DPoint2F(p), r, r),
            brush
        );
    }
}

//=============================================================================
void CRenderTarget::Draw (IImage * image, const Point2 & a, float32 opacity)
{
    ASSERT(image);
    CImage * img = CImage::From(image);

    const Vector2 size = img->GetSize();
    m_renderTarget->DrawBitmap(
        img->GetBitmap(),
        D2D1::RectF(a.x, a.y, a.x + size.x, a.y + size.y),
        opacity
    );
}

//=============================================================================
void CRenderTarget::Draw (IImage * i, IImage * m, const Point2 & pos, float32 opacity)
{
    CImage * image = CImage::From(i);
    CImage * mask = CImage::From(m);

    const Vector2 size = image->GetSize();

    D2D1_BITMAP_BRUSH_PROPERTIES propertiesXClampYClamp = D2D1::BitmapBrushProperties(
        D2D1_EXTEND_MODE_CLAMP,
        D2D1_EXTEND_MODE_CLAMP,
        D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR
    );

    HRESULT hr;
    ID2D1BitmapBrush * imageBrush = null;
    hr = m_renderTarget->CreateBitmapBrush(
        image->GetBitmap(),
        propertiesXClampYClamp,
        &imageBrush
    );
    ASSERT(SUCCEEDED(hr));
    ASSERT(imageBrush);

    ID2D1BitmapBrush * maskBrush = null;
    hr = m_renderTarget->CreateBitmapBrush(
        mask->GetBitmap(),
        propertiesXClampYClamp,
        &maskBrush
    );
    ASSERT(SUCCEEDED(hr));
    ASSERT(maskBrush);

    D2D1_ANTIALIAS_MODE aaModePrev = m_renderTarget->GetAntialiasMode();

    m_renderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
    m_renderTarget->FillOpacityMask(
        mask->GetBitmap(),
        imageBrush,
        D2D1_OPACITY_MASK_CONTENT_GRAPHICS,
        &D2D1::RectF(pos.x, pos.y, pos.x + size.x, pos.y + size.y)
    );

    m_renderTarget->SetAntialiasMode(aaModePrev);

    SafeRelease(maskBrush);
    SafeRelease(imageBrush);
}

//=============================================================================
void CRenderTarget::Draw (const QuadraticCurve2 & curve, const Color & color, float32 width)
{
    // NOTE (jasonj): could build a line-strip instead of doing individual line calls

    // Use de Casteljau subdivision

    // Get the midpoint while retaining the temporaries. Same as curve.Eval(0.5f).
    const Point2 midpoint01 = Lerp(curve.m_p0, curve.m_p1, 0.5f);
    const Point2 midpoint12 = Lerp(curve.m_p1, curve.m_p2, 0.5f);
    const Point2 midpoint   = Lerp(midpoint01, midpoint12, 0.5f);

    // Determine if this curve is sufficiently flat to be represented as a single line segment
    const Vector2 delta = curve.m_p2 - curve.m_p0;
    const float32 d = Abs((curve.m_p1.x - curve.m_p2.x) * delta.y - (curve.m_p1.y - curve.m_p2.y) * delta.x);

    const bool isFlat = d < CURVE_COLLINEARITY_EPSILON;

    if (isFlat)
    {
        Line(curve.m_p0, curve.m_p2, color, width);
    }
    else
    {
        Draw(QuadraticCurve2(curve.m_p0, midpoint01, midpoint), color, width);
        Draw(QuadraticCurve2(midpoint, midpoint12, curve.m_p2), color, width);
    }
}

//=============================================================================
void CRenderTarget::Draw (const CubicCurve2 & curve, const Color & color, float32 width)
{
    const Point2 midpoint01  = Lerp(curve.m_p0, curve.m_p1, 0.5f);
    const Point2 midpoint12  = Lerp(curve.m_p1, curve.m_p2, 0.5f);
    const Point2 midpoint23  = Lerp(curve.m_p2, curve.m_p3, 0.5f);
    const Point2 midpoint012 = Lerp(midpoint01, midpoint12, 0.5f);
    const Point2 midpoint123 = Lerp(midpoint12, midpoint23, 0.5f);
    const Point2 midpoint    = Lerp(midpoint012, midpoint123, 0.5f);


    const Vector2 delta03 = curve.m_p3 - curve.m_p0;
    const Vector2 delta13 = curve.m_p1 - curve.m_p3;
    const Vector2 delta23 = curve.m_p2 - curve.m_p3;

    const float32 d2 = Abs(Cross(delta13, delta03));
    const float32 d3 = Abs(Cross(delta23, delta03));
    const bool isFlat = Sq(d2 + d3) < CURVE_COLLINEARITY_EPSILON * LengthSq(delta03);

    if (isFlat)
    {
        Line(curve.m_p0, curve.m_p3, color, width);
    }
    else
    {
        Draw(CubicCurve2(curve.m_p0, midpoint01, midpoint012, midpoint), color, width);
        Draw(CubicCurve2(midpoint, midpoint123, midpoint23, curve.m_p3), color, width);
    }
}


//=============================================================================
void CRenderTarget::Draw(const CString & text, Token style, const Point2 & pos, const Vector2 & size)
{
    ID2D1SolidColorBrush * brush = CContext::Get()->GetColorBrush();
    brush->SetColor(ToColorF(Color::White));

    IDWriteTextFormat * textFormat = CContext::Get()->FindTextFormat(style);

    CStringUtf16 textUtf16 = text;
    m_renderTarget->DrawText(
        textUtf16.Ptr(),
        textUtf16.Count(),
        textFormat,
        D2D1::RectF(pos.x, pos.y, pos.x + size.x, pos.y + size.y),
        brush
    );
}

//=============================================================================
Vector2 CRenderTarget::Measure(const CString & text, Token style, const Vector2 & size)
{
    IDWriteTextFormat * textFormat = CContext::Get()->FindTextFormat(style);
    
    CStringUtf16 textUtf16 = text;

    IDWriteTextLayout * textLayout;
    CContext::Get()->GetDwriteFactory()->CreateTextLayout(
        textUtf16.Ptr(),
        textUtf16.Count(),
        textFormat,
        size.x,
        size.y,
        &textLayout
    );

    
    DWRITE_TEXT_METRICS metrics;
    HRESULT hr = textLayout->GetMetrics(&metrics);
    ASSERT(SUCCEEDED(hr));

    SafeRelease(textLayout);

    return Vector2(
        metrics.width,
        metrics.height
   );
}


} // namespace Graphics