//==================================================================================================
//
// File:    GeomAabb.inl
// Author:  Jason Jackson
// Date:    October 5th, 2008
//
// Implements inlined functions related to axis-aligned bounding boxes
//
//=================================================================================================


inline Aabb2 operator+ (const Aabb2 & lhs, const Aabb2 & rhs)       { return Aabb2( Min(lhs.min, rhs.min), Max(lhs.max, rhs.max) ); }
inline Aabb2 operator+ (const Aabb2 & lhs, const Point2 & rhs)      { return Aabb2( Min(lhs.min, rhs), Max(lhs.max, rhs) ); }
inline Aabb2 operator+ (const Point2 & lhs, const Aabb2 & rhs)      { return Aabb2( Min(rhs.min, lhs), Max(rhs.max, lhs) ); }
inline Aabb2 Intersection (const Aabb2 & lhs, const Aabb2 & rhs)    { return Aabb2( Max(lhs.min, rhs.min), Min(lhs.max, rhs.max) ); }


Aabb3 operator+ (const Aabb3 & lhs, const Aabb3 & rhs)     { return Aabb3( Min(lhs.min, rhs.min), Max(lhs.max, rhs.max) ); }
Aabb3 operator+ (const Aabb3 & lhs, const Point3 & rhs)    { return Aabb3( Min(lhs.min, rhs), Max(lhs.max, rhs) ); }
Aabb3 operator+ (const Point3 & lhs, const Aabb3 & rhs)    { return Aabb3( Min(rhs.min, lhs), Max(rhs.max, lhs) ); }
Aabb3 Intersection (const Aabb3 & lhs, const Aabb3 & rhs)  { return Aabb3( Max(lhs.min, rhs.min), Min(lhs.max, rhs.max) ); }

//=============================================================================
float32 Aabb3::ProjectedRadiusAlongVector( const Vector3 & v ) const
{
    Vector3 extent = (max - min) * 0.5f;
    return  extent.x * Abs(v.x) +
            extent.y * Abs(v.y) +
            extent.z * Abs(v.z);

}