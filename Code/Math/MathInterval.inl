//==================================================================================================
//
// File:    MathInterval.inl
// Author:  Jason Jackson
// Date:    September 20, 2008
//
// An interval on a number line
//==================================================================================================

//=============================================================================
Interval::Interval()
{
}

//=============================================================================
Interval::Interval( float32 a, float32 b )
:a(a)
,b(b)
{
}

//=============================================================================
Interval & Interval::operator+=( const Interval & rhs )
{
    a = Min(a, rhs.a);
    b = Max(b, rhs.b);
    return *this;
}

//=============================================================================
Interval operator+( const Interval & lhs, const Interval & rhs )
{
    return Interval( Min(lhs.a, rhs.a), Max(lhs.b, rhs.b) );
}

//=============================================================================
bool operator==( const Interval & lhs, const Interval & rhs )
{
    return lhs.a == rhs.a && lhs.b == rhs.b;
}

//=============================================================================
bool Equal( const Interval & lhs, const Interval & rhs )
{
    return Equal(lhs.a, rhs.a) && Equal(lhs.b, rhs.b);
}

//=============================================================================
Interval Intersection( const Interval & lhs, const Interval & rhs )
{
    return Interval( Max(lhs.a, rhs.a), Min(lhs.b, rhs.b) );
}

//=============================================================================
bool IsNull( const Interval & i )
{
    return i.a > i.b;
}