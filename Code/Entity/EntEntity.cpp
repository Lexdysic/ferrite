#include "EntPch.h"

//=============================================================================
//
// CEntity
//
//=============================================================================

//=============================================================================
CEntity::CEntity (EntityId id) :
    m_id(id)
{
}

//=============================================================================
CEntity::~CEntity ()
{
    for (auto it : m_components)
    {
        delete it.second;
    }
}

//=============================================================================
void CEntity::Attach (CComponent * comp)
{
    ASSERT(!m_components.Contains(comp->GetType()));

    m_components.Set(comp->GetType(), comp);

    comp->Attached(this);
}

//=============================================================================
void CEntity::Detach (CComponent * comp)
{
    ASSERT(m_components.Find(comp->GetType()) == comp);

    m_components.Delete(comp->GetType());

    comp->Detached(this);
}

//=============================================================================
CComponent * CEntity::Get (const ComponentType & type)
{
    return m_components.Find(type);
}

//=============================================================================
uint CEntity::GetComponentCount () const
{
    return m_components.Count();
}

//=============================================================================
CComponent * CEntity::EnumComponent (uint i)
{
    ASSERT(!"need to implement");
    return NULL;
}
