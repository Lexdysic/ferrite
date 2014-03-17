//==================================================================================================
//
// File:    GeomTest.h
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// Tests the positiong of one object compared to a second
//
//=================================================================================================

#ifdef GEOMTEST_H
#  error "Cannot include header more than once."
#endif
#define GEOMTEST_H

enum GeomTestResult
{
    Inside,
    Outside,
    Straddle,
    On = Straddle
};

inline GeomTestResult Test (const Sphere3 & sphere, const Plane3 & plane);
inline GeomTestResult Test (const Obb3 & box, const Plane3 & plane);
inline GeomTestResult Test (const Aabb3 & box, const Plane3 & plane);
