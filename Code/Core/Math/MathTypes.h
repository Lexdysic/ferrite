//==================================================================================================
//
// File:    MathTypes.h
// Author:  Jason Jackson
// Date:    September 20, 2008
//
// Defines all types for the math library.
//
//==================================================================================================

#ifdef MATHTYPES_H
#  error "Cannot include header more than once."
#endif
#define MATHTYPES_H

class Vector2;
class Vector3;
class Vector4;

class Point2;
class Point3;

class Matrix22;
class Matrix33;
class Matrix34;
class Matrix44;

class Quaternion;

class Radian;
class Degree;

class Interval;


//=============================================================================
//
// Short type names
//
//=============================================================================

typedef Vector2             v2;
typedef Vector3             v3;
typedef Vector4             v4;

typedef Point2              p2;
typedef Point3              p3;

typedef Matrix22            m22;
typedef Matrix33            m33;
typedef Matrix34            m34;
typedef Matrix44            m44;

typedef Quaternion          q32;