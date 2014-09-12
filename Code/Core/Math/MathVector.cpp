#include "MathPch.h"


//*****************************************************************************
//
// Vector2
//
//*****************************************************************************

//=============================================================================
const Vector2 Vector2::Zero(    0.0f, 0.0f);
const Vector2 Vector2::One(     1.0f, 1.0f);
const Vector2 Vector2::UnitX(   1.0f, 0.0f);
const Vector2 Vector2::UnitY(   0.0f, 1.0f);
const Vector2 Vector2::Infinity( Math::Infinity, Math::Infinity );


//*****************************************************************************
//
// Vector3
//
//*****************************************************************************

//=============================================================================
const Vector3 Vector3::Zero(    0.0f, 0.0f, 0.0f );
const Vector3 Vector3::One(     1.0f, 1.0f, 1.0f );
const Vector3 Vector3::UnitX(   1.0f, 0.0f, 0.0f );
const Vector3 Vector3::UnitY(   0.0f, 1.0f, 0.0f );
const Vector3 Vector3::UnitZ(   0.0f, 0.0f, 1.0f );
const Vector3 Vector3::Infinity( Math::Infinity, Math::Infinity, Math::Infinity );


//*****************************************************************************
//
// Vector4
//
//*****************************************************************************

//=============================================================================
const Vector4 Vector4::Zero(    0.0f, 0.0f, 0.0f, 0.0f );
const Vector4 Vector4::One(     1.0f, 1.0f, 1.0f, 1.0f );
const Vector4 Vector4::UnitX(   1.0f, 0.0f, 0.0f, 0.0f );
const Vector4 Vector4::UnitY(   0.0f, 1.0f, 0.0f, 0.0f );
const Vector4 Vector4::UnitZ(   0.0f, 0.0f, 1.0f, 0.0f );
const Vector4 Vector4::UnitW(   0.0f, 0.0f, 0.0f, 1.0f );
const Vector4 Vector4::Infinity( Math::Infinity, Math::Infinity, Math::Infinity, Math::Infinity );


//*****************************************************************************
//
// Functions
//
//*****************************************************************************

//=============================================================================
void BuildBasis(const Vector3 & x, Vector3 & u, Vector3 & v, Vector3 & w)
{
    u = Normalize(x);

    const Vector3 a = Abs(u);
    if( a.x <= a.y && a.x <= a.z )      
        v = Cross(u, Normalize(Vector3(1.0f, -u.z, u.y)));
    else if( a.y <= a.x && a.y <= a.z ) 
        v = Cross(u, Normalize(Vector3(-u.z, 1.0f, u.x)));
    else                                
        v = Cross(u, Normalize(Vector3(-u.y, u.x, 1.0f)));

    w = Cross(u, v);

    //ASSERT(Normalized(u));
    //ASSERT(Normalized(v));
    //ASSERT(Normalized(w));
    ASSERT(Dot(u, v) < 1e-6);
    ASSERT(Dot(v, w) < 1e-6);
    ASSERT(Dot(w, u) < 1e-6);
}