#include "UiPch.h"

namespace UserInterface
{

//=============================================================================
//
// CProxy
//
//=============================================================================

//=============================================================================
CProxy::CProxy (CWidget * widget, CWidget * parent) :
    m_widget(widget),
    m_parent(CContext::Get()->FindProxy(parent)),
    m_flags(FLAG_NEEDS_NATIVE_SIZE)
{
    if (m_parent)
        m_parent->AddChild(this);
}

//=============================================================================
CProxy::~CProxy ()
{
    while (m_children.Count())
    {
        CWidget * widget = (*m_children.Top())->m_widget;
        delete widget;
    }

    if (m_parent)
        m_parent->RemoveChild(this);

    if (!m_flags.Test(FLAG_WIDGET_DESTRUCT))
        delete m_widget;
}

//=============================================================================
void CProxy::Update ()
{
    m_widget->OnWidgetUpdate();
}

//=============================================================================
void CProxy::Render ()
{
    m_widget->OnWidgetRender(m_position, m_actualSize);
}

//=============================================================================
void CProxy::AddChild (CProxy * child)
{
    m_children.Add(child);
    CContext::Get()->NeedsLayout(this);
}

//=============================================================================
void CProxy::RemoveChild (CProxy * child)
{
    const uint index = m_children.Find(child);
    ASSERT(index < m_children.Count());
    m_children.RemoveUnordered(index);
}

//=============================================================================
void CProxy::SetSize (const Vector2 & size)
{
    if (size == m_actualSize)
        return;
    m_actualSize = size;
    CContext::Get()->NeedsLayout(this);
}

//=============================================================================
const Vector2 & CProxy::GetNativeSize ()
{
    m_widget->OnWidgetGetNativeSize(&m_nativeSize);
    return m_nativeSize;
}

//=============================================================================
void CProxy::SetMouseFlags (Flags32 mouseFlags)
{
    m_mouseFlags.ClearAll();
    m_mouseFlags.Set(mouseFlags);
}



//=============================================================================
//
// CWidget
//
//=============================================================================
//=============================================================================
CWidget::CWidget (CWidget * parent)
{
    CContext::Get()->WidgetRegister(this, parent);
}

//=============================================================================
CWidget::~CWidget ()
{
    CProxy * proxy = CContext::Get()->FindProxy(this);
    proxy->m_flags.Set(CProxy::FLAG_WIDGET_DESTRUCT);
    CContext::Get()->WidgetUnregister(this);
}

//=============================================================================
CWidget * CWidget::GetParent () const
{
    CProxy * proxy = CContext::Get()->FindProxy(this);
    return proxy->m_parent->GetWidget();
}

//=============================================================================
void CWidget::DestroyWidget ()
{
    CContext::Get()->WidgetDestroy(this);
}

//=============================================================================
void CWidget::SetPosition (const Point2 & pos)
{
    CProxy * proxy = CContext::Get()->FindProxy(this);
    proxy->m_position = pos;
}

//=============================================================================
const Point2 & CWidget::GetPosition () const
{
    CProxy * proxy = CContext::Get()->FindProxy(this);
    return proxy->m_position;
}

//=============================================================================
void CWidget::SetSize (const Vector2 & size)
{
    CProxy * proxy = CContext::Get()->FindProxy(this);
    proxy->SetSize(size);
}

//=============================================================================
Vector2 CWidget::GetNativeSize ()
{
    CProxy * proxy = CContext::Get()->FindProxy(this);
    return proxy->GetNativeSize();
}

//=============================================================================
void CWidget::SetMouseEnable (Flags32 mouseFlags)
{
    CProxy * proxy = CContext::Get()->FindProxy(this);
    return proxy->SetMouseFlags(mouseFlags);
}

//=============================================================================
void CWidget::ScheduleLayout ()
{
    CProxy * proxy = CContext::Get()->FindProxy(this);
    CContext::Get()->NeedsLayout(proxy);
}

//=============================================================================
void CWidget::OnWidgetGetNativeSize (Vector2 * outSize) { *outSize = Vector2::Zero; }
void CWidget::OnWidgetLayout (const Point2 &, const Vector2 &) {}
void CWidget::OnWidgetUpdate () {}
void CWidget::OnWidgetRender (const Point2 &, const Vector2 &) {}
void CWidget::OnWidgetMouseDown (EMouse, const Point2 &) {}
void CWidget::OnWidgetMouseUp (EMouse, const Point2 &) {}
void CWidget::OnWidgetMouseMove (const Point2 &) {}
void CWidget::OnWidgetMouseWheel (sint, const Point2 &) {}
void CWidget::OnWidgetMouseEnter () {}
void CWidget::OnWidgetMouseExit () {}

} // namespace UserInterface