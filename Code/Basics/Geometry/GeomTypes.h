#ifdef GEOMTYPES_H
#  error "Cannot include header more than once."
#endif
#define GEOMTYPES_H

//*****************************************************************************
//
// Forwards
//
//*****************************************************************************

class Aabb2;
class Aabb3;
class Capsule3;
class Ellipsoid3;
class Halfspace2;
class Halfspace3;
class Line2;
class Line3;
class Lozenge3;
class Obb3;
class Plane2;
class Plane3;
class Ray2;
class Ray3;
class Rect3;
class Segment3;
class Slab3;
class Sphere2;
class Sphere3;
class Triangle3;
class Polygon2;


//*****************************************************************************
//
// Constants
//
//*****************************************************************************

namespace Geometry
{

enum class EWinding
{
    Clockwise,
    CounterClockwise,
    Invalid
};

} // namespace Geometry