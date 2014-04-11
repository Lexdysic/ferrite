#include "PhysPch.h"

namespace Physics
{

//=============================================================================
//
// Constants
//
//=============================================================================

const Time::Delta TIME_STEP = Time::Ms(10.0);



//=============================================================================
//
// CContext
//
//=============================================================================

//=============================================================================
CContext CContext::s_context;

//=============================================================================
CContext::CContext () :
    m_timeAccumulator(0.0),
    m_gravity(0.0f, 100.0f),
    m_debugDrawRigidBody(false),
    m_debugDrawColliders(false)
{
}

//=============================================================================
CContext::~CContext ()
{
}

//=============================================================================
void CContext::Initialize ()
{
    Graphics::GetContext()->NotifyRegister(this);
}

//=============================================================================
void CContext::Uninitialize ()
{
    Graphics::GetContext()->NotifyUnregister(this);
}

//=============================================================================
void CContext::DebugToggleRigidBody ()
{
    m_debugDrawRigidBody = !m_debugDrawRigidBody;
}

//=============================================================================
void CContext::DebugToggleCollider ()
{
    m_debugDrawColliders = !m_debugDrawColliders;
}

//=============================================================================
void CContext::Update (Time::Delta deltaTime)
{
    m_timeAccumulator += deltaTime;
    while (m_timeAccumulator >= TIME_STEP)
    {
        m_timeAccumulator -= TIME_STEP;
        Tick();
    }
    Cleanup();
}

//=============================================================================
void CContext::Tick ()
{
    const float dt = TIME_STEP.GetSeconds();
    for (auto * rigidBody : m_rigidBodyList)
    {
        auto * transform = rigidBody->GetOwner()->Get<CTransformComponent2>();

        // Linear
        const Vector2 & linearAcceleration = rigidBody->m_force / rigidBody->m_mass + m_gravity;
        rigidBody->m_linearVelocity += linearAcceleration * dt;
        transform->UpdatePositionLocal(rigidBody->m_linearVelocity * dt + 0.5f * linearAcceleration * Sq(dt));

        // Angular
        const Radian angularAcceleration = Radian(rigidBody->m_torque / rigidBody->m_momentOfInertia);
        rigidBody->m_angularVelocity += angularAcceleration * dt;
        transform->UpdateRotation(rigidBody->m_angularVelocity * dt + 0.5f * angularAcceleration * Sq(dt));
    }
}

//=============================================================================
void CContext::Cleanup ()
{
    for (auto * rigidBody : m_rigidBodyList)
    {
        rigidBody->m_force  = Vector2::Zero;
        rigidBody->m_torque = 0.0f;
    }
}

//=============================================================================
void CContext::OnCreate (CRigidBodyComponent * comp)
{
    m_rigidBodyList.InsertTail(comp);
}

//=============================================================================
void CContext::OnCreate (CColliderComponent * comp)
{
    m_colliderList.InsertTail(comp);

    switch (comp->GetMaterial())
    {
        case EMaterial::Solid:
            m_solidList.InsertTail(comp);
        break;

        case EMaterial::Liquid:
            m_liquidList.InsertTail(comp);
        break;
    }
}

//=============================================================================
void CContext::OnGraphicsDebugRender (Graphics::IRenderTarget * renderTarget)
{
    if (m_debugDrawRigidBody)
    {
        for (auto * rigidBody : m_rigidBodyList)
        {
            auto * transform = rigidBody->GetOwner()->Get<CTransformComponent2>();

            const Point2 & pos = transform->GetPosition();

            renderTarget->Arrow(pos, pos + rigidBody->GetVelocity(), Color::Red);
        }
    }

    if (m_debugDrawColliders)
    {
        for (auto * collider : m_colliderList)
        {
            collider->RenderDebug(renderTarget);
        }
    }

    renderTarget->SetWorld(Matrix23::Identity);
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

} // namespace Physics