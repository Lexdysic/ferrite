#ifdef GEOMSPHERE_H
#  error "Cannot include header more than once."
#endif
#define GEOMSPHERE_H

//*****************************************************************************
//
// Forwards
//
//*****************************************************************************

class Sphere2;
class Sphere3;

typedef Sphere2 Circle;



//*****************************************************************************
//
// Sphere2
//
//*****************************************************************************

class Sphere2
{
public: // Construction

	Sphere2 ();
	Sphere2 (const Sphere2 & rhs);
    Sphere2 (const Point2 & c, float32 r);

	Sphere2 & operator= (const Sphere2 & rhs) = default;

public: // Constants

    static const Sphere2 Unit;

public: // Data

    union
    {
        struct{ Point2 center;  float32 radius; };
        struct{ float32 x, y, r; };
    };
};



//*****************************************************************************
//
// Sphere3
//
//*****************************************************************************

class Sphere3
{
public: // Construction

    Sphere3 ();
	Sphere3 (const Sphere3 & rhs);
    Sphere3 (const Point3 & c, float32 r);

public: // Constants

    static const Sphere3 Unit;

public: // Data

    union
    {
        struct { Point3 center;  float32 radius; };
        struct { float32 x, y, z, r; };
    };
};
