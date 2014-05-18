

namespace Graphics
{

//=============================================================================
//
// CImageComponent
//
//=============================================================================

class CImageComponent :
    public IImageComponent,
    public CRenderComponent
{
public:

    CImageComponent (const CPath & filename, const Vector2 & size);
    ~CImageComponent ();

private: // CRenderComponent

    void Render (IRenderTarget * renderTarget);

private: // IComponent

    ComponentId     GetId () const { return CComponent::GetId(); }
    IEntity *       GetOwner () const override { return CComponent::GetOwner(); }
    ComponentType   GetType () const override { return IImageComponent::TYPE; }

private: // IImageComponent


private: // 

    IImage * m_image;
    Vector2  m_size;
};



//=============================================================================
//
// CPrimativeComponent
//
//=============================================================================

class CPrimativeComponent :
    public IPrimativeComponent,
    public CRenderComponent
{
    enum EType
    {
        TYPE_Circle,
        TYPE_Rect,
    };

public:

    // NOTE (jason): if there is a third constructor, consider making derived classes instead
    CPrimativeComponent (EType type, const Vector2 & size);
    CPrimativeComponent (float32 radius);
    CPrimativeComponent (const Vector2 & size);
    ~CPrimativeComponent ();

private: // CRenderComponent

    void Render (IRenderTarget * renderTarget);

private: // IComponent

    ComponentId     GetId () const { return CComponent::GetId(); }
    IEntity *       GetOwner () const override { return CComponent::GetOwner(); }
    ComponentType   GetType () const override { return IPrimativeComponent::TYPE; }

private: // IPrimativeComponent

    void SetColor (const Color & color) override;
    void SetPosition (const Point2 & pos) override;

private: // 

    EType   m_type;
    Vector2 m_size;
    Point2  m_position;
    Color   m_color;
};

} // namespace Graphics