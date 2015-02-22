#ifndef SYSTEMS_USERINTERFACE_H
#define SYSTEMS_USERINTERFACE_H

#include "Systems\Input\Input.h"
#include "Basics\Time\Time.h"

namespace System
{
    interface IWindow;
} // namespace System

namespace UserInterface
{


//==================================================================================================
//
// Forward Declare
//
//==================================================================================================
interface IContext;
interface IWidget;


const uint32 FLAG_MOUSE_FOCUS = (1 << 0);
const uint32 FLAG_MOUSE_CLICK = (1 << 1);
const uint32 FLAG_MOUSE_WHEEL = (1 << 2);
const uint32 FLAG_MOUSE_DRAG  = (1 << 3);

const uint32 MASK_MOUSE = FLAG_MOUSE_FOCUS | FLAG_MOUSE_CLICK | FLAG_MOUSE_WHEEL | FLAG_MOUSE_DRAG;


//==================================================================================================
//
// IContext
//
//==================================================================================================
interface IContext
{
    virtual void Initialize (System::IWindow * window) pure;
    virtual void Uninitialize () pure;

    virtual void Update (const Time::Delta deltaTime) pure;
    virtual void Render () pure;
};

IContext * GetContext ();


//==================================================================================================
//
// CWidget
//
//==================================================================================================
class CWidget
{
public:
    CWidget (CWidget * parent);
    virtual ~CWidget ();

    CWidget * GetParent () const;
    void DestroyWidget ();

    // Position
    const Point2 & GetPosition () const;
    void SetPosition (const Point2 & pos);
    // Point2 ConvertToScreen (const Point2 & widgetPos);
    // Point2 ConvertToWidget (const Point2 & screenPos);

    // Size
    Vector2 GetNativeSize ();
    const Vector2 & GetActualSize () const;
    void SetSize (const Vector2 & size);

    void SetMouseEnable (Flags32 mouseFlags);
    void ScheduleLayout ();

    // Notifications
    virtual void OnWidgetGetNativeSize (Vector2 * outSize);
    virtual void OnWidgetLayout (const Point2 & pos, const Vector2 & size);
    virtual void OnWidgetUpdate ();
    virtual void OnWidgetRender (const Point2 & pos, const Vector2 & size);
    virtual void OnWidgetMouseDown (EMouse button, const Point2 & pos);
    virtual void OnWidgetMouseUp (EMouse button, const Point2 & pos);
    virtual void OnWidgetMouseMove (const Point2 & pos);
    virtual void OnWidgetMouseWheel (sint ticks, const Point2 & pos);
    virtual void OnWidgetMouseEnter ();
    virtual void OnWidgetMouseExit ();
};

} // namespace UserInterface

#endif // SYSTEMS_USERINTERFACE_H