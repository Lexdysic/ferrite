#ifndef UTILITIES_NOTIFIER_H
#define UTILITIES_NOTIFIER_H

//*****************************************************************************
//
// Forward Declares
//
//*****************************************************************************

template <typename T>
class TNotifyTarget;


namespace Private
{

template <typename T>
struct TNotifyLink;

} // Private



//*****************************************************************************
//
// TNotifyTarget
//
//*****************************************************************************

template <typename T>
class TNotifyTarget
{
public:
    TNotifyTarget ();

private:
    Private::TNotifyLink<T> m_link;

private:
    CLASS_NO_COPY(TNotifyTarget);

    template <typename T>
    friend class TNotifier;

    template <typename T>
    friend struct Private::TNotifyLink;
};



//*****************************************************************************
//
// TNotifier
//
//*****************************************************************************

template <typename T>
class TNotifier
{
public:

    ~TNotifier ();

    void Add (TNotifyTarget<T> * target);
    void Remove (TNotifyTarget<T> * target);

    template <typename... Ts, typename... Args>
    void Call (void (T::*function)(Ts...), const Args &... args);

private:

    inline void Validate ();

    Private::TNotifyLink<T> m_link;
};

#include "Notifier.inl"

#endif // UTILITIES_NOTIFIER_H