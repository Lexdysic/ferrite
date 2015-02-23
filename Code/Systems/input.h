
#ifndef SYSTEMS_INPUT_H
#define SYSTEMS_INPUT_H

#include "Utilities/Notifier.h"
#include "Systems/Entity.h"


//=============================================================================
//
// Constants
//
//=============================================================================

enum class EKey
{
    Escape,

    Left,
    Up,
    Right,
    Down,

    Insert,
    Delete,
    Home,
    End,
    PageUp,
    PageDown,

    Space,

    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,

    Num0,
    Num1,
    Num2,
    Num3,
    Num4,
    Num5,
    Num6,
    Num7,
    Num8,
    Num9,

    NumPad0,
    NumPad1,
    NumPad2,
    NumPad3,
    NumPad4,
    NumPad5,
    NumPad6,
    NumPad7,
    NumPad8,
    NumPad9,

    NumPadMultply,
    NumPadDivide,
    NumPadAdd,
    NumPadSubtract,
    NumPadEnter,
    NumPadDelete,

    F1,
    F2,
    F3,
    F4,

    F5,
    F6,
    F7,
    F8,

    F9,
    F10,
    F11,
    F12,

    Unknown,
    Max
};

enum class EMouse
{
    Primary   = 1,
    Secondary = 2,
    Middle    = 4,
    Thumb1    = 8,
    Thumb2    = 16,
    Max       = 32
};

enum class EButton
{
    LeftShoulder,
    LeftTrigger,
    LeftStick,

    RightShoulder,
    RightTrigger,
    RightStick,

    LeftDpadUp,
    LeftDpadRight,
    LeftDpadDown,
    LeftDpadLeft,

    RightDpadUp,
    RightDpadRight,
    RightDpadDown,
    RightDpadLeft,

    CenterLeft,
    CenterMiddle,
    CenterRight,

    Max,

    Unknown,
};

enum class EGameAxis
{
    LeftStickX,
    LeftStickY,
    LeftTrigger,

    RightStickX,
    RightStickY,
    RightTrigger,

    Max,
    Unknown,
};

enum class EGameStick
{
    Left,
    Right,

    Max,
    Unknown
};


//=============================================================================
//
// Forwards
//
//=============================================================================

interface IInputManager;
struct CInputNotify;
interface IInputComponent;

namespace System
{
    interface IWindow;
}


//=============================================================================
//
// IInputManager
//
//=============================================================================

interface IInputManager
{
    virtual void Initialize (System::IWindow * window) pure;
    virtual void Uninitialize () pure;
    virtual void Update () pure;

    virtual void NotifyRegister (CInputNotify * target) pure;
    virtual void NotifyUnregister (CInputNotify * target) pure;

    virtual bool KeyIsDown (EKey key) pure;
    virtual bool KeyIsUp (EKey key) pure;

    virtual bool MouseIsDown (EMouse mouse) pure;
    virtual bool MouseIsUp (EMouse mouse) pure;
    virtual const Point2 & MousePos () pure;

    virtual float32 GetAxis(EGameAxis axis) pure;
};

IInputManager * InputGetManager ();


//=============================================================================
//
// CInputNotify
//
//=============================================================================

struct CInputNotify : TNotifyTarget<CInputNotify>
{
    virtual void OnInputKeyDown (EKey key);
    virtual void OnInputKeyUp (EKey key);

    virtual void OnInputMouseDown (EMouse key);
    virtual void OnInputMouseUp (EMouse key);
    virtual void OnInputMouseMove (const Point2 & pos);

    virtual void OnInputGamepadDown(EButton button);
    virtual void OnInputGamepadUp(EButton button);
    //virtual void OnInputGamepadAxisChange(EGameAxis axis, float value);

};


//=============================================================================
//
// IInputComponent
//
//=============================================================================

interface IInputComponent : IComponent
{
    static const ComponentType TYPE;
    static IInputComponent * Attach (IEntity * entity);

    // TODO: Controller data
};

#endif // SYSTEMS_INPUT_H