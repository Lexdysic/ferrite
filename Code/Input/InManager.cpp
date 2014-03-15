#include "InPch.h"

#pragma comment(lib, "Xinput9_1_0.lib")

//=============================================================================
float32 MapTrigger(BYTE value)
{
    return value / 255.0f;
}

//=============================================================================
float32 MapStick(SHORT value)
{
    const sint MIN = -32768;
    const sint MAX = 32767;
    const sint DEAD_ZONE = 5000;

    if (Abs(value) < DEAD_ZONE)
        value = 0;

    const float32 t = InvLerp(float32(value), float32(MIN), float32(MAX));
    const float32 axis = Lerp(-1.0f, 1.0f, t);
    return axis;
}

//=============================================================================
bool MapButton(WORD buttons, WORD flag)
{
    return (buttons & flag) != 0;
}




//=============================================================================
//
// CManager
//
//=============================================================================
CManager CManager::s_manager;

//=============================================================================
CManager::CManager ()
{
    MemZero(m_keys);
    MemZero(m_mouse);
}

//=============================================================================
CManager::~CManager ()
{

}

//=============================================================================
void CManager::Initialize (System::IWindow * window)
{
    m_window = window;
    m_window->NotifyRegister(this);
}

//=============================================================================
void CManager::Uninitialize ()
{
    m_window->NotifyUnregister(this);
}

//=============================================================================
void CManager::Update ()
{
    //byte newKeyState[256];
    //::GetKeyboardState(newKeyState);

    //for (uint i = 8; i < array_size(newKeyState); ++i)
    //{
    //    const bool newState = newKeyState[i] != 0;
    //    const bool oldState = m_keys[i] != 0;
    //    if (newState == oldState)
    //        continue;

    //    const EKey key = (EKey)i;
    //    m_keys[i] = newState;
    //    if (newState)
    //        m_notifier.Call(&CInputNotify::OnInputKeyDown, key);
    //    else
    //        m_notifier.Call(&CInputNotify::OnInputKeyUp, key);
    //}

    {
        XINPUT_STATE state;
        MemZero(state);
        const DWORD result = ::XInputGetState(0, &state);
        
        if (result == ERROR_SUCCESS)
        {
            m_gamepad.isAvailable = true;

            m_gamepad.axis[int(EGameAxis::LeftStickX)] = MapStick(state.Gamepad.sThumbLX);
            m_gamepad.axis[int(EGameAxis::LeftStickY)] = MapStick(state.Gamepad.sThumbLY);
            m_gamepad.axis[int(EGameAxis::LeftTrigger)] = MapTrigger(state.Gamepad.bLeftTrigger);

            m_gamepad.axis[int(EGameAxis::RightStickX)] = MapStick(state.Gamepad.sThumbRX);
            m_gamepad.axis[int(EGameAxis::RightStickY)] = MapStick(state.Gamepad.sThumbRY);
            m_gamepad.axis[int(EGameAxis::RightTrigger)] = MapTrigger(state.Gamepad.bRightTrigger);

            Update(EButton::LeftDpadUp, MapButton(state.Gamepad.wButtons, XINPUT_GAMEPAD_DPAD_UP));
            Update(EButton::LeftDpadUp, MapButton(state.Gamepad.wButtons, XINPUT_GAMEPAD_DPAD_UP));
            Update(EButton::LeftDpadRight, MapButton(state.Gamepad.wButtons, XINPUT_GAMEPAD_DPAD_RIGHT));
            Update(EButton::LeftDpadDown, MapButton(state.Gamepad.wButtons, XINPUT_GAMEPAD_DPAD_DOWN));
            Update(EButton::LeftDpadLeft, MapButton(state.Gamepad.wButtons, XINPUT_GAMEPAD_DPAD_LEFT));
            Update(EButton::LeftStick, MapButton(state.Gamepad.wButtons, XINPUT_GAMEPAD_LEFT_THUMB));
            Update(EButton::LeftShoulder, MapButton(state.Gamepad.wButtons, XINPUT_GAMEPAD_LEFT_SHOULDER));
            Update(EButton::LeftTrigger, (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD));

            Update(EButton::RightDpadUp, MapButton(state.Gamepad.wButtons, XINPUT_GAMEPAD_Y));
            Update(EButton::RightDpadRight, MapButton(state.Gamepad.wButtons, XINPUT_GAMEPAD_X));
            Update(EButton::RightDpadDown, MapButton(state.Gamepad.wButtons, XINPUT_GAMEPAD_A));
            Update(EButton::RightDpadLeft, MapButton(state.Gamepad.wButtons, XINPUT_GAMEPAD_B));
            Update(EButton::RightStick, MapButton(state.Gamepad.wButtons, XINPUT_GAMEPAD_RIGHT_THUMB));
            Update(EButton::RightShoulder, MapButton(state.Gamepad.wButtons, XINPUT_GAMEPAD_RIGHT_SHOULDER));
            Update(EButton::RightTrigger, (state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD));

            Update(EButton::CenterLeft, MapButton(state.Gamepad.wButtons, XINPUT_GAMEPAD_BACK));
            Update(EButton::CenterMiddle, false);
            Update(EButton::CenterRight, MapButton(state.Gamepad.wButtons, XINPUT_GAMEPAD_START));
        }
        else
        {
            MemZero(m_gamepad);
        }
    }
}

