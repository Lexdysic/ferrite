
//=============================================================================
//
// CEntity
//
//=============================================================================

class CEntity :
    public TRefCounted<IEntity>,
    public IEntity
{
public: // Internal------------------------------------------------------------

    CEntity (EntityId id);
    ~CEntity ();

public: // Statics ------------------------------------------------------------

    static CEntity *       From (IEntity * x)       { return (CEntity *)x; }
    static const CEntity * From (const IEntity * x) { return (CEntity *)x; }

public: // IEntity-------------------------------------------------------------

    EntityId GetId () const override { return m_id; }

    void         Attach (CComponent * pComponent) override;
    void         Detach (CComponent * pComponent) override;

    CComponent * Get (const ComponentType & type) override;
    uint         GetComponentCount () const override;
    CComponent * EnumComponent (uint i) override;

public: // IRefCounted --------------------------------------------------------

    TSmartPtrData<IEntity> * _SmartPtrGetData () override { return TRefCounted::_SmartPtrGetData(); }
    void _SmartPtrDestroy () override { delete this; }

public: // Links --------------------------------------------------------------

    LIST_LINK(CEntity) m_link;

private: //--------------------------------------------------------------------

    // Types
    typedef TDictionary<ComponentType, CComponent *> TypeToComp;

    // Data
    const EntityId    m_id;
    TypeToComp        m_components;
};


typedef TIdManager<TIdDataSerial<EntityId>> EntityIdManager;
