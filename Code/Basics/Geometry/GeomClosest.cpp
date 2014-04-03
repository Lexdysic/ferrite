//==================================================================================================
//
// File:    GeomClosest.cpp
// Author:  Jason Jackson
// Date:    October 5th, 2008
//
// Implement functions which find the closest point(s) between two objects
//
//=================================================================================================

#include "GeomPch.h"


//=============================================================================
// 
//    Closest
//    
// Description: 
//    Computes the closest point on a triangle to a point
//    
// Parameters: 
//    [const Point3 & p] - Point to test against
//    [const Triangle3 & tri] - Triangle to find a point on
//    
// Return: 
//    [Point3] - A point on the given triangle
//=============================================================================
Point3 Closest( const Point3 & p, const Triangle3 & tri )
{
    // Check if p is outside of A
    Vector3  ab = tri.b - tri.a;
    Vector3  ac = tri.c - tri.a;
    Vector3  ap = p     - tri.a;
    float32 d1 = Dot(ab, ap);
    float32 d2 = Dot(ac, ap);

    if( d1 <= 0.0f && d2 <= 0.0f )
        return tri.a;

    // Check if p is outside of B
    Vector3  bp = p - tri.b;
    float32 d3 = Dot(ab, bp);
    float32 d4 = Dot(ac, bp);

    if( d3 >= 0.0f && d4 <= d3 )
        return tri.b;

    // Check if p in edge region of AB
    float32 vc = d1*d4 - d3*d2;
    if( vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f )
    {
        float32 v = d1 / (d1 - d3);
        return tri.a * v * ab;
    }

    // Check if p in vertex region of C
    Vector3  cp = p - tri.c;
    float32 d5 = Dot(ab, cp);
    float32 d6 = Dot(ac, cp);
    if( d6 >= 0.0f && d5 <= d6 )
        return tri.c;

    // Check if p in edge region of AC
    float32 vb = d5*d2 - d1*d6;
    if( vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f )
    {
        float32 w = d2 / (d2 - d6);
        return tri.a + w * ac;
    }

    // Check if p in edge region BC
    float32 va = d3*d6 - d5*d4;
    if( va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f )
    {
        float32 w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
        return tri.b + w * (tri.c - tri.b);
    }

    // P inside face region
    float32 denom   = 1.0f / (va + vb + vc);
    float32 v       = vb * denom;
    float32 w       = vc * denom;

    return tri.a + ab * v + ac * w;
}



//=============================================================================
// 
//    ClosestInfo
//    
// Description: 
//    Gathers information about the closest meaningful geometry on two lines. This includes the
//    the times in both lines that represent the closest point to each other.
//    
// Parameters: 
//    [ClosestInfoLineLine3 & out] - Struct to be filled with information
//    [const Line3 & line1] - A line segment
//    [const Line3 & line2] - 
//    
// Return: 
//    [bool] - True if the information is unique for the two lines
//=============================================================================
bool ClosestInfo( ClosestInfoLineLine3 & out, const Line3 & line1, const Line3 & line2 )
{
    Vector3 r = line1.origin - line2.origin;

    float32 a = Dot( line1.direction, line1.direction );
    float32 e = Dot( line2.direction, line2.direction );
    float32 b = Dot( line1.direction, line2.direction );
    float32 d = a * e - b * b;

    // Are the lines parallel?
    if( Equal( d, 0.0f ) )
    {
        return false;
    }
    else
    {
        float32 c = Dot( line1.direction, r );
        float32 f = Dot( line2.direction, r );


        out.time1 = (b * f - c * e) / d;
        out.time2 = (a * f - b * c) / d;

        return true;
    }
}


//=============================================================================
// 
//    ClosestInfo
//    
// Description: 
//    Gathers the closest information about meaningful geometry on two line segments. This includes
//    the points on both lines which are closest to each other. The time on the line to those points,
//    and the squared distance of the two points.
//    
// Parameters: 
//    [ClosestInfoSegmentSegment3 & out] - Struct to be filled with the information
//    [const Segment3 & line1] - 
//    [const Segment3 & line2] - 
//    
// Return: 
//    [bool] - True if the given information is unique for the two lines
//=============================================================================
bool ClosestInfo( ClosestInfoSegmentSegment3 & out, const Segment3 & line1, const Segment3 & line2 )
{
    Vector3      d1 = line1.b - line1.a;
    Vector3      d2 = line2.b - line2.a;
    Vector3      r  = line1.a - line2.a;
    float32     a  = LengthSq(d1);
    float32     e  = LengthSq(d2);
    float32     f  = Dot(d2, r);
    float32 &   s  = out.time1;
    float32 &   t  = out.time2;

    bool bAZero = Equal(a, 0.0f);
    bool bEZero = Equal(e, 0.0f);

    // Do both segments degenerate to points?
    if( bAZero && bEZero )
    {
        s           = 0.0f;
        t           = 0.0f;
        out.point1  = line1.a;
        out.point2  = line2.a;
        out.distSq  = LengthSq(r);
        return true;
    }

    bool retVal = true;

    // First segment degerates to a point
    if( bAZero )
    {
        s = 0.0f;
        t = Clamp( f / e, 0.0f, 1.0f );
    }
    else
    {
        float32 c = Dot(d1, r);

        // Second segment degenerates to a point
        if( bEZero )
        {
            s = Clamp( -c / a, 0.0f, 1.0f );
            t = 0.0f;
        }
        // Non-degenerate case
        else
        {
            float32 b       = Dot(d1, d2);
            float32 denom   = a * e - b * b;

            if( !Equal( denom, 0.0f ) )
                s = Clamp( (b * f - c * e) / denom, 0.0f, 1.0f );
            else
            {
                s = 0.0f;
                retVal = false;
            }

            // Compute point on line2 closest to line1
            t = (b * s + f) / e;

            // if we need to clamp t, we must recompute s for the new value
            if( t < 0.0f )
            {
                s = Clamp( -c / a, 0.0f, 1.0f );
                t = 0.0f;
            }
            else if( t > 1.0f )
            {
                s = Clamp( (b - c) / a, 0.0f, 1.0f );
                t = 1.0f;
            }
        }
    }

    out.point1 = line1.a + d1 * s;
    out.point2 = line2.a + d2 * t;
    out.distSq = DistanceSq( out.point1, out.point2 );
    return retVal;;
}


//=============================================================================
// 
//    ClosestInfo
//    
// Description: 
//    Gathers information about the closest geometry on two rays.
//    
// Parameters: 
//    [ClosestInfoSegmentSegment3 & out] - Struct to be filled with information
//    [const Ray3 & line1] - 
//    [const Ray3 & line2] - 
//    
// Return: 
//    [bool] - True if this information is unique for the given two rays
//=============================================================================
bool ClosestInfo( ClosestInfoSegmentSegment3 & out, const Ray3 & line1, const Ray3 & line2 )
{
    assert(!"Not Implemented");

    out;
    line1;
    line2;

    return false;
}


