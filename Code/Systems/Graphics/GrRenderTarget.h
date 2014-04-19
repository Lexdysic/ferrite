
namespace Graphics
{


//=============================================================================
//
// CRenderTarget
//
//=============================================================================

class CRenderTarget :
    public IRenderTarget
{
    CLASS_CONVERSION(CRenderTarget, IRenderTarget);

public: // Public

    CRenderTarget ();
    CRenderTarget (ID2D1RenderTarget * renderTarget);

    void SetRenderTarget (ID2D1RenderTarget * renderTarget);

private: // IRenderTarget

    Vector2 GetSize () const override;
    Vector2u GetDims () const override;
    IImage * GetImage () override;

    void Clear (const Color & color) override;

    void Begin () override;
    void End () override;

    void SetView (const Matrix23 & mat) override;
    void SetWorld (const Matrix23 & mat) override;

private: // IRenderCommands

    void Line (const Point2 & a, const Point2 & b, const Color & color, float32 width = 1.0f) override;
    void Line (const TArray<Point2> & points, const Color & color, float32 width, ELoop loop) override;

    void Rectangle(const Point2 & a, const Point2 & b, const Color & color, EDrawStyle style) override;
    void Arrow (const Point2 & a, const Point2 & b, const Color & color, float32 width = 1.0f) override;
    void Circle(const Point2 & p, float32 r, const Color & color, EDrawStyle style) override;

    void Draw (IImage * image, const Point2 & pos, float32 opacity = 1.0f) override;
    void Draw (IImage * image, IImage * mask, const Point2 & pos, float32 opacity = 1.0f) override;

    void Draw (const QuadraticCurve2 & curve, const Color & color, float32 width = 1.0f) override;
    void Draw (const CubicCurve2 & curve, const Color & color, float32 width = 1.0f) override;

    void Draw(const CString & text, Token style, const Point2 & pos, const Vector2 & size) override;
    Vector2 Measure(const CString & text, Token style, const Vector2 & size) override;

private: // Internals

    ID2D1RenderTarget * m_renderTarget;
    CImage              m_image;
    //Matrix23                m_transformModel;
    Matrix23            m_transformWorld;
    Matrix23            m_transformView;

    // Helpers
    void UpdateTransform ();

};


} // namespace Graphics