namespace Graphics
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
public: // Internal -----------------------------------------------------------

    CContext ();
    ~CContext ();

    ID2D1HwndRenderTarget * GetRenderTarget () const { return m_pRenderTarget; }
    IWICImagingFactory *    GetWicFactory () const { return m_pWicFactory; }
    ID2D1SolidColorBrush *  GetColorBrush () const { return m_pSolidBrush; }
    IDWriteFactory *        GetDwriteFactory() const { return m_pDWriteFactory; }

    IDWriteTextFormat * FindTextFormat(Token name) { return m_textFormats.Find(name); }

    void OnCreate (CRenderComponent * comp);
    void OnCreate (CImage * image);
    void OnDestroy (CImage * image);

public: // Static -------------------------------------------------------------

    static CContext * Get () { return &s_context; }
    static CContext s_context;

public: // IContext -----------------------------------------------------------

    void Initialize (System::IWindow * window) override;
    void Uninitialize () override;

    Vector2 GetScreenSize () const override;

    // Rendering
    IRenderTarget * Backbuffer () override { return &m_backbuffer; }
    void Render () override;

    void DebugRender () override;
    void DebugText (const CString & text, const Point2 & pos, const Vector2 & size) override;
    Vector2 DebugTextMeasure (const CString & text, const Vector2 & size) override;

    // Images
    IImage * ImageLoad (const CString & filename) override;
    IImage * ImageCreate (uint width, uint height) override;
    IImage * ImageCreate (const Vector2u & size) override;
    void     ImageDestroy (IImage * image) override;

    // Text
    void TextRegisterStyle(Token name, const CString & font, float32 size) override;

    // Render Targets
    IRenderTarget * RenderTargetCreate (const Vector2u & size) override;
    void RenderTargetDestroy (IRenderTarget * renderTarget) override;

    // Notify
    void NotifyRegister (CContextNotify * target) override { m_notify.Add(target); }
    void NotifyUnregister (CContextNotify * target) override { m_notify.Remove(target); }

private: // System::IWindowNotify ---------------------------------------------

    void OnWindowSize (const Vector2u & size) override;

private: // -------------------------------------------------------------------

    typedef TNotifier<CContextNotify> CNotifier;
    typedef LIST_DECLARE(CRenderComponent, m_link) ListComponent;
    typedef TDictionary<Token, IDWriteTextFormat *> MapTextFormat;
    
    // Data
    System::IWindow *       m_pWindow;

    ID2D1Factory *          m_pD2DFactory;
    IDWriteFactory *        m_pDWriteFactory;
    IWICImagingFactory *    m_pWicFactory;

    ID2D1HwndRenderTarget * m_pRenderTarget;
    CRenderTarget           m_backbuffer;

    // Rendering objects
    ID2D1SolidColorBrush *  m_pSolidBrush;
    ID2D1BitmapBrush *      m_pBitmapBrush;
    MapTextFormat           m_textFormats;

    // Data
    std::vector<CImage *>   m_images;
    ListComponent           m_compList;
    CNotifier               m_notify;
};

} // namespace Graphics