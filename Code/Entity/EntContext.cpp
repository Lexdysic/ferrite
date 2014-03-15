#include "EntPch.h"


//=============================================================================
//
// CContext
//
//=============================================================================

//=============================================================================
CContext CContext::s_context;

//=============================================================================
CContext::CContext () :
    m_debugDraw(false)
{

}

//=============================================================================
CContext::~CContext ()
{
    for (auto entityPair : m_entities)
        delete entityPair.second;
    m_entities.Clear();
}

//=============================================================================
void CContext::OnCreate (CTransformComponent2 * comp)
{
    m_transforms.InsertTail(comp);
}

//=============================================================================
IEntity * CContext::CreateEntity ()
{
    EntityId id = m_entityIdManager.New();
    CEntity * pEntity = new CEntity(id);

    m_entities.Set(id, pEntity);

    return pEntity;
}

//=============================================================================
void CContext::DestroyEntity (IEntity * entity)
{
    if (!entity)
        return;

    EntityId id = entity->GetId();
    delete CEntity::From(entity);
    m_entityIdManager.Delete(id);
    m_entities.Delete(id);
}

//=============================================================================
IEntity * CContext::GetEntity (EntityId id)
{
    return m_entities.Find(id);
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
void CContext::Update ()
{
    m_notifier.Call(&CEntityNotify::OnEntityUpdate);
}

//=============================================================================
void CContext::NotifyRegister (CEntityNotify * target)
{
    m_notifier.Add(target);
}

//=============================================================================
void CContext::NotifyUnregister (CEntityNotify * target)
{
    m_notifier.Remove(target);
}

//=============================================================================
void CContext::OnGraphicsDebugRender (Graphics::IRenderTarget * renderTarget)
{
    if (!m_debugDraw)
        return;

    for (auto * transform : m_transforms)
    {
        Radian rotation = transform->GetRotation();
        const Point2 & pos = transform->GetPosition();

        const float x = Cos(rotation);
        const float y = Sin(rotation);
        renderTarget->Line(pos, pos + Vector2(x, y) * 10.0f, Color::Red);
        renderTarget->Line(pos, pos + Vector2(-y, x) * 10.0f, Color::Green);
    }
}



//=============================================================================
//
// API Functions
//
//=============================================================================

//=============================================================================
IEntityContext * EntityGetContext ()
{
    return CContext::Get();
}



//=============================================================================
//
// CEntityNotify
//
//=============================================================================

void CEntityNotify::OnEntityUpdate () {}