//=============================================================================
void CManager::Update (EButton button, bool curr)
{
    const uint index = uint(button);
    const bool prev = m_gamepad.button[index];
    m_gamepad.button[index] = curr;

    if (curr != prev)
    {
        if (curr)
            m_notifier.Call(&CInputNotify::OnInputGamepadDown, button);
        else
            m_notifier.Call(&CInputNotify::OnInputGamepadUp, button);
    }
}

//=============================================================================
void CManager::NotifyRegister (CInputNotify * target)
{
    m_notifier.Add(target);
}

//=============================================================================
void CManager::NotifyUnregister (CInputNotify * target)
{
    m_notifier.Remove(target);
}

//=============================================================================
bool CManager::KeyIsDown (EKey key)
{
    return m_keys[int(key)];
}

//=============================================================================
bool CManager::KeyIsUp (EKey key)
{
    return !m_keys[int(key)];
}

//=============================================================================
bool CManager::MouseIsDown (EMouse mouse)
{
    return m_mouse[int(mouse)];
}

//=============================================================================
bool CManager::MouseIsUp (EMouse mouse)
{
    return !m_mouse[int(mouse)];
}

//=============================================================================
const Point2 & CManager::MousePos ()
{
    return m_mousePos;
}

//=============================================================================
float32 CManager::GetAxis(EGameAxis axis)
{
    return m_gamepad.axis[int(axis)];
}

//=============================================================================
void CManager::OnWindowKeyDown (EKey key)
{
    const unsigned index = int(key);
    if (m_keys[index])
        return;

    m_keys[index] = true;
    m_notifier.Call(&CInputNotify::OnInputKeyDown, key);
}

//=============================================================================
void CManager::OnWindowKeyUp (EKey key)
{
    const unsigned index = int(key);
    if (!m_keys[index])
        return;

    m_keys[index] = false;
    m_notifier.Call(&CInputNotify::OnInputKeyUp, key);
}

//=============================================================================
void CManager::OnWindowMouseDown (EMouse button, const Point2s & pos)
{
    m_mouse[int(button)] = true;
    m_notifier.Call(&CInputNotify::OnInputMouseDown, button);
}

//=============================================================================
void CManager::OnWindowMouseUp (EMouse button, const Point2s & pos)
{
    m_mouse[int(button)] = false;
    m_notifier.Call(&CInputNotify::OnInputMouseUp, button);
}

//=============================================================================
void CManager::OnWindowMouseWheel (sint32 ticks, const Point2s & pos)
{

}

//=============================================================================
void CManager::OnWindowMouseMove (const Point2s & pos)
{

}



//=============================================================================
//
// API Functions
//
//=============================================================================

//=============================================================================
IInputManager * InputGetManager ()
{
    return CManager::Get();
}




//=============================================================================
//
// CInputNotify
//
//=============================================================================

void CInputNotify::OnInputKeyDown (EKey) {}
void CInputNotify::OnInputKeyUp (EKey) {}
void CInputNotify::OnInputMouseDown (EMouse) {}
void CInputNotify::OnInputMouseUp (EMouse) {}
void CInputNotify::OnInputMouseMove (const Point2 &) {}
void CInputNotify::OnInputGamepadDown(EButton) {}
void CInputNotify::OnInputGamepadUp(EButton) {}