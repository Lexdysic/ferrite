
//=============================================================================
template <typename T, uint C>
TBlockAllocator<T, C>::TBlockAllocator ()
{
}

//=============================================================================
template <typename T, uint C>
TBlockAllocator<T, C>::~TBlockAllocator ()
{
#ifdef BLOCK_ALLOCATOR_VALIDATE
    ASSERT(m_allocCount == 0);
#endif

    Clear();
}

//=============================================================================
template <typename T, uint C>
template <typename... Args>
T * TBlockAllocator<T, C>::New (const Args &... args)
{
    void * obj = New();

    return new(obj) T(args...);
}

//=============================================================================
template <typename T, uint C>
void TBlockAllocator<T, C>::Delete (T * obj)
{
    obj->~T();

    Delete(obj);
}

//=============================================================================
template <typename T, uint C>
void * TBlockAllocator<T, C>::Alloc ()
{
    if (!m_objList)
        Grow();

    void * obj = m_objList;
    m_objList = m_objList->next;

#ifdef BLOCK_ALLOCATOR_VALIDATE
    m_allocCount++;
#endif

    return obj;
}

//=============================================================================
template <typename T, uint C>
void TBlockAllocator<T, C>::Free (void * obj)
{
    FreeObj * freeObj = static_cast<FreeObj *>(obj);

    freeObj->next = m_objList;
    m_objList     = freeObj;

#ifdef BLOCK_ALLOCATOR_VALIDATE
    ASSERT(m_allocCount > 0); // Double delete?
    m_allocCount--;
#endif
}

//=============================================================================
template <typename T, uint C>
void TBlockAllocator<T, C>::Clear ()
{
    for (Block * next; m_blockList; m_blockList = next)
    {
        next = m_blockList->next;
        delete m_blockList;
    }
}

//=============================================================================
template <typename T, uint C>
void TBlockAllocator<T, C>::Grow ()
{
    Block * block = new Block();
    block->next = m_blockList;
    m_blockList = block;

    // Link in all the new free objects to the free list
    T * ptr = (T *)block->objects;
    T * term = ptr + C;
    for ( ; ptr < term; ++ptr) 
    {
        FreeObj * freeObj = (FreeObj *)(ptr);

        freeObj->next = m_objList;
        m_objList = freeObj;
    }
}