
namespace UserInterface
{

class CProxy : IRefCounted<CProxy>
{
    REFCOUNTED_ADAPTER(CProxy)
    friend class CContext;
    friend class CWidget;

public:

    typedef TWeakPtr<CProxy> Ref;

public:
    CProxy (CWidget * widget, CWidget * parent);
    ~CProxy ();

    void Update ();
    void Render ();

    void AddChild (CProxy * child);
    void RemoveChild (CProxy * child);

    const Point2 & GetPosition () const { return m_position; }
    const Vector2 & GetSize () const { return m_actualSize; }
    void SetSize (const Vector2 & size);
    const Vector2 & GetNativeSize ();
    Aabb2 GetAabb () const { return Aabb2(m_position, m_position + m_actualSize); }

    CWidget * GetWidget () { return m_widget; }
    const TArray<CProxy::Ref> & GetChildren () { return m_children; }

    void SetMouseFlags (Flags32 mouseFlags);

private:
    // Constants
    static const uint32 FLAG_NEEDS_NATIVE_SIZE = (1 << 0);
    static const uint32 FLAG_WIDGET_DESTRUCT   = (1 << 1);

    // Data
    LIST_LINK(CProxy)   m_linkLayout;
    CWidget *           m_widget;
    CProxy::Ref         m_parent;
    TArray<CProxy::Ref> m_children;
    Vector2             m_actualSize;
    Vector2             m_nativeSize;
    Point2              m_position;
    Flags32             m_mouseFlags;
    Flags32             m_flags;
};

} // namespace UserInterface