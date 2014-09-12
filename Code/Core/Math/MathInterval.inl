
//*****************************************************************************
//
// Interval
//
//*****************************************************************************

//=============================================================================
Interval::Interval ()
{
}

//=============================================================================
Interval::Interval (float32 min, float32 max) :
    min(min),
    max(max)
{
}

//=============================================================================
Interval & Interval::operator+= (const Interval & rhs)
{
    min = Min(min, rhs.min);
    max = Max(max, rhs.max);
    return *this;
}

//=============================================================================
bool Interval::IsValid () const
{
    return min <= max;
}

//=============================================================================
Interval operator+ (const Interval & lhs, const Interval & rhs)
{
    return Interval(Min(lhs.min, rhs.min), Max(lhs.max, rhs.max));
}

//=============================================================================
bool operator== (const Interval & lhs, const Interval & rhs)
{
    return lhs.min == rhs.min && lhs.max == rhs.max;
}



//*****************************************************************************
//
// Functions
//
//*****************************************************************************

//=============================================================================
bool Equal (const Interval & lhs, const Interval & rhs)
{
    return Equal(lhs.min, rhs.min) && Equal(lhs.max, rhs.max);
}

//=============================================================================
Interval Intersection (const Interval & lhs, const Interval & rhs)
{
    return Interval(
        Max(lhs.min, rhs.min),
        Min(lhs.max, rhs.max)
    );
}

//=============================================================================
float32 Distance (const Interval & lhs, const Interval & rhs)
{
    if (lhs.min < rhs.min)
	    return rhs.min - lhs.max;
    else
	    return lhs.min - rhs.max;
}

//=============================================================================
float32 Length (const Interval & interval)
{
    if (!interval.IsValid())
        return 0.0f;

    return interval.max - interval.min;
}
