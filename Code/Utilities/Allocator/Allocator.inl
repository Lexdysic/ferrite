
//=============================================================================
template <typename T, uint S>
TBlockAllocator<T, S>::TBlockAllocator () :
    m_blockList(NULL),
    m_objList(NULL)
#ifdef BLOCK_ALLOCATOR_VALIDATE
    ,m_allocCount(0)
#endif
{
}

//=============================================================================
template <typename T, uint S>
TBlockAllocator<T, S>::~TBlockAllocator ()
{
#ifdef BLOCK_ALLOCATOR_VALIDATE
    ASSERT(m_allocCount == 0);
#endif

    Clear();
}

//=============================================================================
template <typename T, uint S>
void * TBlockAllocator<T, S>::New ()
{
    if (!m_objList)
        Grow();

    void * obj = m_objList;
    m_objList = m_objList->next;

#ifdef BLOCK_ALLOCATOR_VALIDATE
    m_allocCount++;
#endif

    return obj;//new(obj) T();
}

//=============================================================================
template <typename T, uint S>
void TBlockAllocator<T, S>::Delete (void * obj)
{
    //obj->~T();

    FreeObj * freeObj = static_cast<FreeObj *>(obj);

    freeObj->next = m_objList;
    m_objList     = freeObj;

#ifdef BLOCK_ALLOCATOR_VALIDATE
    m_allocCount--;
#endif
}

//=============================================================================
template <typename T, uint S>
void TBlockAllocator<T, S>::Clear ()
{
    for (Block * next; m_blockList; m_blockList = next)
    {
        next = m_blockList->next;
        delete m_blockList;
    }
}

//=============================================================================
template <typename T, uint S>
void TBlockAllocator<T, S>::Grow ()
{
    Block * block = new Block();
    block->next = m_blockList;
    m_blockList = block;

    // Link in all the new free objects to the free list
    T * ptr = (T *)block->objects;
    T * term = ptr + S;
    for ( ; ptr < term; ++ptr) 
    {
        FreeObj * freeObj = (FreeObj *)(ptr);

        freeObj->next = m_objList;
        m_objList = freeObj;
    }

}