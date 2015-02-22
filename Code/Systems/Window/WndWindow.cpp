
#include "WndPch.h"

#ifdef _MSC_VER
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "user32.lib")
#endif

namespace System {

struct VirtualKeyMapper
{
    int vk;
    EKey key;
};

static const VirtualKeyMapper s_mapVirtualKey[] =
{
    { 0x00,             EKey::Unknown, },
    { VK_LBUTTON,       EKey::Unknown },
    { VK_RBUTTON,       EKey::Unknown },
    { VK_CANCEL,        EKey::Unknown },
    { VK_MBUTTON,       EKey::Unknown },
    { VK_XBUTTON1,      EKey::Unknown },
    { VK_XBUTTON2,      EKey::Unknown },
    { 0x07,             EKey::Unknown },
    { VK_BACK,          EKey::Unknown },
    { VK_TAB,           EKey::Unknown },
    { 0x0a,             EKey::Unknown },
    { 0x0b,             EKey::Unknown },
    { VK_CLEAR,         EKey::Unknown },
    { VK_RETURN,        EKey::Unknown },
    { 0x0e,             EKey::Unknown },
    { 0x0f,             EKey::Unknown },
    { VK_SHIFT,         EKey::Unknown },
    { VK_CONTROL,       EKey::Unknown },
    { VK_MENU,          EKey::Unknown },
    { VK_PAUSE,         EKey::Unknown },
    { VK_CAPITAL,       EKey::Unknown },
    { VK_KANA,          EKey::Unknown },
    { 0x16,             EKey::Unknown },
    { VK_JUNJA,         EKey::Unknown },
    { VK_FINAL,         EKey::Unknown },
    { VK_KANJI,         EKey::Unknown },
    { 0x1a,             EKey::Unknown },
    { VK_ESCAPE,        EKey::Escape },
    { VK_CONVERT,       EKey::Unknown },
    { VK_NONCONVERT,    EKey::Unknown },
    { VK_ACCEPT,        EKey::Unknown },
    { VK_MODECHANGE,    EKey::Unknown },
    { VK_SPACE,         EKey::Space },
    { VK_PRIOR,         EKey::PageUp },
    { VK_NEXT,          EKey::PageDown },
    { VK_END,           EKey::End },
    { VK_HOME,          EKey::Home },
    { VK_LEFT,          EKey::Left },
    { VK_UP,            EKey::Up },
    { VK_RIGHT,         EKey::Right },
    { VK_DOWN,          EKey::Down },
    { VK_SELECT,        EKey::Unknown },
    { VK_PRINT,         EKey::Unknown },
    { VK_EXECUTE,       EKey::Unknown },
    { VK_SNAPSHOT,      EKey::Unknown },
    { VK_INSERT,        EKey::Insert },
    { VK_DELETE,        EKey::Delete },
    { VK_HELP,          EKey::Unknown },
    { '0',              EKey::Num0 },
    { '1',              EKey::Num1 },
    { '2',              EKey::Num2 },
    { '3',              EKey::Num3 },
    { '4',              EKey::Num4 },
    { '5',              EKey::Num5 },
    { '6',              EKey::Num6 },
    { '7',              EKey::Num7 },
    { '8',              EKey::Num8 },
    { '9',              EKey::Num9 },
    { 0x3a,             EKey::Unknown },
    { 0x3b,             EKey::Unknown },
    { 0x3c,             EKey::Unknown },
    { 0x3d,             EKey::Unknown },
    { 0x3e,             EKey::Unknown },
    { 0x3f,             EKey::Unknown },
    { 0x40,             EKey::Unknown },
    { 'A',              EKey::A },
    { 'B',              EKey::B },
    { 'C',              EKey::C },
    { 'D',              EKey::D },
    { 'E',              EKey::E },
    { 'F',              EKey::F },
    { 'G',              EKey::G },
    { 'H',              EKey::H },
    { 'I',              EKey::I },
    { 'J',              EKey::J },
    { 'K',              EKey::K },
    { 'L',              EKey::L },
    { 'M',              EKey::M },
    { 'N',              EKey::N },
    { 'O',              EKey::O },
    { 'P',              EKey::P },
    { 'Q',              EKey::Q },
    { 'R',              EKey::R },
    { 'S',              EKey::S },
    { 'T',              EKey::T },
    { 'U',              EKey::U },
    { 'V',              EKey::V },
    { 'W',              EKey::W },
    { 'X',              EKey::X },
    { 'Y',              EKey::Y },
    { 'Z',              EKey::Z },
    { VK_LWIN,          EKey::Unknown },
    { VK_RWIN,          EKey::Unknown },
    { VK_APPS,          EKey::Unknown },
    { 0x5e,             EKey::Unknown },
    { VK_SLEEP,         EKey::Unknown },
    { VK_NUMPAD0,       EKey::NumPad0 },
    { VK_NUMPAD1,       EKey::NumPad1 },
    { VK_NUMPAD2,       EKey::NumPad2 },
    { VK_NUMPAD3,       EKey::NumPad3 },
    { VK_NUMPAD4,       EKey::NumPad4 },
    { VK_NUMPAD5,       EKey::NumPad5 },
    { VK_NUMPAD6,       EKey::NumPad6 },
    { VK_NUMPAD7,       EKey::NumPad7 },
    { VK_NUMPAD8,       EKey::NumPad8 },
    { VK_NUMPAD9,       EKey::NumPad9 },
    { VK_MULTIPLY,      EKey::NumPadMultply },
    { VK_ADD,           EKey::NumPadAdd },
    { VK_SEPARATOR,     EKey::Unknown },
    { VK_SUBTRACT,      EKey::NumPadSubtract },
    { VK_DECIMAL,       EKey::NumPadDelete },
    { VK_DIVIDE,        EKey::NumPadDivide },
    { VK_F1,            EKey::F1 },
    { VK_F2,            EKey::F2 },
    { VK_F3,            EKey::F3 },
    { VK_F4,            EKey::F4 },
    { VK_F5,            EKey::F5 },
    { VK_F6,            EKey::F6 },
    { VK_F7,            EKey::F7 },
    { VK_F8,            EKey::F8 },
    { VK_F9,            EKey::F9 },
    { VK_F10,           EKey::F10 },
    { VK_F11,           EKey::F11 },
    { VK_F12,           EKey::F12 },
    { VK_F13,           EKey::Unknown },
    { VK_F14,           EKey::Unknown },
    { VK_F15,           EKey::Unknown },
    { VK_F16,           EKey::Unknown },
    { VK_F17,           EKey::Unknown },
    { VK_F18,           EKey::Unknown },
    { VK_F19,           EKey::Unknown },
    { VK_F20,           EKey::Unknown },
    { VK_F21,           EKey::Unknown },
    { VK_F22,           EKey::Unknown },
    { VK_F23,           EKey::Unknown },
    { VK_F24,           EKey::Unknown },
};

static EKey FindKey (int vk)
{
    if (vk >= array_size(s_mapVirtualKey))
        return EKey::Unknown;

    ASSERT(s_mapVirtualKey[vk].vk == vk);
    return s_mapVirtualKey[vk].key;
}



//=============================================================================
//
// CManager
//
//*****************************************************************************

//=============================================================================
static CManager s_manager;

//=============================================================================
CManager::CManager () :
    m_mainWindow(null)
{
}

//=============================================================================
void CManager::SetMainWindow (CWindow * window)
{
    ASSERT(!window || !m_mainWindow);
    m_mainWindow = window;
}




//=============================================================================
//
// CWindow
//
//=============================================================================


//=============================================================================
CWindow::CWindow (const CString & title, uint width, uint height) :
    m_width(width),
    m_height(height),
    m_windowHandle(null),
    m_cursorNormal(null),
    m_cursorNull(null)
{
    HINSTANCE instance = GetModuleHandle(0);

    const CStringUtf16 utf16 = title;
    const wchar * className = utf16.Ptr();

    // Cursors
    {
        uint32 cursorAnd = 0xFFFFFFFF;
        uint32 cursorXor = 0x00000000;
        m_cursorNull   = CreateCursor(null, 0, 0, 1, 1, &cursorAnd, &cursorXor);
        m_cursorNormal = LoadCursor(null, IDC_ARROW);
    }

    // Window Class
    {
        UnregisterClassW(className, instance);

        WNDCLASSEXW windowClass;
        windowClass.cbSize        = sizeof(WNDCLASSEXW);
        windowClass.style         = CS_OWNDC;
        windowClass.lpfnWndProc   = &StaticProc;
        windowClass.cbClsExtra    = 0;
        windowClass.cbWndExtra    = 0;
        windowClass.hInstance     = instance;
        windowClass.hIcon         = LoadIcon(null, IDI_APPLICATION);
        windowClass.hCursor       = null;
        windowClass.hbrBackground = null;
        windowClass.lpszMenuName  = null;
        windowClass.hIconSm       = null;
        windowClass.lpszClassName = className;

        const ATOM ret = RegisterClassEx(&windowClass);
        ASSERT(ret);
    }

    // Create Window
    {
        const uint32 style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

        RECT adjustedRect = {0, 0, m_width, m_height};
        AdjustWindowRect(&adjustedRect, style, false);

        const uint32 adjustedWidth  = adjustedRect.right  - adjustedRect.left;
        const uint32 adjustedHeight = adjustedRect.bottom - adjustedRect.top;

        m_windowHandle = CreateWindowW(
            className,
            utf16.Ptr(), 
            style, 
            CW_USEDEFAULT, 
            CW_USEDEFAULT, 
            adjustedWidth, 
            adjustedHeight, 
            null, 
            null, 
            instance, 
            null
        );

        ASSERT(m_windowHandle);
    }

    SetWindowLongPtrW(m_windowHandle, GWLP_USERDATA, (LONG_PTR)this);
    SetWindowTextW(m_windowHandle, utf16.Ptr());
}

//=============================================================================
CWindow::~CWindow() 
{
    DestroyCursor(m_cursorNull);

    DestroyWindow(m_windowHandle);
    m_windowHandle = 0;
}

//=============================================================================
Vector2u CWindow::GetClientSize () const
{
    RECT rect;
    ::GetClientRect(m_windowHandle, &rect);

    return Vector2u(rect.right - rect.left, rect.bottom - rect.top);
}

//=============================================================================
void CWindow::Invalidate() const
{
    InvalidateRect(m_windowHandle, null, false);
}

//=============================================================================
void CWindow::SetTitle (const CString & title)
{
    CStringUtf16 utf16 = title;
    SetWindowTextW(m_windowHandle, utf16.Ptr());
}

//=============================================================================
void CWindow::NotifyRegister (CWindowNotify * notify)
{
    m_notify.Add(notify);
}

//=============================================================================
void CWindow::NotifyUnregister (CWindowNotify * notify)
{
    m_notify.Remove(notify);
}

//=============================================================================
LRESULT CWindow::OnMessage (UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
    switch (uMsg)
    {
        case WM_ACTIVATE:
            OnActivate(wParam != WA_INACTIVE);
        break;

        case WM_CLOSE:
        case WM_QUIT:
            OnClose();
        break;

        case WM_ERASEBKGND:
        break;

        case WM_GETMINMAXINFO:
        {
            MINMAXINFO * pInfo = (MINMAXINFO *)lParam;
            OnGetMinMaxInfo(pInfo);
        }
        break;

        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        {
            uint8 key = (uint8)wParam;
            OnKeyDown(key);
        }
        break;

        case WM_KEYUP:
        case WM_SYSKEYUP:
        {
            uint8 key = (uint8)wParam;
            OnKeyUp(key);
        }
        break;

        case WM_LBUTTONDOWN:
            OnMouseDown(VK_LBUTTON, Point2s(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
        break;

        case WM_MBUTTONDOWN:
            OnMouseDown(VK_MBUTTON, Point2s(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
        break;

        case WM_RBUTTONDOWN:
            OnMouseDown(VK_RBUTTON, Point2s(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
        break;

            //if( !m_flags.Test(FLAG_MOUSE_LEFT | FLAG_MOUSE_MIDDLE | FLAG_MOUSE_RIGHT) )
            //    SetCapture(m_windowHandle);

        case WM_LBUTTONUP:
            OnMouseUp(VK_LBUTTON, Point2s(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
        break;

        case WM_MBUTTONUP:
            OnMouseUp(VK_MBUTTON, Point2s(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
        break;

        case WM_RBUTTONUP:
            OnMouseUp(VK_RBUTTON, Point2s(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
        break;

            //if( !m_flags.Test(FLAG_MOUSE_LEFT | FLAG_MOUSE_MIDDLE | FLAG_MOUSE_RIGHT) )
            //    ReleaseCapture();

        case WM_MOUSEMOVE:
            OnMouseMove(Point2s(LOWORD(lParam), HIWORD(lParam)));
        break;

        case WM_MOUSEWHEEL:
        {
            const sint16 wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
            const sint32 ticks = wheelDelta / WHEEL_DELTA;

            POINT pos = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
            ScreenToClient(m_windowHandle, &pos);

            OnMouseWheel(ticks, Point2s(pos.x, pos.y));
        }
        break;

        case WM_MOVING:
            OnMoving();
        break;

        case WM_PAINT: 
        {
            PAINTSTRUCT ps;
            HDC hDc = BeginPaint(m_windowHandle, &ps);
            OnPaint(hDc);
            EndPaint(m_windowHandle, &ps);
        }
        break;

        case WM_SETCURSOR:
            if (LOWORD(lParam) == HTCLIENT)
                SetCursor(m_cursorNormal);
            else
                return DefWindowProc(m_windowHandle, uMsg, wParam, lParam);
        break;

        case WM_SIZE:
            OnSize();
        break;

        case WM_SIZING:
            OnSizing();
        break;

        default:
            return DefWindowProc(m_windowHandle, uMsg, wParam, lParam);
    }

    return 0;
}

//=============================================================================
LRESULT CALLBACK CWindow::StaticProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
    CWindow * window = (CWindow *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    if (!window)
        return DefWindowProc(hWnd, uMsg, wParam, lParam);

    return window->OnMessage(uMsg, wParam, lParam);
}

//=============================================================================
bool CWindow::Update ()
{
    if( !m_windowHandle )
        return false;

    for( ;; )
    {
        MSG uMsg;
        if( !PeekMessage(&uMsg, m_windowHandle, 0, 0, PM_REMOVE) )
            break;

        TranslateMessage(&uMsg);
        DispatchMessage(&uMsg);
    }

    return !m_flags.Test(FLAG_CLOSE);
}

//=============================================================================
bool CWindow::UpdateBlocking () 
{
    if( !m_windowHandle )
        return false;

    MSG uMsg;
    if( GetMessage(&uMsg, m_windowHandle, 0, 0) == 0 )
        return false;

    TranslateMessage(&uMsg);
    DispatchMessage(&uMsg);

    return !m_flags.Test(FLAG_CLOSE);
}

//=============================================================================
void CWindow::OnActivate (bool) 
{
}

//=============================================================================
void CWindow::OnClose () 
{ 
    m_flags.Set(FLAG_CLOSE); 
}

//=============================================================================
void CWindow::OnGetMinMaxInfo (MINMAXINFO * info)
{
    info->ptMinTrackSize.x = 200;
    info->ptMinTrackSize.y = 150;
}

//=============================================================================
void CWindow::OnKeyDown (uint8 vk) 
{
    const EKey key = FindKey(vk);
    m_notify.Call(&CWindowNotify::OnWindowKeyDown, key);
}

//=============================================================================
void CWindow::OnKeyUp (uint8 vk) 
{
    const EKey key = FindKey(vk);
    m_notify.Call(&CWindowNotify::OnWindowKeyUp, key);
}

//=============================================================================
void CWindow::OnMouseDown (uint8 button, const Point2s & pos)
{
    if (m_mouseDown.NoneSet())
        SetCapture(m_windowHandle);

    m_mouseDown.SetBit(button);

    m_notify.Call(&CWindowNotify::OnWindowMouseDown, EMouse(button), pos);
}

//=============================================================================
void CWindow::OnMouseUp (uint8 button, const Point2s & pos)
{
    m_notify.Call(&CWindowNotify::OnWindowMouseUp, EMouse(button), pos);

    m_mouseDown.ClearBit(button);

    if (m_mouseDown.NoneSet())
        ReleaseCapture();
}

//=============================================================================
void CWindow::OnMouseMove (const Point2s & pos) 
{
    m_notify.Call(&CWindowNotify::OnWindowMouseMove, pos);
}

//=============================================================================
void CWindow::OnMouseWheel (sint32 ticks, const Point2s & pos)
{
    m_notify.Call(&CWindowNotify::OnWindowMouseWheel, ticks, pos);
}

//=============================================================================
void CWindow::OnMoving () 
{
}

//=============================================================================
void CWindow::OnPaint (HDC hDc) 
{

}

//=============================================================================
void CWindow::OnSize () 
{
    const Vector2u & screenSize = GetClientSize();
    m_notify.Call(&CWindowNotify::OnWindowSize, screenSize);

}

//=============================================================================
void CWindow::OnSizing () 
{
}


//=============================================================================
//
// API Functions
//
//=============================================================================

//=============================================================================
IWindow * WindowCreate (const CString & title, uint width, uint height)
{
    CWindow * window = new CWindow(title, width, height);

    s_manager.SetMainWindow(window);

    return window;
}

//=============================================================================
void WindowDestroy (IWindow * w)
{
    CWindow * window = CWindow::From(w);

    if (window == s_manager.GetMainWindow())
        s_manager.SetMainWindow(null);

    delete window;
}

//=============================================================================
IWindow * GetWindow ()
{
    return s_manager.GetMainWindow();
}

//=============================================================================
//
// CWindowNotify
//
//=============================================================================

//=============================================================================
void CWindowNotify::OnWindowKeyDown(EKey) {}
void CWindowNotify::OnWindowKeyUp(EKey) {}
void CWindowNotify::OnWindowMouseDown(EMouse, const Point2s &) {}
void CWindowNotify::OnWindowMouseUp(EMouse, const Point2s &) {}
void CWindowNotify::OnWindowMouseWheel (sint32, const Point2s &) {}
void CWindowNotify::OnWindowMouseMove (const Point2s &) {}
void CWindowNotify::OnWindowPaint(void *) {}
void CWindowNotify::OnWindowSize (const Vector2u & size) {}



//=============================================================================
//
// Exported Functions
//
//=============================================================================

//=============================================================================
Point2 CursorGetPos (System::IWindow * window)
{
    POINT p;
    GetCursorPos(&p);

    ScreenToClient((HWND)window->GetHwnd(), &p);

    return Point2(float32(p.x), float32(p.y));
}


} // namespace System