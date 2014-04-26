
#include "GrPch.h"


namespace Graphics
{


//=============================================================================
//
// Helpers
//
//=============================================================================

bool IsColorLight (const Color & color)
{
    const Hsl hsl(color);

    return hsl.l > 0.4f;
}



//=============================================================================
//
// CRenderComponent
//
//=============================================================================

//=============================================================================
CRenderComponent::CRenderComponent ()
{
    CContext::Get()->OnCreate(this);
}

//=============================================================================
CRenderComponent::~CRenderComponent ()
{

}



//=============================================================================
//
// CImageComponent
//
//=============================================================================

//=============================================================================
CImageComponent::CImageComponent (const CString & filename, const Vector2 & size) :
    m_size(size)
{
    m_image = CContext::Get()->ImageLoad(filename);
}

//=============================================================================
CImageComponent::~CImageComponent ()
{
    CContext::Get()->ImageDestroy(m_image);
}

//=============================================================================
void CImageComponent::Render (IRenderTarget * renderTarget)
{
    IEntity * entity = GetOwner();
    if (auto * transform = entity->Get<CTransformComponent2>())
    {
        const Matrix23 & offset = Matrix23::CreateTranslation(-0.5f * m_image->GetSize());
        const Matrix23 & scale = Matrix23::CreateScale(m_size / m_image->GetSize());
        renderTarget->SetWorld(transform->GetMatrix() * scale * offset);
    }
    else
    {
        renderTarget->SetWorld(Matrix23::Identity);
    }

    renderTarget->Draw(m_image, Point2::Zero);
}



//=============================================================================
//
// IImageComponent
//
//=============================================================================

//=============================================================================
const ComponentType IImageComponent::TYPE('P','r','i','m','a','t','i','v','e');

//=============================================================================
IImageComponent * IImageComponent::Attach (IEntity * entity, const CString & filename, const Vector2 & size)
{
    CImageComponent * comp = new CImageComponent(filename, size);

    CContext::Get()->OnCreate(comp);

    entity->Attach(comp);

    return comp;
}



//=============================================================================
//
// CPrimativeComponent
//
//=============================================================================

//=============================================================================
CPrimativeComponent::CPrimativeComponent (EType type, const Vector2 & size) :
    m_type(type),
    m_size(size),
    m_position(Point2::Zero),
    m_color(Color(1.0f, 1.0f, 1.0f))
{

}

//=============================================================================
CPrimativeComponent::CPrimativeComponent (float32 radius) :
    CPrimativeComponent(TYPE_Circle, Vector2(radius, 0.0f))
{
}

CPrimativeComponent::CPrimativeComponent (const Vector2 & size) :
    CPrimativeComponent(TYPE_Rect, size)
{
}

//=============================================================================
CPrimativeComponent::~CPrimativeComponent ()
{
}

//=============================================================================
void CPrimativeComponent::SetPosition (const Point2 & pos)
{
    m_position = pos;
}

//=============================================================================
void CPrimativeComponent::SetColor (const Color & color)
{
    m_color = color;
}

//=============================================================================
void CPrimativeComponent::Render (IRenderTarget * renderTarget)
{
    IEntity * entity = GetOwner();
    auto * transform = entity->Get<CTransformComponent2>();
    if (transform)
    {
        const Matrix23 & trans  = Matrix23::CreateTranslation(transform->GetPosition());
        const Matrix23 & rotate = Matrix23::CreateRotation(transform->GetRotation());
        const Matrix23 & localTrans = Matrix23::CreateTranslation(m_position);
        const Matrix23 & world  = trans * rotate * localTrans;
        renderTarget->SetWorld(world);
    }
    else
    {
        renderTarget->SetWorld(Matrix23::Identity);
    }

    const Color INNER_COLOR(1.0f, 1.0f, 0.0f, 1.0f);
    const Color LINE_COLOR(0.0f, 0.0f, 0.0f, 1.0f);

    const auto & halfSize = 0.5f * m_size;
    switch (m_type)
    {
        case TYPE_Circle:
        {
            renderTarget->Circle(
                Point2::Zero,
                m_size.x,
                m_color
            );
        }
        break;

        case TYPE_Rect:
        {
            renderTarget->Rectangle(-halfSize, halfSize, m_color);
        }
        break;
    }

    renderTarget->Line(
        Point2::Zero,
        Point2(halfSize.x, 0.0f),
        IsColorLight(m_color) ? Color::Black : Color::White
    );
}


//=============================================================================
//
// IPrimativeComponent
//
//=============================================================================

//=============================================================================
const ComponentType IPrimativeComponent::TYPE('P','r','i','m','a','t','i','v','e');

//=============================================================================
IPrimativeComponent * IPrimativeComponent::Attach (IEntity * entity, float32 radius)
{
    CPrimativeComponent * comp = new CPrimativeComponent(radius);

    CContext::Get()->OnCreate(comp);

    entity->Attach(comp);

    return comp;
}

//=============================================================================
IPrimativeComponent * IPrimativeComponent::Attach (IEntity * entity, const Vector2 & size)
{
    CPrimativeComponent * comp = new CPrimativeComponent(size);

    CContext::Get()->OnCreate(comp);

    entity->Attach(comp);

    return comp;
}

} // namespace Graphics