


//*****************************************************************************
//
// Compile-time switches
//
//*****************************************************************************

//#define NOTIFIER_VALIDATE



//*****************************************************************************
//
// TNotifyLink
//
//*****************************************************************************

namespace Private
{

struct non_iterator_tag {};

template <typename T>
struct TNotifyLink
{
    TNotifyLink ();
    TNotifyLink (non_iterator_tag);
    ~TNotifyLink ();

    void LinkAfter (TNotifyLink<T> * link);
    void LinkBefore (TNotifyLink<T> * link);
    void Unlink ();
    bool IsLinked ();
    TNotifyTarget<T> * GetTarget ();

    // Data
    bool             isIterator;
    TNotifyLink<T> * prev;
    TNotifyLink<T> * next;
};

//=============================================================================
template <typename T>
TNotifyLink<T>::TNotifyLink () :
    prev(this),
    next(this),
    isIterator(true)
{
}

//=============================================================================
template <typename T>
TNotifyLink<T>::TNotifyLink (non_iterator_tag) :
    prev(this),
    next(this),
    isIterator(false)
{
}

//=============================================================================
template <typename T>
TNotifyLink<T>::~TNotifyLink ()
{
    Unlink();
}

//=============================================================================
template <typename T>
void TNotifyLink<T>::LinkAfter (TNotifyLink<T> * link)
{
    Unlink();

    prev = link;
    next = link->next;

    link->next->prev = this;
    link->next = this;
}

//=============================================================================
template <typename T>
void TNotifyLink<T>::LinkBefore (TNotifyLink<T> * link)
{
    Unlink();

    prev = link->prev;
    next = link;

    link->prev->next = this;
    link->prev = this;
}

//=============================================================================
template <typename T>
void TNotifyLink<T>::Unlink ()
{
    next->prev = prev;
    prev->next = next;

    prev = this;
    next = this;
}

//=============================================================================
template <typename T>
bool TNotifyLink<T>::IsLinked ()
{
    return next != this;
}

//=============================================================================
template <typename T>
TNotifyTarget<T> * TNotifyLink<T>::GetTarget ()
{
    ASSERT(!isIterator);
    return struct_of(m_link, TNotifyTarget<T>, *this);
}

} // Private



//*****************************************************************************
//
// TNotifyTarget
//
//*****************************************************************************

template <typename T>
TNotifyTarget<T>::TNotifyTarget () :
    m_link(Private::non_iterator_tag())
{
}



//*****************************************************************************
//
// TNotifier
//
//*****************************************************************************

//=============================================================================
template <typename T>
TNotifier<T>::~TNotifier ()
{
    Validate();
    while (m_link.IsLinked())
        m_link.next->Unlink();
    Validate();
}

//=============================================================================
template <typename T>
void TNotifier<T>::Add (TNotifyTarget<T> * target)
{
    Validate();
    target->m_link.LinkBefore(&m_link);
    Validate();
}

//=============================================================================
template <typename T>
void TNotifier<T>::Remove (TNotifyTarget<T> * target)
{
    Validate();
    target->m_link.Unlink();
    Validate();
}

//=============================================================================
template <typename T>
template <typename... Ts, typename... Args>
void TNotifier<T>::Call(void (T::*function)(Ts...), const Args &... args)
{
	Validate();
	Private::TNotifyLink<T> next;
	Private::TNotifyLink<T> * curr = m_link.next;
	for (; curr != &m_link; curr = next.next)
	{
		next.LinkAfter(curr);

		T * target = static_cast<T *>(curr->GetTarget());
		(target->*function)(args...);
	}
	next.Unlink();
	Validate();
}

//=============================================================================
template <typename T>
void TNotifier<T>::Validate ()
{
#ifdef NOTIFIER_VALIDATE
    Private::TNotifyLink<T> * curr = m_link.next;
    for ( ; curr != &m_link; curr = curr->next)
    {
        T * target = static_cast<T *>(curr->GetTarget());
    }
#endif
}


