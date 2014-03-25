
// Forward Declare
namespace System
{
    interface IWindow;
}


namespace Graphics
{

//=============================================================================
//
// Forwards
//
//=============================================================================

interface CContextNotify;



//=============================================================================
//
// Constants
//
//=============================================================================

enum class EPixelFormat
{
    R8G8B8,
    R8G8B8A8,
    A8
};

enum class EDrawStyle
{
    Filled,
    Outline
};

enum class ELoop
{
    Closed,
    Open
};

enum class ETextWeight
{
    Light,
    Normal,
    Bold,
};

struct FillOutline
{
    Color fill;
    Color outline;
};



//=============================================================================
//
// IImage
//
//=============================================================================

interface IImage
{
    // Properties
    virtual Vector2 GetSize () const pure;
    virtual Vector2u GetDims () const pure;
    virtual const wchar * GetFilename () const pure;
};



//=============================================================================
//
// IRenderCommands
//
//=============================================================================

interface IRenderCommands
{
    // Primatives
    virtual void Line (const Point2 & a, const Point2 & b, const Color & color, float32 width = 1.0f) pure;
    virtual void Line (const TArray<Point2> & points, const Color & color, float32 width = 1.0f, ELoop loop = ELoop::Open) pure;


    virtual void Rectangle(const Point2 & a, const Point2 & b, const Color & color, EDrawStyle style = EDrawStyle::Filled) pure;
    virtual void Arrow (const Point2 & a, const Point2 & b, const Color & color, float32 width = 1.0f) pure;
    virtual void Circle(const Point2 & p, float32 r, const Color & color, EDrawStyle style = EDrawStyle::Filled) pure;

    // Images
    virtual void Draw (IImage * image, const Point2 & pos, float32 opacity = 1.0f) pure;
    virtual void Draw (IImage * image, IImage * mask, const Point2 & pos, float32 opacity = 1.0f) pure;

    // Curves
    virtual void Draw (const QuadraticCurve2 & curve, const Color & color, float32 width = 1.0f) pure;
    virtual void Draw (const CubicCurve2 & curve, const Color & color, float32 width = 1.0f) pure;

    // Text
    virtual void Draw(const wchar text[], Token style, const Point2 & pos, const Vector2 & size = Vector2::Infinity) pure;
    virtual Vector2 Measure(const wchar text[], Token style, const Vector2 & size) pure;

};



//=============================================================================
//
// IRenderTarget
//
//=============================================================================

interface IRenderTarget : IRenderCommands
{
    // Properties
    virtual Vector2 GetSize () const pure;
    virtual Vector2u GetDims () const pure;
    virtual IImage * GetImage () pure;

    // Rendering
    virtual void Begin () pure;
    virtual void End () pure;
    virtual void Clear (const Color & color = Color::Black) pure;

    //virtual void SetModel (const Matrix23 & mat) pure;
    virtual void SetView (const Matrix23 & mat) pure;
    virtual void SetWorld (const Matrix23 & mat) pure;
};



//=============================================================================
//
// IContext
//
//=============================================================================

interface IContext
{
    virtual void Initialize (System::IWindow * window) pure;
    virtual void Uninitialize () pure;

    // View
    virtual Vector2 GetScreenSize () const pure;

    // Rendering
    virtual IRenderTarget * Backbuffer () pure;
    virtual void Render () pure;
    
    // Debug
    virtual void DebugRender () pure;
    virtual void DebugText (const wchar text[], const Point2 & pos, const Vector2 & size = Vector2::Infinity) pure;
    virtual Vector2 DebugTextMeasure (const wchar text[], const Vector2 & size) pure;

    // Images
    virtual IImage * ImageLoad (const wchar filename[]) pure;
    virtual IImage * ImageCreate (uint width, uint height) pure;
    virtual IImage * ImageCreate (const Vector2u & size) pure;
    virtual void     ImageDestroy (IImage * image) pure;

    // Text
    virtual void TextRegisterStyle(Token name, const wchar font[], float32 size) pure;

    // Render Targets
    virtual IRenderTarget * RenderTargetCreate (const Vector2u & size) pure;
    virtual void RenderTargetDestroy (IRenderTarget * renderTarget) pure;

    // Notifications
    virtual void NotifyRegister (CContextNotify * target) pure;
    virtual void NotifyUnregister (CContextNotify * target) pure;


};

IContext * GetContext ();



//=============================================================================
//
// CContextNotify
//
//=============================================================================

struct CContextNotify : TNotifyTarget<CContextNotify>
{
    virtual void OnGraphicsDebugRender (IRenderTarget * renderTarget) pure;
};



//=============================================================================
//
// CRenderComponent
//
//=============================================================================

class CRenderComponent :
    public CComponent
{
    friend class CContext;

public:
    CRenderComponent ();
    ~CRenderComponent ();

protected:
    virtual void Render (IRenderTarget * renderTarget) pure;

private: // Links
    LIST_LINK(CRenderComponent) m_link;
};


//=============================================================================
//
// IImageComponent
//
//=============================================================================

interface IImageComponent : IComponent
{
    static const ComponentType TYPE;
};



//=============================================================================
//
// IPrimativeComponent
//
//=============================================================================

interface IPrimativeComponent : IComponent
{
    static const ComponentType TYPE;
    static IPrimativeComponent * Attach (IEntity * entity, float32 radius);
    static IPrimativeComponent * Attach (IEntity * entity, const Vector2 & size);


    virtual void SetColor (const Color & color) pure;
    virtual void SetPosition (const Point2 & pos) pure;
};

} // namespace Graphics