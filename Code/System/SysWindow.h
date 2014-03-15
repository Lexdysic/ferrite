#ifdef SYSWINDOW_H
#   error Header Included Twice
#endif
#define SYSWINDOW_H


namespace System {

//=============================================================================
//
// CWindow
//
//=============================================================================

class CWindow :
    public IWindow
{
public:

    CWindow (const wchar title[], uint width, uint height);
    virtual ~CWindow ();

public: // Static

    static CWindow * From (IWindow * x) { return (CWindow *)x; }
    static const CWindow * From (const IWindow * x) { return (CWindow *)x; }

public: // IWindow

    // Commands
    bool Update () override;
    bool UpdateBlocking () override;
    void Invalidate () const override;
    void SetTitle (const wchar title[]) override;

    // Query
    Vector2u GetClientSize () const override;
    void *   GetHwnd () const override { return (void *)mWindowHandle; }

    // Notify
    void NotifyRegister (CWindowNotify * notify) override;
    void NotifyUnregister (CWindowNotify * notify) override;

protected:

    void OnActivate (bool isActive);
    void OnClose ();
    void OnGetMinMaxInfo (MINMAXINFO * info);
    void OnKeyDown (uint8 key);
    void OnKeyUp (uint8 key);
    void OnMouseDown (uint8 button, const Point2s & pos);
    void OnMouseUp (uint8 button, const Point2s & pos);
    void OnMouseMove (const Point2s & pos);
    void OnMouseWheel (sint32 ticks, const Point2s & pos);
    void OnMoving ();
    void OnPaint (HDC hDc);
    void OnPaintBackground ();
    void OnSize ();
    void OnSizing ();

private:

    // Constants
    enum {
        FLAG_IS_ACTIVE          = 1 << 0,
        FLAG_CLOSE              = 1 << 1,
    };

    // Types
    struct InputData {
        bool  isDown;
        float timeStamp;
    };
    typedef TNotifier<CWindowNotify> NotifyList;

    // Data
    HWND            mWindowHandle;
    Flags<uint32>      mFlags;
    uint32             mWidth;
    uint32             mHeight;
    HCURSOR         mCursorNormal;
    HCURSOR         mCursorNull;
    NotifyList      m_notify;
    Flags<uint>     m_mouseDown;

    LRESULT OnMessage(UINT message, WPARAM wParam, LPARAM lParam);

private:

    static ULONG_PTR              msGdiStartupToken;
    static ULONG_PTR              msGdiHookToken;
    static Gdiplus::NotificationUnhookProc msGdiUnhookProc;

public:
    static void ClassInitialize();
    static void ClassUninitialize();
    static LRESULT CALLBACK StaticProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};



//=============================================================================
//
// CManager
//
//=============================================================================
class CManager
{
public:
    CManager ();

    CWindow * GetMainWindow () { return m_mainWindow; }
    void SetMainWindow (CWindow * window);

private:
    CWindow * m_mainWindow;
};


} // namespace System
