#ifdef MATHPOINT_H
#  error "Cannot include header more than once."
#endif
#define MATHPOINT_H


//*****************************************************************************
//
// Point2
//
//*****************************************************************************

class Point2 : public Vector2
{
public:
    inline Point2 ();
    inline Point2 (const Vector2 & v);
    inline Point2 (float32 x, float32 y);
};



//*****************************************************************************
//
// Point3
//
//*****************************************************************************

class Point3 : public Vector3
{
public:
    inline Point3();
    inline Point3( const Vector3 & v );
    inline Point3( float32 x, float32 y, float32 z );
};



//*****************************************************************************
//
// Operators
//
//*****************************************************************************

inline Vector2  operator- (const Point2 & lhs,  const Point2 & rhs );
inline Point2   operator- (const Point2 & lhs,  const Vector2 & rhs );
inline Point2   operator+ (const Point2 & lhs,  const Vector2 & rhs );
inline Point2   operator+ (const Vector2 & lhs, const Point2 & rhs );

inline Vector3  operator- (const Point3 & lhs,  const Point3 & rhs );
inline Point3   operator- (const Point3 & lhs,  const Vector3 & rhs );
inline Point3   operator+ (const Point3 & lhs,  const Vector3 & rhs );
inline Point3   operator+ (const Vector3 & lhs, const Point3 & rhs );

inline float32  Min (const Point2 & p);
inline float32  Min (const Point3 & p);

inline Point2   Min (const Point2 & a, const Point2 & b);
inline Point3   Min (const Point3 & a, const Point3 & b);

inline float32  Max (const Point2 & p);
inline float32  Max (const Point3 & p);

inline Point2   Max (const Point2 & a, const Point2 & b);
inline Point3   Max (const Point3 & a, const Point3 & b);