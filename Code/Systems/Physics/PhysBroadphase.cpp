#include "PhysPch.h"

namespace Physics
{

//=============================================================================
TArray<CColliderComponent *> CBroadphase::Find (const Circle & circle, Flags32 group)
{
    // TODO: check the data structure for objects nearby

    TArray<CColliderComponent *> out;
    for (auto * collider : m_colliders)
    {
        if (!collider->GetGroups().Test(group))
            continue;

        out.Add(collider);
    }

    return out;
}

//=============================================================================
TArray<CColliderComponent *> CBroadphase::Find (const Aabb2 & box, Flags32 group)
{
    // TODO: check the data structure for objects nearby

    TArray<CColliderComponent *> out;
    for (auto * collider : m_colliders)
    {
        if (!collider->GetGroups().Test(group))
            continue;

        out.Add(collider);
    }

    return out;
}

//=============================================================================
void CBroadphase::Add (CColliderComponent * collider)
{
    m_colliders.InsertTail(collider);
}

//=============================================================================
void CBroadphase::Remove (CColliderComponent * collider)
{
    collider->m_linkBroadphase.Unlink();
}

//=============================================================================
void CBroadphase::Update (CColliderComponent * collider)
{
    // TODO: update the data structure about this colliders new position
}

} // namespace Physics