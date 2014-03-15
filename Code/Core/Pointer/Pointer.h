
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
    SmartPtrBase () :
        m_data(null)
    {
    }

    SmartPtrBase (T * data) :
        m_data(data)
    {
    }

    ~SmartPtrBase ()
    {
        // TODO: assert that m_data == null
    }

    T & operator* ()
    {
        return *m_data;
    }

    T * operator-> ()
    {
        return m_data;
    }

    operator bool ()
    {
        return m_data != null;
    }

    operator T * ()
    {
        return m_data;
    }

    operator const T * ()
    {
        return m_data;
    }

    operator const T * () const
    {
        return m_data;
    }

protected:
    T * m_data;
};

}



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
    StrongPtr ()
    {
    }

    StrongPtr (T * rhs) :
        Private::SmartPtrBase<T>(rhs)
    {
        IncRef();
    }

    StrongPtr (const StrongPtr<T> & rhs) :
        Private::SmartPtrBase<T>(rhs.m_data)
    {
        IncRef();
    }

    ~StrongPtr ()
    {
        DecRef();
    }

    const StrongPtr<T> & operator= (const StrongPtr<T> & rhs)
    {
        DecRef();

        m_data = rhs.m_data;

        IncRef();

        return *this;
    }

    const StrongPtr<T> & operator= (const nullptr_t & rhs)
    {
        DecRef();

        m_data = null;

        return *this;
    }

private:
    inline void IncRef ()
    {
        if (m_data)
            m_data->GetRefCountData()->IncRef();
    }

    inline void DecRef ()
    {
        if (m_data)
        {
            const uint refCount = m_data->GetRefCountData()->DecRef();
            if (!refCount)
                delete m_data;
        }
    }

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
    WeakPtr ()
    {
    }

    WeakPtr (const WeakPtr & rhs) :
        Private::SmartPtrBase<T>(rhs.m_data)
    {
        if (m_data)
            m_data->GetRefCountData()->m_weak.InsertTail(this);
    }

    WeakPtr (T * data) :
        Private::SmartPtrBase<T>(data)
    {
        if (m_data)
            m_data->GetRefCountData()->m_weak.InsertTail(this);
    }

    WeakPtr<T> & operator= (const WeakPtr<T> & rhs)
    {
        m_link.Unlink();

        m_data = rhs.m_data;

        if (m_data)
            m_data->GetRefCountData()->m_weak.InsertTail(this);

        return *this;
    }

private:

    // Notifications
    void OnDestroy ()
    {
        m_data = null;
    }

    // Data
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
    SmartPtrData () :
        m_refCount(0)
    {
    }

    ~SmartPtrData ()
    {
        for (auto weak : m_weak)
        {
            weak->OnDestroy();
        }

        ASSERT(m_refCount == 0);
    }

    void IncRef ()
    {
        m_refCount++;
    }

    uint DecRef ()
    {
        ASSERT(m_refCount != 0);
        return --m_refCount;
    }

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
    CRefCounted () :
        m_refCount(0)
    {
    }

    ~CRefCounted ()
    {
        for (auto weak : m_weak)
        {
            weak->OnDestroy();
        }

        ASSERT(m_refCount == 0);
    }

    void IncRef ()
    {
        m_refCount++;
    }

    uint DecRef ()
    {
        ASSERT(m_refCount != 0);
        return --m_refCount;
    }


private: // IRefCounted<T>

    CRefCounted<T> * GetRefCountData () { return this; }

private:
    // Types
    typedef LIST_DECLARE(WeakPtr<T>, m_link) WeakList;

    // Data
    WeakList m_weak;
    uint     m_refCount;
};


#include "Pointer.inl"