
//=============================================================================
//
// TSmartPtrBase
//
//=============================================================================

namespace Pointer {
namespace Private {

//=============================================================================
template <typename T>
TSmartPtrBase<T>::TSmartPtrBase () :
    m_ptr(null)
{
}

//=============================================================================
template <typename T>
TSmartPtrBase<T>::TSmartPtrBase (T * data) :
    m_ptr(data)
{
}

//=============================================================================
template <typename T>
TSmartPtrBase<T>::~TSmartPtrBase ()
{
    ASSERT(m_ptr == null);
}

//=============================================================================
template <typename T>
T & TSmartPtrBase<T>::operator* ()
{
    return *m_ptr;
}

//=============================================================================
template <typename T>
T * TSmartPtrBase<T>::operator-> ()
{
    return m_ptr;
}

//=============================================================================
template <typename T>
TSmartPtrBase<T>::operator bool ()
{
    return m_ptr != null;
}

//=============================================================================
template <typename T>
TSmartPtrBase<T>::operator T * ()
{
    return m_ptr;
}

//=============================================================================
template <typename T>
TSmartPtrBase<T>::operator const T * ()
{
    return m_ptr;
}

//=============================================================================
template <typename T>
TSmartPtrBase<T>::operator const T * () const
{
    return m_ptr;
}

}} // namespace Pointer::Private



//=============================================================================
//
// TStrongPtr
//
//=============================================================================

//=============================================================================
template <typename T>
TStrongPtr<T>::TStrongPtr () :
    m_ptr(null)
{
}

//=============================================================================
template <typename T>
TStrongPtr<T>::TStrongPtr (T * rhs) :
    Pointer::Private::TSmartPtrBase<T>(rhs)
{
    IncRef();
}

//=============================================================================
template <typename T>
TStrongPtr<T>::TStrongPtr (const TStrongPtr<T> & rhs) :
    Pointer::Private::TSmartPtrBase<T>(rhs.m_ptr)
{
    IncRef();
}

//=============================================================================
template <typename T>
TStrongPtr<T>::~TStrongPtr ()
{
    DecRef();
    m_ptr = null;
}

//=============================================================================
template <typename T>
const TStrongPtr<T> & TStrongPtr<T>::operator= (const TStrongPtr<T> & rhs)
{
    DecRef();

    m_ptr = rhs.m_ptr;

    IncRef();

    return *this;
}

//=============================================================================
template <typename T>
const TStrongPtr<T> & TStrongPtr<T>::operator= (const nullptr_t & rhs)
{
    DecRef();

    m_ptr = null;

    return *this;
}

//=============================================================================
template <typename T>
void TStrongPtr<T>::IncRef ()
{
    if (m_ptr)
        m_ptr->_SmartPtrGetData()->IncRef();
}

//=============================================================================
template <typename T>
void TStrongPtr<T>::DecRef ()
{
    if (!m_ptr)
        return;

    const uint refCount = m_ptr->_SmartPtrGetData()->DecRef();
    if (!refCount)
    {
        m_ptr->_SmartPtrDestroy();
        m_ptr = null;
    }
}



//=============================================================================
//
// TWeakPtr
//
//=============================================================================

//=============================================================================
template <typename T>
TWeakPtr<T>::TWeakPtr ()
{
}

//=============================================================================
template <typename T>
TWeakPtr<T>::TWeakPtr (const TWeakPtr<T> & rhs) :
    Pointer::Private::TSmartPtrBase<T>(rhs.m_ptr)
{
    if (m_ptr)
        m_ptr->_SmartPtrGetData()->AddWeak(this);
}

//=============================================================================
template <typename T>
TWeakPtr<T>::TWeakPtr (const TStrongPtr<T> & rhs) :
    Pointer::Private::TSmartPtrBase<T>(rhs.m_ptr)
{
    if (m_ptr)
        m_ptr->_SmartPtrGetData()->AddWeak(this);
}

//=============================================================================
template <typename T>
TWeakPtr<T>::TWeakPtr (T * data) :
    Pointer::Private::TSmartPtrBase<T>(data)
{
    if (m_ptr)
        m_ptr->_SmartPtrGetData()->AddWeak(this);
}

//=============================================================================
template <typename T>
TWeakPtr<T>::~TWeakPtr ()
{
    m_ptr = null;
}

//=============================================================================
template <typename T>
TWeakPtr<T> & TWeakPtr<T>::operator= (const TWeakPtr<T> & rhs)
{
    m_link.Unlink();

    m_ptr = rhs.m_ptr;

    if (m_ptr)
        m_ptr->_SmartPtrGetData()->AddWeak(this);

    return *this;
}

//=============================================================================
template <typename T>
void TWeakPtr<T>::OnObjectDestroyed ()
{
    m_ptr = null;
}





//=============================================================================
//
// TSmartPtrData
//
//=============================================================================

//=============================================================================
template <typename T>
TSmartPtrData<T>::TSmartPtrData () :
    m_refCount(0)
{
}

//=============================================================================
template <typename T>
TSmartPtrData<T>::~TSmartPtrData ()
{
    for (auto weak : m_weaklist)
    {
        weak->OnObjectDestroyed();
    }

    ASSERT(m_refCount == 0);
}

//=============================================================================
template <typename T>
void TSmartPtrData<T>::IncRef ()
{
    m_refCount++;
}

//=============================================================================
template <typename T>
uint TSmartPtrData<T>::DecRef ()
{
    ASSERT(m_refCount != 0);
    return --m_refCount;
}

//=============================================================================
template <typename T>
void TSmartPtrData<T>::AddWeak (TWeakPtr<T> * weak)
{
    m_weaklist.InsertTail(weak);
}





//=============================================================================
//
// TRefCounted
//
//=============================================================================

//=============================================================================
template <typename T>
TRefCounted<T>::TRefCounted ()
{
}

//=============================================================================
template <typename T>
TRefCounted<T>::~TRefCounted ()
{

}

//=============================================================================
template <typename T>
TSmartPtrData<T> * TRefCounted<T>::_SmartPtrGetData ()
{
    return &m_data;
}


//=============================================================================
template <typename T>
void TRefCounted<T>::_SmartPtrDestroy ()
{
    delete this;
}