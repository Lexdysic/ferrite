#include "PhysPch.h"

namespace Physics
{

//=============================================================================
//
// Constants
//
//=============================================================================

const Time::Delta TIME_STEP = Time::Ms(8.0);



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
void CContext::NotifyRegister (IContextNotify * notify)
{
    m_notifier.Add(notify);
}

//=============================================================================
void CContext::NotifyUnregister (IContextNotify * notify)
{
    m_notifier.Remove(notify);
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
    uint counter = 0;
    m_debugCollisionCount = 0;

    m_timeAccumulator += deltaTime;
    while (m_timeAccumulator >= TIME_STEP)
    {
        m_notifier.Call(&IContextNotify::OnPhysicsPreTick);

        m_timeAccumulator -= TIME_STEP;
        counter++;
        Tick();

        m_notifier.Call(&IContextNotify::OnPhysicsPostTick);
        Cleanup();
    }


    DebugValue("Physics::Ticks", counter);
    DebugValue("Physics::Collisions", m_debugCollisionCount);
}

//=============================================================================
void CContext::Tick ()
{
    Detection();
    Integrate();
}

//=============================================================================
void CContext::Detection ()
{
    // TODO: find potential collection sets

    for (auto * colliderA = m_colliderList.Head(); colliderA; colliderA = m_colliderList.Next(colliderA))
    {
        auto * entityA        = colliderA->GetOwner();
        auto * rigidBodyA     = entityA->Get<IRigidBodyComponent>();
        const auto & velocityA = rigidBodyA ? rigidBodyA->GetVelocity() : Vector2::Zero;
        const auto & polygonA = colliderA->GetPolygon();

        for (auto * colliderB = m_colliderList.Next(colliderA); colliderB; colliderB = m_colliderList.Next(colliderB))
        {
            // TODO: check any collision filters

            auto * entityB         = colliderB->GetOwner();
            auto * rigidBodyB      = entityB->Get<IRigidBodyComponent>();
            const auto & velocityB = rigidBodyB ? rigidBodyB->GetVelocity() : Vector2::Zero;
            const auto & polygonB  = colliderB->GetPolygon();

            // There is no way to respond to two bodies with no rigidBody
            if (!rigidBodyA && !rigidBodyB)
                continue;

            const Vector2 relativeVelocity = velocityA - velocityB;
            CollisionResult result;
            if (!CheckCollision(polygonA, polygonB, relativeVelocity, &result))
                continue;

            Response(colliderA, colliderB, result);
        }
    }
}

//=============================================================================
bool CContext::CheckCollision (
    const Polygon2 &  polygonA,
    const Polygon2 &  polygonB,
    const Vector2 &   velocity,
    CollisionResult * result
) const {
    ASSERT(result);
    result->separation  = Math::Infinity;
    result->isCollide   = true;
    result->willCollide = true;

    // Check PolygonA
    if (!CheckCollisionSingle(
        polygonA,
        polygonA,
        polygonB,
        velocity,
        result
    )) {
        return false;
    }
    
    // Check PolygonB
    if (!CheckCollisionSingle(
        polygonB,
        polygonA,
        polygonB,
        velocity,
        result
    )) {
        return false;
    }

    return result->willCollide;
}

//=============================================================================
bool CContext::CheckCollisionSingle (
    const Polygon2 &  polygonCheck,
    const Polygon2 &  polygonA,
    const Polygon2 &  polygonB,
    const Vector2 &   velocity,
    CollisionResult * result
) const
{
    ASSERT(result);

    const uint count = polygonCheck.points.Count();
    for (uint iPrev = count-1, iCurr=0; iCurr < count; iPrev = iCurr, iCurr++)
    {
        // Get the current axis
        const Point2 &  prev = polygonCheck.points[iPrev];
        const Point2 &  curr = polygonCheck.points[iCurr];
        const Vector2 & edge = curr - prev;
        const Vector2 & axis = Normalize(Perpendicular(edge));

        // Get the projected interval along the axis
        Interval intervalA = polygonA.ProjectedIntervalAlongVector(axis);
        Interval intervalB = polygonB.ProjectedIntervalAlongVector(axis);

        // If the projected intervals overlap (negative distance), there is currently a collision
        if (Distance(intervalA, intervalB) > 0.0f)
            result->isCollide = false;

        // Add the projected velocity to the range in order to extend it
        const float32 projectedVelocity = Dot(axis, velocity);
        if (projectedVelocity < 0.0f)
            intervalA.min += projectedVelocity;
        else
            intervalA.max += projectedVelocity;

        // Do the same test with the velocity extended range
        float32 separation = Distance(intervalA, intervalB);
        if (separation > 0.0f)
            result->willCollide = false;

        // If no collision possible, we can exit loop
        if (!result->isCollide && !result->willCollide)
            return false;

        // Is this now the smallest separation?
        separation = Abs(separation);
        if (separation < result->separation)
        {
            result->separation = separation;
            result->direction  = axis;
        }
    }

    return true;
}

//=============================================================================
void CContext::Response (
    CColliderComponent * colliderA,
    CColliderComponent * colliderB,
    const CollisionResult & result
) {
    auto * entityA    = colliderA->GetOwner();
    auto * transformA = entityA->Get<CTransformComponent2>();
    auto * rigidBodyA = entityA->Get<IRigidBodyComponent>();

    auto * entityB    = colliderB->GetOwner();
    auto * transformB = entityB->Get<CTransformComponent2>();
    auto * rigidBodyB = entityB->Get<IRigidBodyComponent>();

    ASSERT(rigidBodyA || rigidBodyB);
    return; // TODO: this is not a valid thing to do

    if (rigidBodyA && rigidBodyB)
    {
        const float32 massA     = rigidBodyA ? rigidBodyA->GetMass() : Math::Infinity;
        const float32 massB     = rigidBodyB ? rigidBodyB->GetMass() : Math::Infinity;
        const float32 totalMass = massA + massB;
        const float32 coeffA    = massB / totalMass;
        const float32 coeffB    = massA / totalMass;

        transformA->UpdatePosition(result.direction * result.separation * coeffA);
        transformB->UpdatePosition(result.direction * result.separation * -coeffB);
    }
    else
    {
        auto * transform = rigidBodyA ? transformA : transformB;
        auto * rigidbody = rigidBodyA ? rigidBodyA : rigidBodyB;
        const float32 coeff = rigidBodyA ? 1.0f : -1.0f;

        const auto velocity = rigidbody->GetVelocity();
        const auto projectedSeparation = Dot(result.direction, velocity);
        const auto separation = result.direction * projectedSeparation * coeff;
        rigidbody->SetVelocity(velocity + separation);
    }



    m_debugCollisionCount++;
}

//=============================================================================
void CContext::Integrate()
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
    
    m_broadphase.Add(comp);
}

//=============================================================================
void CContext::OnDestroy (CColliderComponent * comp)
{
    m_broadphase.Remove(comp);
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