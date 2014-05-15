
//=============================================================================
//
// Forwards
//
//=============================================================================

template <typename T> class     TWeakPtr;
template <typename T> class     TStrongPtr;
template <typename T> interface IRefCounted;
template <typename T> class     TRefCounted;

namespace Pointer {
namespace Private {
    template <typename T> class TSmartPtrBase;
}} // namespace Pointer::Private



//=============================================================================
//
// TSmartPtrBase
//
//=============================================================================

namespace Pointer {
namespace Private {

template <typename T>
class TSmartPtrBase
{
public:

    TSmartPtrBase ();
    TSmartPtrBase (T * data);
    ~TSmartPtrBase ();

    T & operator* ();
    T * operator-> ();

    operator bool ();
    operator T * ();
    operator const T * ();
    operator const T * () const;

protected:

    T * m_ptr;
};

}} // namespace Pointer::Private



//=============================================================================
//
// TStrongPtr
//
//=============================================================================

template <typename T>
class TStrongPtr :
    public Pointer::Private::TSmartPtrBase<T>
{
    template <typename T>
    friend class TWeakPtr;
public:

    TStrongPtr ();
    TStrongPtr (T * rhs);
    TStrongPtr (const TStrongPtr<T> & rhs);
    ~TStrongPtr ();

    const TStrongPtr<T> & operator= (const TStrongPtr<T> & rhs);
    const TStrongPtr<T> & operator= (const nullptr_t & rhs);

private:

    inline void IncRef ();
    inline void DecRef ();
};



//=============================================================================
//
// TWeakPtr
//
//=============================================================================

template <typename T>
class TWeakPtr :
    public Pointer::Private::TSmartPtrBase<T>
{
    template <typename T>
    friend class TSmartPtrData;
public:

    TWeakPtr ();
    TWeakPtr (const TWeakPtr<T> & rhs);
    TWeakPtr (const TStrongPtr<T> & rhs);
    TWeakPtr (T * data);
    ~TWeakPtr ();

    TWeakPtr<T> & operator= (const TWeakPtr<T> & rhs);

private:
    void OnObjectDestroyed ();

    TLink<TWeakPtr<T>> m_link;
};



//=============================================================================
//
// TSmartPtrData
//
//=============================================================================

template <typename T>
class TSmartPtrData
{
    template <typename T>
    friend class TRefCounted;
public:

    TSmartPtrData ();
    ~TSmartPtrData ();

    void IncRef ();
    uint DecRef ();
    void AddWeak (TWeakPtr<T> * weak);

private:
    // Types
    typedef LIST_DECLARE(TWeakPtr<T>, m_link) WeakList;

    // Data
    WeakList m_weaklist;
    uint     m_refCount;
};



//=============================================================================
//
// IRefCounted
//
//=============================================================================

template <typename T>
interface IRefCounted
{
    virtual TSmartPtrData<T> * _SmartPtrGetData () pure;
    virtual void _SmartPtrDestroy () pure;
};



//=============================================================================
//
// TRefCounted
//
//=============================================================================

template <typename T>
class TRefCounted
{
    template <typename T> friend class TWeakPtr;
    template <typename T> friend class StrongPtr;

public:
    TRefCounted ();
    ~TRefCounted ();

protected: // IRefCounted<T>

    TSmartPtrData<T> * _SmartPtrGetData ();
    void _SmartPtrDestroy ();

private:
    TSmartPtrData<T> m_data;
};


//=============================================================================
#define REFCOUNTED_ADAPTER(interface)                           \                                                    \
    TSmartPtrData<interface> * _SmartPtrGetData () override     \
    {                                                           \
        return TRefCounted<interface>::_SmartPtrGetData();      \
    }                                                           \
                                                                \
    void _SmartPtrDestroy () override                           \
    {                                                           \
        TRefCounted<interface>::_SmartPtrDestroy();             \
    }

#include "Pointer.inl"