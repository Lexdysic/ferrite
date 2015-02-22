#ifndef SYSTEMS_WINDOW_H
#define SYSTEMS_WINDOW_H

#include "Utilities\Notifier\Notifier.h"
#include "Systems\Input\Input.h"


enum class EKey;
enum class EMouse;

namespace System 
{

interface IWindow;
interface CWindowNotify;



//=============================================================================
//
// IWindow
//
//============================================================================

interface IWindow
{
    // Commands
    virtual bool Update () pure;
    virtual bool UpdateBlocking () pure;
    virtual void Invalidate () const pure;
    virtual void SetTitle (const CString & title) pure;

    // Query
    virtual Vector2u GetClientSize () const pure;
    virtual void * GetHwnd () const pure;

    // Notify
    virtual void NotifyRegister (CWindowNotify * notify) pure;
    virtual void NotifyUnregister (CWindowNotify * notify) pure;
};



//=============================================================================
//
// CWindowNotify
//
//============================================================================

struct CWindowNotify : TNotifyTarget<CWindowNotify>
{
    //virtual void OnWindowClose ();
    virtual void OnWindowKeyDown (EKey key);
    virtual void OnWindowKeyUp (EKey key);
    virtual void OnWindowMouseDown (EMouse button, const Point2s & pos);
    virtual void OnWindowMouseUp (EMouse button, const Point2s & pos);
    virtual void OnWindowMouseWheel (sint32 ticks, const Point2s & pos);
    virtual void OnWindowMouseMove (const Point2s & pos);
    virtual void OnWindowPaint (void * g);
    virtual void OnWindowSize (const Vector2u & size);
};

IWindow * WindowCreate (const CString & title, uint width, uint height);
void WindowDestroy (IWindow * window);

IWindow * GetWindow ();



//=============================================================================
//
// Helper Functions
//
//============================================================================

Point2 CursorGetPos (System::IWindow * window);

} // namespace System

#endif // SYSTEMS_WINDOW_H