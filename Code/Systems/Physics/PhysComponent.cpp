
#include "PhysPch.h"


namespace Physics
{

//=============================================================================
//
// CRigidBodyComponent
//
//=============================================================================

//=============================================================================
CRigidBodyComponent::CRigidBodyComponent () :
    CComponent(),
    m_linearVelocity(Vector2::Zero),
    m_angularVelocity(0.0f),
    m_force(Vector2::Zero),
    m_torque(0.0f)
{
    SetMass(1.0f);
}

//=============================================================================
CRigidBodyComponent::~CRigidBodyComponent ()
{

}

//=============================================================================
void CRigidBodyComponent::SetMass (float32 mass)
{
    m_mass = mass;
    m_momentOfInertia = m_mass * (Sq(100.0f) + Sq(70.0f)) / 12; // TODO: need a generic way to compute this
}

//=============================================================================
void CRigidBodyComponent::AddForce (const Vector2 & force, const Point2 & at)
{
    if (Equal(force, Vector2::Zero))
        return;

    CTransformComponent2 * transform = GetOwner()->Get<CTransformComponent2>();

    const Vector2 radius = at - transform->GetPosition();
    const float32 torque = Cross(radius, force);

    AddTorque(torque);
    AddForce(force);
}

//=============================================================================
void CRigidBodyComponent::AddForce (const Vector2 & f)
{
    ASSERT(Math::IsFinite(f.x) && Math::IsFinite(f.y));
    m_force += f;
}

//=============================================================================
void CRigidBodyComponent::AddTorque (float32 t)
{
    ASSERT(Math::IsFinite(t));
    m_torque += t;
}

//=============================================================================
void CRigidBodyComponent::OnAttached (IEntity * entity)
{
    CTransformComponent2 * transform = EnsureComponent<CTransformComponent2>(entity);
    ref(transform);
}

//=============================================================================
void CRigidBodyComponent::UpdateVelocity (const Vector2 & v)
{
    m_linearVelocity += v;
}

//=============================================================================
void CRigidBodyComponent::UpdateAngularVelocity (Radian angle)
{
    m_angularVelocity += angle;
}




//=============================================================================
//
// CColliderComponent
//
//=============================================================================

//=============================================================================
CColliderComponent::CColliderComponent (const Circle & circle, EMaterial material) :
    m_type(EType::Circle),
    m_circle(circle),
    m_coeffOfRestitution(1.0f),
    m_material(material),
    m_groupMask(Flags32::All)
{

}

//=============================================================================
CColliderComponent::CColliderComponent (const Aabb2 & aabb, EMaterial material) :
    m_type(EType::Box),
    m_aabb(aabb),
    m_coeffOfRestitution(1.0f),
    m_material(material),
    m_groupMask(Flags32::All)
{
}

//=============================================================================
CColliderComponent::CColliderComponent (EType type, EMaterial material) :
    m_type(type),
    m_coeffOfRestitution(1.0f),
    m_material(material),
    m_groupMask(Flags32::All)
{
}

//=============================================================================
CColliderComponent::~CColliderComponent ()
{
}

//=============================================================================
void CColliderComponent::OnAttached (IEntity * entity)
{
    CTransformComponent2 * comp = EnsureComponent<CTransformComponent2>(entity);
}

//=============================================================================
Aabb2 CColliderComponent::GetBoundingBox () const
{
    auto * transform = GetOwner()->Get<CTransformComponent2>();
    const float32 radius = Length(m_aabb.max - m_aabb.min) * 0.5f;

    return Aabb2(transform->GetPosition(), Vector2(radius, radius));
}

//=============================================================================
Polygon2 CColliderComponent::GetPolygon () const
{   
    auto * transform = GetOwner()->Get<CTransformComponent2>();
    const Matrix23 matrix = transform->GetMatrix();
    
    switch (m_type)
    {
        case EType::Circle:
            ASSERT(false); // What do?
        break;

        case EType::Box:
        {
            TArray<Point2> points = m_aabb.GetPoints();
            for (Point2 & p : points)
                p = matrix * p;
            return Polygon2(points);
        }
        break;
    }
    return Polygon2();
}

//=============================================================================
void CColliderComponent::RenderDebug (Graphics::IRenderTarget * renderTarget)
{
    const Color DEBUG_COLOR(0.0f, 1.0f, 1.0f);

    auto * transform = GetOwner()->Get<CTransformComponent2>();
    renderTarget->SetWorld(transform->GetMatrix());

    switch (m_type)
    {
        case EType::Circle:
            renderTarget->Circle(
                m_circle.center,
                m_circle.radius,
                DEBUG_COLOR,
                Graphics::EDrawStyle::Outline
            );
        break;

        case EType::Box:
            renderTarget->Rectangle(
                m_aabb.min,
                m_aabb.max,
                DEBUG_COLOR,
                Graphics::EDrawStyle::Outline
            );
        break;
    }
}


//=============================================================================
//
// IRigidBodyComponent
//
//=============================================================================

const ComponentType IRigidBodyComponent::TYPE('R','i','g','i','d','B','o','d','y');

//=============================================================================
IRigidBodyComponent * IRigidBodyComponent::Attach (IEntity * entity)
{
    CRigidBodyComponent * comp = new CRigidBodyComponent();
    
    CContext::Get()->OnCreate(comp);

    entity->Attach(comp);

    return comp;
}



//=============================================================================
//
// IColliderComponent
//
//=============================================================================

const ComponentType IColliderComponent::TYPE('C','o','l','l','i','d','e','r');

//=============================================================================
IColliderComponent * IColliderComponent::Attach (IEntity * entity, const Circle & circle, EMaterial material)
{
    CColliderComponent * comp = new CColliderComponent(circle, material);
    
    CContext::Get()->OnCreate(comp);

    entity->Attach(comp);

    return comp;
}

//=============================================================================
IColliderComponent * IColliderComponent::Attach (IEntity * entity, const Aabb2 & aabb, EMaterial material)
{
    CColliderComponent * comp = new CColliderComponent(aabb, material);
    
    CContext::Get()->OnCreate(comp);

    entity->Attach(comp);

    return comp;
}

} // Physics