#ifdef BUILD_DEBUG
#   define BLOCK_ALLOCATOR_VALIDATE
#endif

template <typename T, uint Size = 16>
class TBlockAllocator
{
public:
    TBlockAllocator ();
    ~TBlockAllocator ();

    void * New ();
    void   Delete (void * obj);
    void   Clear ();
	
private:
    static const uint BLOCK_BYTES = sizeof(T) * Size;

    struct FreeObj
    {
        FreeObj * next;
    };

    struct Block
    {
        Block * next;
        uint8   objects[BLOCK_BYTES];
    };

    Block   * m_blockList;
    FreeObj * m_objList;
#ifdef BLOCK_ALLOCATOR_VALIDATE
    uint      m_allocCount;
#endif

    void Grow ();

    static_assert(sizeof(T) >= sizeof(FreeObj), "Cannot use block allocators on small types");
};

#include "Allocator.inl"