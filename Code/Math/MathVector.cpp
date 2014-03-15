//==================================================================================================
//
// File:    MathVector.cpp
// Author:  Jason Jackson
// Date:    September 24, 2008
//
// Implementation of vector methods in 2-, 3-, and 4-space
//
//==================================================================================================

#include "MathPch.h"

const Vector2 Vector2::Zero(    0.0f, 0.0f );
const Vector2 Vector2::One(     1.0f, 1.0f );
const Vector2 Vector2::UnitX(   1.0f, 0.0f );
const Vector2 Vector2::UnitY(   0.0f, 1.0f );
const Vector2 Vector2::Infinity( Math::Infinity, Math::Infinity );

const Vector3 Vector3::Zero(    0.0f, 0.0f, 0.0f );
const Vector3 Vector3::One(     1.0f, 1.0f, 1.0f );
const Vector3 Vector3::UnitX(   1.0f, 0.0f, 0.0f );
const Vector3 Vector3::UnitY(   0.0f, 1.0f, 0.0f );
const Vector3 Vector3::UnitZ(   0.0f, 0.0f, 1.0f );
const Vector3 Vector3::Infinity( Math::Infinity, Math::Infinity, Math::Infinity );

const Vector4 Vector4::Zero(    0.0f, 0.0f, 0.0f, 0.0f );
const Vector4 Vector4::One(     1.0f, 1.0f, 1.0f, 1.0f );
const Vector4 Vector4::UnitX(   1.0f, 0.0f, 0.0f, 0.0f );
const Vector4 Vector4::UnitY(   0.0f, 1.0f, 0.0f, 0.0f );
const Vector4 Vector4::UnitZ(   0.0f, 0.0f, 1.0f, 0.0f );
const Vector4 Vector4::UnitW(   0.0f, 0.0f, 0.0f, 1.0f );
const Vector4 Vector4::Infinity( Math::Infinity, Math::Infinity, Math::Infinity, Math::Infinity );

//=============================================================================
void BuildBasis(const v3 & x, v3 & u, v3 & v, v3 & w)
{
    u = Normalize(x);

    const v3 a = Abs(u);
    if( a.x <= a.y && a.x <= a.z )      
        v = Cross(u, Normalize(v3(1.0f, -u.z, u.y)));
    else if( a.y <= a.x && a.y <= a.z ) 
        v = Cross(u, Normalize(v3(-u.z, 1.0f, u.x)));
    else                                
        v = Cross(u, Normalize(v3(-u.y, u.x, 1.0f)));

    w = Cross(u, v);

    //assert(Normalized(u));
    //assert(Normalized(v));
    //assert(Normalized(w));
    assert(Dot(u, v) < 1e-6);
    assert(Dot(v, w) < 1e-6);
    assert(Dot(w, u) < 1e-6);
}