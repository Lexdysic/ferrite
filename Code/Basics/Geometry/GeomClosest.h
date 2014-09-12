#ifdef GEOMCLOSEST_H
#  error "Cannot include header more than once."
#endif
#define GEOMCLOSEST_H

//*****************************************************************************
//
// ClosestInfoLineLine3
//
//*****************************************************************************

struct ClosestInfoLineLine3
{
    float32 time1;      //!< The time of the closest point on the first line
    float32 time2;      //!< The time of the closest point on the second line
};



//*****************************************************************************
//
// ClosestInfoSegmentSegment3
//
//*****************************************************************************

struct ClosestInfoSegmentSegment3
{
    float32 time1;      //!< The time of the closest point on the first line
    float32 time2;      //!< The time of the closest point on the second line
    Point3  point1;     //!< The point on first line that is closest to the second
    Point3  point2;     //!< The point on second line that is closest to the first
    float32 distSq;     //!< The squared distance of the closest points on the lines
};



//*****************************************************************************
//
// ClosestInfoRayRay3
//
//*****************************************************************************

struct ClosestInfoRayRay3
{
    float32 time1;      //!< The time of the closest point on the first line
    float32 time2;      //!< The time of the closest point on the second line
    Point3  point1;     //!< The point on first line that is closest to the second
    Point3  point2;     //!< The point on second line that is closest to the first
    float32 distSq;     //!< The squared distance of the closest points on the lines
};



//*****************************************************************************
//
// Functions
//
//*****************************************************************************

inline Point3 Closest (const Point3 & p,  const Plane3 & plane);
inline Point3 Closest (const Point3 & p,  const Line3 & line);
inline Point3 Closest (const Point3 & p,  const Ray3 & line);

inline Point2 Closest (const Point2 & p,  const Segment2 & line);
inline Point3 Closest (const Point3 & p,  const Segment3 & line);

inline Point3 Closest (const Point3 & p,  const Aabb3 & box);
inline Point3 Closest (const Point3 & p,  const Obb3 & box);
inline Point3 Closest (const Point3 & p,  const Rect3 & rect);
       Point3 Closest (const Point3 & p,  const Triangle3 & tri);

bool ClosestInfo (ClosestInfoLineLine3 & out, const Line3 & line1, const Line3 & line2);
bool ClosestInfo (ClosestInfoSegmentSegment3 & out, const Segment3 & line1, const Segment3 & line2);
//bool ClosestInfo( ClosestInfoRayRay3 & out, const Ray3 & line1, const Ray3 & line2 );
