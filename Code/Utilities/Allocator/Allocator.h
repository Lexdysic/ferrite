#ifdef BUILD_DEBUG
#   define BLOCK_ALLOCATOR_VALIDATE
#endif

template <typename T, uint Count = 16>
class TBlockAllocator
{
public:
    TBlockAllocator ();
    ~TBlockAllocator ();
    
    void * Alloc ();
    void   Free (void * obj);

    template <typename... Args>
    T * New (const Args &... args);
    void   Delete (T * obj);
    void   Clear ();
	
private:
    static const uint BLOCK_BYTES = sizeof(T) * Count;

    struct FreeObj
    {
        FreeObj * next;
    };

    struct Block
    {
        Block * next;
        byte    objects[BLOCK_BYTES];
    };

    Block   * m_blockList = null;
    FreeObj * m_objList = null;
#ifdef BLOCK_ALLOCATOR_VALIDATE
    uint      m_allocCount = 0;
#endif

    void Grow ();

    static_assert(sizeof(T) >= sizeof(FreeObj), "Cannot use block allocators on small types");
};

#include "Allocator.inl"