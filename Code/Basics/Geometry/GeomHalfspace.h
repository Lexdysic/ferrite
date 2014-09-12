#ifdef GEOMHALFSPACE_H
#  error "Cannot include header more than once."
#endif
#define GEOMHALFSPACE_H

//*****************************************************************************
//
// Halfspace2
//
//*****************************************************************************

class Halfspace2
{
public:
    Halfspace2 () = default;
    Halfspace2 (const Point2 & point, const Vector2 & outwardNormal);
    
    Point2  point;
    Vector2 normal;
};



//*****************************************************************************
//
// Halfspace3
//
//*****************************************************************************

class Halfspace3
{
public:
    Halfspace3 () = default;
    Halfspace3 (const Point3 & point, const Vector3 & outwardNormal);
    
    Point3  point;
    Vector3 normal;
};