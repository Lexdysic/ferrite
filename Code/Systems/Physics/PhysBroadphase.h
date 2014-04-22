namespace Physics
{

class CBroadphase
{
public:

    TArray<CColliderComponent *> Find (const Circle & cirle, Flags32 group);
    TArray<CColliderComponent *> Find (const Aabb2 & box, Flags32 group);

    void Add (CColliderComponent * collider);
    void Remove (CColliderComponent * collider);
    void Update (CColliderComponent * collider);
    //void Get (CColliderComponent * collider);

private:

    typedef LIST_DECLARE(CColliderComponent, m_linkBroadphase) ColliderList;

    ColliderList m_colliders;
};

} // namespace Physics