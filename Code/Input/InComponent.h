
//=============================================================================
//
// CInputComponent
//
//=============================================================================

class CInputComponent :
    public IInputComponent,
    public CComponent,
    public CInputNotify
{
public:

    CInputComponent ();
    ~CInputComponent ();
    
private: // IComponent

    ComponentId     GetId () const { return CComponent::GetId(); }
    IEntity *       GetOwner () const override { return CComponent::GetOwner(); }
    ComponentType   GetType () const override { return IInputComponent::TYPE; }

private: // IRigidBodyComponent

public: // Links

    LIST_LINK(CInputComponent) m_link;

private: // 

};
