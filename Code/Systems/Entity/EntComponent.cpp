
#include "EntPch.h"



//=============================================================================
//
// CComponent
//
//=============================================================================

//=============================================================================
CComponent::CComponent () :
    m_id(CContext::Get()->GetComponentIdManager().New()),
    m_owner(NULL)
{

}

//=============================================================================
CComponent::~CComponent ()
{
    CContext::Get()->GetComponentIdManager().Delete(m_id);
}

//=============================================================================
ComponentId CComponent::GetId () const
{
    return m_id;
}

//=============================================================================
IEntity * CComponent::GetOwner () const
{
    return m_owner;
}

//=============================================================================
ComponentType CComponent::GetType () const
{
    FATAL_EXIT(L"Dervied components must specify a type");
    return ComponentType::Null;
}

//=============================================================================
void CComponent::Attached (IEntity * entity)
{
    m_owner = entity;
}

//=============================================================================
void CComponent::Detached (IEntity * entity)
{
    ASSERT(m_owner == entity);
    m_owner = NULL;
}

//=============================================================================
void CComponent::OnAttached (IEntity * entity)
{
}

//=============================================================================
void CComponent::OnDetached (IEntity * entity)
{
}



//=============================================================================
//
// CTransformComponent2
//
//=============================================================================

const ComponentType CTransformComponent2::TYPE('T','r','a','n','s','f','o','r','m','2');

//=============================================================================
CTransformComponent2::CTransformComponent2 () :
    m_parent(null),
    m_positionLocal(Point2::Zero),
    m_rotationLocal(0.0)
{

}

//=============================================================================
CTransformComponent2::~CTransformComponent2 ()
{

}

//=============================================================================
CTransformComponent2 * CTransformComponent2::Attach (IEntity * entity)
{
    CTransformComponent2 * comp = new CTransformComponent2();

    CContext::Get()->OnCreate(comp);

    entity->Attach(comp);

    return comp;
}

//=============================================================================
void CTransformComponent2::SetParent (CTransformComponent2 * parent)
{
    ASSERT(parent != this);

    // TODO (jason): ensure that we are not creating a cycle
    m_parent = parent;
    // TODO (jason): udpate world position cache?
}

//=============================================================================
void CTransformComponent2::SetParent (IEntity * entity)
{
    auto * transform = entity->Get<CTransformComponent2>();
    ASSERT(transform);

    SetParent(transform);
}

//=============================================================================
Point2 CTransformComponent2::GetPosition () const
{
    if (m_parent)
    {
        const Point2 & positionParent = m_parent->GetPosition();
        Radian rotationParent = m_parent->GetRotation();

        const Matrix22 & matRotationParent = Matrix22::CreateRotation(rotationParent);
        return matRotationParent * m_positionLocal + positionParent;
    }
    else
    {
        return m_positionLocal;
    }
}

//=============================================================================
const Point2 & CTransformComponent2::GetPositionLocal () const
{
    return m_positionLocal;
}

//=============================================================================
void CTransformComponent2::SetPosition (const Point2 & pos)
{
    if (m_parent)
    {
        FATAL_EXIT(L"Not implemented");
    }
    else
    {
        m_positionLocal = pos;
    }
}

//=============================================================================
void CTransformComponent2::SetPositionLocal (const Point2 & pos)
{
    m_positionLocal = pos;
}

//=============================================================================
void CTransformComponent2::UpdatePosition (const Vector2 & delta)
{
    SetPosition(GetPosition() + delta);
}

//=============================================================================
void CTransformComponent2::UpdatePositionLocal (const Vector2 & delta)
{
    m_positionLocal += delta;
}

//=============================================================================
Radian CTransformComponent2::GetRotation () const
{
    if (m_parent)
    {
        return m_rotationLocal + m_parent->GetRotation();
    }
    else
    {
        return m_rotationLocal;
    }
}

//=============================================================================
Radian CTransformComponent2::GetRotationLocal () const
{
    return m_rotationLocal;
}

//=============================================================================
void CTransformComponent2::SetRotation (Radian angle)
{
    if (m_parent)
    {
        FATAL_EXIT(L"Not implemented");
    }
    else
    {
        m_rotationLocal = angle;
    }
}

//=============================================================================
void CTransformComponent2::SetRotationLocal (Radian angle)
{
    m_rotationLocal = angle;
}

//=============================================================================
void CTransformComponent2::UpdateRotation (Radian delta)
{
    SetRotation(GetRotation() + delta);
}

//=============================================================================
void CTransformComponent2::UpdateRotationLocal (Radian delta)
{
    m_rotationLocal += delta;
}

//=============================================================================
Matrix23 CTransformComponent2::GetMatrix () const
{
    return Matrix23::CreateTransform(GetPosition(), GetRotation());
}