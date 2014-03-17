#include "PhysPch.h"

namespace Physics
{

//=============================================================================
//
// Constants
//
//=============================================================================

const Time::Delta TIME_STEP = Time::Ms(10.0);
const Vector2 GRAVITY(0.0f, 100.0f);



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
        m_time += TIME_STEP;
        m_timeAccumulator -= TIME_STEP;
        Tick();
    }
}

//=============================================================================
void CContext::Tick ()
{
    const float t = TIME_STEP.GetSeconds();
    for (auto * rigidBody : m_rigidBodyList)
    {
        auto * transform = rigidBody->GetOwner()->Get<CTransformComponent2>();

        // Linear
        const Vector2 & linearForce = GRAVITY;
        const Vector2 & linearAcceleration = linearForce / rigidBody->mass;
        rigidBody->UpdateVelocity(linearAcceleration * t);
        transform->UpdatePositionLocal(rigidBody->GetVelocity() * t + 0.5f * linearAcceleration * Sq(t));

        // Angular
        const Radian angularAcceleration(-rigidBody->GetAngularVelocity() * 0.2f);
        rigidBody->UpdateAngularVelocity(angularAcceleration * t);
        transform->UpdateRotation(rigidBody->GetAngularVelocity() * t + 0.5f * angularAcceleration * Sq(t));
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

            renderTarget->Arrow(pos, pos + rigidBody->GetVelocity(), Color(1.0f, 0.0f, 1.0f));
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