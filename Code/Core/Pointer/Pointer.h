
//*****************************************************************************
//
// Forwards
//
//*****************************************************************************

template <typename T> class     TWeakPtr;
template <typename T> class     TStrongPtr;
template <typename T> interface IRefCounted;

namespace Pointer {
namespace Private {
    template <typename T> class TSmartPtrBase;
	template <typename T> class TSmartPtrData;
}} // namespace Pointer::Private



//*****************************************************************************
//
// TSmartPtrBase
//
//*****************************************************************************

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



//*****************************************************************************
//
// TStrongPtr
//
//*****************************************************************************

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



//*****************************************************************************
//
// TWeakPtr
//
//*****************************************************************************

template <typename T>
class TWeakPtr :
    public Pointer::Private::TSmartPtrBase<T>
{
    template <typename T>
    friend class Pointer::Private::TSmartPtrData;
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



//*****************************************************************************
//
// IRefCounted
//
//*****************************************************************************

template <typename T>
interface IRefCounted
{
	virtual void IncRef () pure;
	virtual unsigned DecRef () pure;
	virtual void AddWeakRef (TWeakPtr<T> * weak) pure;
};



//*****************************************************************************
//
// TSmartPtrData
//
//*****************************************************************************
namespace Pointer { namespace Private {

template <typename T>
class TSmartPtrData
{
public:

    TSmartPtrData ();
    ~TSmartPtrData ();

    void IncRef ();
    uint DecRef ();
    void AddWeakRef (TWeakPtr<T> * weak);

private:
    // Types
    typedef LIST_DECLARE(TWeakPtr<T>, m_link) WeakList;

    // Data
    WeakList m_weaklist;
    uint     m_refCount;
};

}} // namespace Pointer::Private


//*****************************************************************************
//
// REFCOUNTED_ADAPTER
//
//*****************************************************************************

#define REFCOUNTED_ADAPTER(interface)                           \
	private:													\
    friend class TWeakPtr<interface>;                           \
    friend class TStrongPtr<interface>;                         \
	Pointer::Private::TSmartPtrData<interface> m_smartPtrData;	\
																\
	void IncRef () override {									\
		m_smartPtrData.IncRef();								\
	}															\
																\
	uint DecRef () override {									\
		const uint count = m_smartPtrData.DecRef();				\
		if (count == 0)											\
			delete this;										\
		return count;											\
	}															\
																\
	void AddWeakRef (TWeakPtr<interface> * weak) override {		\
		m_smartPtrData.AddWeakRef(weak);						\
	}															

#include "Pointer.inl"