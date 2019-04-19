#ifdef GEOMAABB_H
#  error "Cannot include header more than once."
#endif
#define GEOMAABB_H

#include "Core/Containers/CntArray.h"

//*****************************************************************************
//
// Aabb2
//
//*****************************************************************************

class Aabb2
{
public:
    Aabb2 ();
    Aabb2 (const Point2 & min,    const Point2 & max);
    Aabb2 (const Point2 & center, const Vector2 & halfExtent);

    inline Aabb2 & operator+= (const Aabb2 & rhs);
    inline Aabb2 & operator+= (const Point2 & rhs);

    inline float32 ProjectedRadiusAlongVector (const Vector2 & v) const;
    TArray<Point2> GetPoints() const;

    static const Aabb2 Null;
    static const Aabb2 Infinity;

    Point2 min;
    Point2 max;
};

inline Aabb2 operator+ (const Aabb2 & lhs, const Aabb2 & rhs);
inline Aabb2 operator+ (const Aabb2 & lhs, const Point2 & rhs);
inline Aabb2 operator+ (const Point2 & lhs, const Aabb2 & rhs);
inline Aabb2 Intersection (const Aabb2 & lhs, const Aabb2 & rhs);

void MostSeparatedPointsOnAabb (uint & min, uint & max, const TArray<Point2> & points);



//*****************************************************************************
//
// Aabb3
//
//*****************************************************************************

class Aabb3
{
public:
    Aabb3 ();
    Aabb3 (const Point3 & min,    const Point3 & max);
    Aabb3 (const Point3 & center, const Vector3 & halfExtent);

    inline Aabb3 & operator+= (const Aabb3 & rhs);
    inline Aabb3 & operator+= (const Point3 & rhs);

    inline float32 ProjectedRadiusAlongVector (const Vector3 & v) const;

    static const Aabb3 Null;
    static const Aabb3 Infinity;

    Point3 min;
    Point3 max;
};

inline Aabb3 operator+ (const Aabb3 & lhs, const Aabb3 & rhs);
inline Aabb3 operator+ (const Aabb3 & lhs, const Point3 & rhs);
inline Aabb3 operator+ (const Point3 & lhs, const Aabb3 & rhs);
inline Aabb3 Intersection (const Aabb3 & lhs, const Aabb3 & rhs);

void MostSeparatedPointsOnAabb (uint & min, uint & max, const TArray<Point3> & points);
