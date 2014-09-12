#ifdef GEOMOBB_H
#  error "Cannot include header more than once."
#endif
#define GEOMOBB_H

//*****************************************************************************
//
// Obb2
//
//*****************************************************************************

class Obb2
{
public:
    Obb2 ();
    Obb2 (const Point2 & center, const Vector2 & x, const Vector2 & y);
    Obb2 (const Point2 & center, const Vector2 & unitX, const Vector2 & unitY, const Vector2 & extent);

    inline float32 ProjectedRadiusAlongVector (const Vector2 & v) const;
    inline Matrix23 GetMatrix () const;
    TArray<Point2> GetPoints () const;

    Point2 center;      //!< Center of the box
    Vector2 extent;     //!< Positive halfwidth extents of Obb3 along each local axis
    Vector2 u[2];       //!< Local x-, y-, z-axes
};



//*****************************************************************************
//
// Obb3
//
//*****************************************************************************

class Obb3
{
public:
    Obb3 ();
    Obb3 (const Point3 & center, const Vector3 & x, const Vector3 & y, const Vector3 & z);
    Obb3 (const Point3 & center, const Vector3 & unitX, const Vector3 & unitY, const Vector3 & unitZ, const Vector3 & extent);

    inline float32 ProjectedRadiusAlongVector( const Vector3 & v ) const;

    Point3 center;      //!< Center of the box
    Vector3 extent;      //!< Positive halfwidth extents of Obb3 along each local axis
    Vector3 u[3];        //!< Local x-, y-, z-axes
};