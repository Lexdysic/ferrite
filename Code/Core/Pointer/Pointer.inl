
//=============================================================================
//
// SmartPtrBase
//
//=============================================================================

namespace Private
{

//=============================================================================
template <typename T>
SmartPtrBase<T>::SmartPtrBase () :
    m_data(null)
{
}

//=============================================================================
template <typename T>
SmartPtrBase<T>::SmartPtrBase (T * data) :
    m_data(data)
{
}

//=============================================================================
template <typename T>
SmartPtrBase<T>::~SmartPtrBase ()
{
    // TODO: assert that m_data == null
}

//=============================================================================
template <typename T>
T & SmartPtrBase<T>::operator* ()
{
    return *m_data;
}

//=============================================================================
template <typename T>
T * SmartPtrBase<T>::operator-> ()
{
    return m_data;
}

//=============================================================================
template <typename T>
SmartPtrBase<T>::operator bool ()
{
    return m_data != null;
}

//=============================================================================
template <typename T>
SmartPtrBase<T>::operator T * ()
{
    return m_data;
}

//=============================================================================
template <typename T>
SmartPtrBase<T>::operator const T * ()
{
    return m_data;
}

//=============================================================================
template <typename T>
SmartPtrBase<T>::operator const T * () const
{
    return m_data;
}

} // namespace Private



//=============================================================================
//
// StrongPtr
//
//=============================================================================

//=============================================================================
template <typename T>
StrongPtr<T>::StrongPtr ()
{
}

//=============================================================================
template <typename T>
StrongPtr<T>::StrongPtr (T * rhs) :
    Private::SmartPtrBase<T>(rhs)
{
    IncRef();
}

//=============================================================================
template <typename T>
StrongPtr<T>::StrongPtr (const StrongPtr<T> & rhs) :
    Private::SmartPtrBase<T>(rhs.m_data)
{
    IncRef();
}

//=============================================================================
template <typename T>
StrongPtr<T>::~StrongPtr ()
{
    DecRef();
}

//=============================================================================
template <typename T>
const StrongPtr<T> & StrongPtr<T>::operator= (const StrongPtr<T> & rhs)
{
    DecRef();

    m_data = rhs.m_data;

    IncRef();

    return *this;
}

//=============================================================================
template <typename T>
const StrongPtr<T> & StrongPtr<T>::operator= (const nullptr_t & rhs)
{
    DecRef();

    m_data = null;

    return *this;
}

//=============================================================================
template <typename T>
void StrongPtr<T>::IncRef ()
{
    if (m_data)
        m_data->GetRefCountData()->IncRef();
}

//=============================================================================
template <typename T>
void StrongPtr<T>::DecRef ()
{
    if (m_data)
    {
        const uint refCount = m_data->GetRefCountData()->DecRef();
        if (!refCount)
            delete m_data;
    }
}



//=============================================================================
//
// WeakPtr
//
//=============================================================================

//=============================================================================
template <typename T>
WeakPtr<T>::WeakPtr ()
{
}

//=============================================================================
template <typename T>
WeakPtr<T>::WeakPtr (const WeakPtr<T> & rhs) :
    Private::SmartPtrBase<T>(rhs.m_data)
{
    if (m_data)
        m_data->GetRefCountData()->m_weak.InsertTail(this);
}

//=============================================================================
template <typename T>
WeakPtr<T>::WeakPtr (T * data) :
    Private::SmartPtrBase<T>(data)
{
    if (m_data)
        m_data->GetRefCountData()->m_weak.InsertTail(this);
}

//=============================================================================
template <typename T>
WeakPtr<T> & WeakPtr<T>::operator= (const WeakPtr<T> & rhs)
{
    m_link.Unlink();

    m_data = rhs.m_data;

    if (m_data)
        m_data->GetRefCountData()->m_weak.InsertTail(this);

    return *this;
}

//=============================================================================
template <typename T>
void WeakPtr<T>::OnDestroy ()
{
    m_data = null;
}





//=============================================================================
//
// SmartPtrData
//
//=============================================================================

//=============================================================================
template <typename T>
SmartPtrData<T>::SmartPtrData () :
    m_refCount(0)
{
}

//=============================================================================
template <typename T>
SmartPtrData<T>::~SmartPtrData ()
{
    for (auto weak : m_weak)
    {
        weak->OnDestroy();
    }

    ASSERT(m_refCount == 0);
}

//=============================================================================
template <typename T>
void SmartPtrData<T>::IncRef ()
{
    m_refCount++;
}

//=============================================================================
template <typename T>
uint SmartPtrData<T>::DecRef ()
{
    ASSERT(m_refCount != 0);
    return --m_refCount;
}





//=============================================================================
//
// CRefCounted
//
//=============================================================================

//=============================================================================
template <typename T>
CRefCounted<T>::CRefCounted () :
    m_refCount(0)
{
}

//=============================================================================
template <typename T>
CRefCounted<T>::~CRefCounted ()
{
    for (auto weak : m_weak)
    {
        weak->OnDestroy();
    }

    ASSERT(m_refCount == 0);
}

//=============================================================================
template <typename T>
void CRefCounted<T>::IncRef ()
{
    m_refCount++;
}

//=============================================================================
template <typename T>
uint CRefCounted<T>::DecRef ()
{
    ASSERT(m_refCount != 0);
    return --m_refCount;
}

//=============================================================================
template <typename T>
CRefCounted<T> * CRefCounted<T>::GetRefCountData ()
{
    return this;
}