//==================================================================================================
//
// File:    MathInterval.h
// Author:  Jason Jackson
// Date:    September 20, 2008
//
// An interval on a number line
//
//==================================================================================================

#ifdef MATHINTERVAL_H
#  error "Cannot include header more than once."
#endif
#define MATHINTERVAL_H

//=============================================================================
//
// Interval
//
//=============================================================================
class Interval
{
public:
    inline Interval ();
    inline Interval (float32 a, float32 b);

    inline Interval & operator+= (const Interval & rhs);

    inline bool IsValid () const;

    static const Interval Null;
    static const Interval Infinite;

    float32 a;
    float32 b;
};

inline Interval operator+ (const Interval & lhs, const Interval & rhs);
inline bool     operator== (const Interval & lhs, const Interval & rhs);
inline bool     Equal (const Interval & lhs, const Interval & rhs);
inline Interval Intersection (const Interval & lhs, const Interval & rhs);
inline bool     IsNull (const Interval & i);