//==================================================================================================
//
// File:    MathTypes.inl
// Author:  Jason Jackson
// Date:    September 1, 2009
//
// Basic name substitutions and types
//
//==================================================================================================

//=============================================================================
//
// Flag
//
//=============================================================================

template <typename T>
Flag<T>::Flag (T f) :
    m_value(f)
{
    ASSERT(Math::IsPowerTwo(m_value));
}


//=============================================================================
//
// Flags
//
//=============================================================================

//=============================================================================
template <typename T> const Flags<T> Flags<T>::All(T(-1ll));
template <typename T> const Flags<T> Flags<T>::None(0);

//=============================================================================
template <typename T>
Flags<T>::Flags() :
    mFlags((T)0)
{
}

//=============================================================================
template <typename T>
Flags<T>::Flags(T f) :
    mFlags(f)
{
}

//=============================================================================
template <typename T>
void Flags<T>::Set(T flags)
{
    mFlags |= flags;
}

//=============================================================================
template <typename T>
void Flags<T>::SetBit(uint bit)
{
    //ASSERT(bit < NUM_BITS);

    Set(1 << bit);
}

//=============================================================================
template <typename T>
void Flags<T>::SetAll()
{
    return ~(T)0;
}

//=============================================================================
template <typename T>
void Flags<T>::SetTo (T flags, bool value)
{
    if (value)
        mFlags |= flags;
    else
        mFlags &= ~flags;
}

//=============================================================================
template <typename T>
void Flags<T>::Clear(T flags)
{
    mFlags &= ~flags;
}

//=============================================================================
template <typename T>
void Flags<T>::ClearBit(uint bit)
{
    //ASSERT(bit < NUM_BITS);

    Clear(1 << bit);
}

//=============================================================================
template <typename T>
void Flags<T>::ClearAll()
{
    mFlags = (T)0;
}

//=============================================================================
template <typename T>
bool Flags<T>::Test(T flags) const
{
    return (mFlags & flags) > (T)0;
}

//=============================================================================
template <typename T>
bool Flags<T>::TestBit(uint bit) const
{
    ASSERT(bit < NUM_BITS);

    return Test(1 << bit);
}

//=============================================================================
template <typename T>
bool Flags<T>::AnySet() const
{
    return mFlags > (T)0;
}

//=============================================================================
template <typename T>
bool Flags<T>::NoneSet() const
{
    return mFlags == (T)0;
}

//=============================================================================
template <typename T>
Flags<T>::operator T () const
{
    return mFlags;
}