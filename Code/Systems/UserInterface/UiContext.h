
namespace UserInterface
{

//=============================================================================
//
// CContext
//
//=============================================================================
class CContext :
    public IContext,
    public System::CWindowNotify
{
public: // Static -------------------------------------------------------------

    static CContext s_context;
    static CContext * Get () { return &s_context; }

public: // Internal -----------------------------------------------------------

    CContext ();
    ~CContext ();

    void WidgetRegister (CWidget * widget, CWidget * parent);
    void WidgetUnregister (CWidget * widget);
    void WidgetDestroy (CWidget * widget);

    CProxy * FindProxy (const CWidget * widget);

    void NeedsLayout (CProxy * proxy);

public: // IContext -----------------------------------------------------------

    void Initialize (System::IWindow * window) override;
    void Uninitialize () override;

    void Update (const Time::Delta deltaTime) override;
    void Render () override;

private: // System::IWindowNotify ---------------------------------------------

    void OnWindowSize (const Vector2u & size) override;
    void OnWindowMouseDown (EMouse button, const Point2s & pos) override;
    void OnWindowMouseUp (EMouse button, const Point2s & pos) override;
    void OnWindowMouseMove (const Point2s & pos) override;
    void OnWindowMouseWheel (sint ticks, const Point2s & pos) override;

private: // -------------------------------------------------------------------

    // Types
    typedef TDictionary<const CWidget *, CProxy *> MapWidgetToProxy;
    typedef LIST_DECLARE(CProxy, m_linkLayout) ListLayout;
    typedef std::function<bool (CProxy *)> FProxyPredicate;

    // Data
    System::IWindow *   m_window;
    CProxy::Ref         m_root;
    TArray<CProxy::Ref> m_proxies;
    MapWidgetToProxy    m_proxyLookup;
    ListLayout          m_needsLayout;

    CProxy::Ref     m_mouseFocus;
    CProxy::Ref     m_mouseDown;

    // Helpers
    CProxy * FindProxyUnderPos (const Point2 & pos);
    CProxy * FindProxyUnderPos (const Point2 & pos, FProxyPredicate pred);
    void SetMouseFocus (CProxy * proxy);

};

} // namespace UserInterface