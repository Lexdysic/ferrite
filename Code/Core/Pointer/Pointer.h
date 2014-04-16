
//=============================================================================
//
// Forwards
//
//=============================================================================

template <typename T> class WeakPtr;
template <typename T> class StrongPtr;
template <typename T> struct IRefCounted;
template <typename T> class CRefCounted;

namespace Private
{
    template <typename T> class SmartPtrBase;
}


//=============================================================================
//
// SmartPtrBase
//
//=============================================================================

namespace Private
{

template <typename T>
class SmartPtrBase
{
public:

    SmartPtrBase ();
    SmartPtrBase (T * data);
    ~SmartPtrBase ();

    T & operator* ();
    T * operator-> ();

    operator bool ();
    operator T * ();
    operator const T * ();
    operator const T * () const;

protected:

    T * m_data;
};

} // namespace Private



//=============================================================================
//
// StrongPtr
//
//=============================================================================

template <typename T>
class StrongPtr :
    public Private::SmartPtrBase<T>
{
public:

    StrongPtr ();
    StrongPtr (T * rhs);
    StrongPtr (const StrongPtr<T> & rhs);
    ~StrongPtr ();

    const StrongPtr<T> & operator= (const StrongPtr<T> & rhs);
    const StrongPtr<T> & operator= (const nullptr_t & rhs);

private:

    inline void IncRef ();
    inline void DecRef ();
};



//=============================================================================
//
// WeakPtr
//
//=============================================================================

template <typename T>
class WeakPtr :
    public Private::SmartPtrBase<T>
{
    template <typename T>
    friend class CRefCounted;
public:

    WeakPtr ();
    WeakPtr (const WeakPtr & rhs);
    WeakPtr (T * data);

    WeakPtr<T> & operator= (const WeakPtr<T> & rhs);

private:
    void OnDestroy ();

    TLink<WeakPtr<T>> m_link;
};



//=============================================================================
//
// SmartPtrData
//
//=============================================================================

template <typename T>
class SmartPtrData
{
    template <typename T>
    friend class WeakPtr;
public:

    SmartPtrData ();
    ~SmartPtrData ();

    void IncRef ();
    uint DecRef ();

private:
    // Types
    typedef LIST_DECLARE(WeakPtr<T>, m_link) WeakList;

    // Data
    WeakList m_weak;
    uint     m_refCount;
};



//=============================================================================
//
// IRefCounted
//
//=============================================================================

template <typename T>
struct IRefCounted
{
    //virtual CRefCounted<T> * GetRefCountData () = null;
};



//=============================================================================
//
// CRefCounted
//
//=============================================================================

template <typename T>
class CRefCounted
{
    template <typename T> friend class WeakPtr;
    template <typename T> friend class StrongPtr;

public:
    CRefCounted ();
    ~CRefCounted ();

    void IncRef ();
    uint DecRef ();

private: // IRefCounted<T>

    CRefCounted<T> * GetRefCountData ();

private:
    // Types
    typedef LIST_DECLARE(WeakPtr<T>, m_link) WeakList;

    // Data
    WeakList m_weak;
    uint     m_refCount;
};


#include "Pointer.inl"