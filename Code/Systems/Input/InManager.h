

class CManager :
    public IInputManager,
    public System::CWindowNotify
{
public:

    CManager ();
    ~CManager ();

public: // Static

    static CManager s_manager;
    static CManager * Get () { return &s_manager; }

private: // IInputManager

    void Initialize (System::IWindow * window) override;
    void Uninitialize () override;
    void Update () override;

    void NotifyRegister (CInputNotify * target) override;
    void NotifyUnregister (CInputNotify * target) override;

    bool KeyIsDown (EKey key) override;
    bool KeyIsUp (EKey key) override;

    bool MouseIsDown (EMouse mouse) override;
    bool MouseIsUp (EMouse mouse) override;
    const Point2 & MousePos () override;

    float32 GetAxis (EGameAxis axis) override;

private: // System::CWindowNotify

    void OnWindowKeyDown (EKey key);
    void OnWindowKeyUp (EKey key);
    void OnWindowMouseDown (EMouse button, const Point2s & pos);
    void OnWindowMouseUp (EMouse button, const Point2s & pos);
    void OnWindowMouseWheel (sint32 ticks, const Point2s & pos);
    void OnWindowMouseMove (const Point2s & pos);

private:

    // Types
    typedef TNotifier<CInputNotify> CNotifier;

    struct Gamepad
    {
        bool    isAvailable;
        float32 axis[int(EGameAxis::Max)];
        bool    button[int(EButton::Max)];
    };

    // Data
    System::IWindow * m_window;
    bool        m_keys[int(EKey::Max)];
    bool        m_mouse[int(EMouse::Max)];
    Point2      m_mousePos;
    Gamepad     m_gamepad;
    CNotifier   m_notifier;

    // Helpers
    void Update(EButton button, bool curr);
};
