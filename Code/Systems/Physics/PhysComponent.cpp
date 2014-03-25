
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
    mass(1.0f),
    invMass(1.0f),
    momentOfInertia(1.0f), // Equivelent to mass for rotations
    invMomentOfInertia(1.0f)
{
}

//=============================================================================
CRigidBodyComponent::~CRigidBodyComponent ()
{

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
CColliderComponent::CColliderComponent (const Circle & circle) :
    m_type(TYPE_CIRCLE),
    m_circle(circle),
    m_coeffOfRestitution(1.0f)
{

}

//=============================================================================
CColliderComponent::CColliderComponent (const Aabb2 & aabb) :
    m_type(TYPE_BOX),
    m_aabb(aabb),
    m_coeffOfRestitution(1.0f)
{
}

//=============================================================================
CColliderComponent::CColliderComponent (EType type) :
    m_type(type),
    m_coeffOfRestitution(1.0f)
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
void CColliderComponent::RenderDebug (Graphics::IRenderTarget * renderTarget)
{
    const Color DEBUG_COLOR(0.0f, 1.0f, 1.0f);

    auto * transform = GetOwner()->Get<CTransformComponent2>();
    renderTarget->SetWorld(transform->GetMatrix());

    switch (m_type)
    {
        case TYPE_CIRCLE:
            renderTarget->Circle(
                m_circle.center,
                m_circle.radius,
                DEBUG_COLOR,
                Graphics::EDrawStyle::Outline
            );
        break;

        case TYPE_BOX:
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
IColliderComponent * IColliderComponent::Attach (IEntity * entity, const Circle & circle)
{
    CColliderComponent * comp = new CColliderComponent(circle);
    
    CContext::Get()->OnCreate(comp);

    entity->Attach(comp);

    return comp;
}

//=============================================================================
IColliderComponent * IColliderComponent::Attach (IEntity * entity, const Aabb2 & aabb)
{
    CColliderComponent * comp = new CColliderComponent(aabb);
    
    CContext::Get()->OnCreate(comp);

    entity->Attach(comp);

    return comp;
}

} // Physics