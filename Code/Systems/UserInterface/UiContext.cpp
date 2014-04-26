#include "UiPch.h"

namespace UserInterface
{

//=============================================================================
Point2 ToPoint2 (const Point2s & pos)
{
    return Point2(float32(pos.x), float32(pos.y));
}


//=============================================================================
//
// CContext
//
//=============================================================================

//=============================================================================
CContext CContext::s_context;

//=============================================================================
CContext::CContext () :
    m_window(null)
{

}

//=============================================================================
CContext::~CContext ()
{

}

//=============================================================================
void CContext::Initialize (System::IWindow * window)
{
    ASSERT(!m_window);
    m_window = window;
    m_window->NotifyRegister(this);
}

//=============================================================================
void CContext::Uninitialize ()
{
    while (m_proxies.Count())
    {
        CProxy * proxy = *m_proxies.Top();
        delete proxy->m_widget;
    }
    //for (auto & proxy : m_proxies)
    //    delete (const CProxy *)proxy;

    m_proxyLookup.Clear();

    m_window->NotifyUnregister(this);
    m_window = null;
}

//=============================================================================
void CContext::Update (const Time::Delta deltaTime)
{
    if (!m_root)
        return;

    // Scan through the tree and build an array which is in 
    // breadth-first order. Traverse using indicies because
    // iterators can easily become invalid.
    m_proxies.Clear();
    m_proxies.Add(m_root);
    for (uint i = 0; i < m_proxies.Count(); ++i)
    {
        CProxy * proxy = m_proxies[i];
        m_proxies.Add(proxy->GetChildren());
    }

    // Give all widgets a chance to update their internals
    for (auto proxy : m_proxies)
        proxy->Update();

    // Layout all widgets that require
    while (CProxy * proxy = m_needsLayout.Head())
    {
        proxy->m_linkLayout.Unlink();
        if (proxy->m_flags.Test(CProxy::FLAG_NEEDS_NATIVE_SIZE))
            proxy->SetSize(proxy->GetNativeSize());
        proxy->GetWidget()->OnWidgetLayout(proxy->m_position, proxy->m_actualSize);
    }
}

//=============================================================================
void CContext::Render ()
{
    for (auto proxy : m_proxies)
        proxy->Render();
}

//=============================================================================
void CContext::WidgetRegister (CWidget * widget, CWidget * parent)
{
    ASSERT(!FindProxy(widget));

    CProxy * proxy = new CProxy(widget, parent);

    m_proxyLookup.Set(widget, proxy);

    // All new widgets get an initial layout pass
    NeedsLayout(proxy);

    // Is this the root frame?
    if (!parent)
    {
        ASSERT(!m_root);
        m_root = proxy;
        m_root->m_position = Point2::Zero;
        m_root->SetSize(Graphics::GetContext()->GetScreenSize());
    }
    else
    {
        // We need to grab the size one initial time
        proxy->SetSize(proxy->GetNativeSize());
    }
}

//=============================================================================
void CContext::WidgetUnregister (CWidget * widget)
{
    CProxy * proxy = FindProxy(widget);
    m_proxyLookup.Delete(widget);

    // Clean up any potential dangling pointers
    const uint index = m_proxies.Find(proxy);
    ASSERT(index < m_proxies.Count());
    m_proxies.RemoveOrdered(index);
    //std::remove(m_proxies.Ptr(), m_proxies.Term(), proxy);

    // TODO: use weak pointers instead?
    if (proxy == m_mouseFocus)
        SetMouseFocus(null);
    if (proxy == m_mouseDown)
        m_mouseDown = null; // TODO: need to send off a mouse up?

    delete proxy;
}

//=============================================================================
void CContext::WidgetDestroy (CWidget * widget)
{
    CProxy * proxy = FindProxy(widget);
    m_proxyLookup.Delete(widget);
    delete proxy;
}

//=============================================================================
CProxy * CContext::FindProxy (const CWidget * widget)
{
    return (CProxy *)m_proxyLookup.Find(widget);
}

//=============================================================================
void CContext::NeedsLayout (CProxy * proxy)
{
    if (proxy->m_linkLayout.IsLinked())
        return;

    m_needsLayout.InsertTail(proxy);
}

//=============================================================================
void CContext::OnWindowSize (const Vector2u & clientSize)
{
    if (!m_root)
        return;

    const Vector2 screenSize(float32(clientSize.x), float32(clientSize.y));

    m_root->m_position = Point2::Zero;
    m_root->SetSize(screenSize);
}

//=============================================================================
void CContext::OnWindowMouseDown (EMouse button, const Point2s & mousePos)
{
    const Point2 pos = ToPoint2(mousePos);
    CProxy * proxy = FindProxyUnderPos(
        pos,
        [](CProxy * p) { return p->m_mouseFlags.Test(FLAG_MOUSE_CLICK); }
    );
    if (!proxy)
        return;

    m_mouseDown = proxy;
    proxy->GetWidget()->OnWidgetMouseDown((EMouse)button, pos);
}

//=============================================================================
void CContext::OnWindowMouseUp (EMouse button, const Point2s & mousePos)
{
    const Point2 pos = ToPoint2(mousePos);
    if (m_mouseDown)
    {
        m_mouseDown->GetWidget()->OnWidgetMouseUp((EMouse)button, pos);
        m_mouseDown = null;
    }
}

//=============================================================================
void CContext::OnWindowMouseMove (const Point2s & mousePos)
{
    const Point2 pos = ToPoint2(mousePos);
    CProxy * proxy = FindProxyUnderPos(
        pos,
        [](CProxy * p) { return p->m_mouseFlags.Test(FLAG_MOUSE_FOCUS); }
    );

    SetMouseFocus(proxy);

    if (m_mouseFocus)
    {
        m_mouseFocus->GetWidget()->OnWidgetMouseMove(pos);
    }
}

//=============================================================================
void CContext::OnWindowMouseWheel (sint ticks, const Point2s & mousePos)
{
    const Point2 pos = ToPoint2(mousePos);

    CProxy * proxy = FindProxyUnderPos(
        pos,
        [](CProxy * p) { return p->m_mouseFlags.Test(FLAG_MOUSE_WHEEL); }
    );
    if (!proxy)
        return;

    proxy->GetWidget()->OnWidgetMouseWheel(ticks, pos);
}

//=============================================================================
CProxy * CContext::FindProxyUnderPos (const Point2 & pos)
{
    CProxy::Ref * ptr = m_proxies.Term();
    CProxy::Ref * term = m_proxies.Ptr();
    while (ptr-- > term)
    {
        CProxy * widget = *ptr;
        const Aabb2 & aabb = widget->GetAabb();
        if (Contains(aabb, pos))
            return widget;
    }
    return null;
}

//=============================================================================
CProxy * CContext::FindProxyUnderPos (const Point2 & pos, FProxyPredicate pred)
{
    CProxy::Ref * ptr = m_proxies.Term();
    CProxy::Ref * term = m_proxies.Ptr();
    while (ptr-- > term)
    {
        CProxy * proxy = *ptr;
        const Aabb2 & aabb = proxy->GetAabb();
        if (!Contains(aabb, pos))
            continue;
        if (!pred(proxy))
            continue;
        return proxy;
    }
    return null;
}

//=============================================================================
void CContext::SetMouseFocus (CProxy * proxy)
{
    if (m_mouseFocus == proxy)
        return;
    CProxy * oldMouseFocus = m_mouseFocus;
    m_mouseFocus = proxy;

    if (oldMouseFocus)
        oldMouseFocus->GetWidget()->OnWidgetMouseExit();
    if (m_mouseFocus)
        m_mouseFocus->GetWidget()->OnWidgetMouseEnter();
}


//=============================================================================
//
// Free Functions
//
//=============================================================================

//=============================================================================
IContext * GetContext ()
{
    return &CContext::s_context;
}

} // namespace UserInterface