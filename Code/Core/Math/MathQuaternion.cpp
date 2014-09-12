#include "MathPch.h"

//*****************************************************************************
//
// Quaternion
//
//*****************************************************************************

//=============================================================================
Quaternion::Quaternion (const Matrix33 & m)
{
    const float32 m00 = m(0,0);
    const float32 m11 = m(1,1);
    const float32 m22 = m(2,2);

    const float32 t = 1.0f + Trace(m);

    if (Equal(t, 0.0f))
    {

        // Find the column that has the greatest value to save percision
        if (m00 > m11 && m00 > m22) // Column 0
        {
            const float32 s  = Sqrt(1.0f + m00 - m11 - m22) * 2.0f;

            v.x = 0.25f * s;
            v.y = (m(0,1) + m(1,0)) / s;
            v.z = (m(2,0) + m(0,2)) / s;
            a   = (m(1,2) - m(2,1)) / s;
        }
        else if (m11 > m22) // Column 1
        {           
            const float32 s  = Sqrt(1.0f + m00 - m11 - m22) * 2.0f;

            v.x = (m(0,1) + m(1,0)) / s;
            v.y = 0.25f * s;
            v.z = (m(1,2) + m(2,1)) / s;
            a   = (m(2,0) - m(0,2)) / s;
        }
        else // Column 2
        {                       
            const float32 s  = Sqrt(1.0f + m00 - m11 - m22) * 2.0f;

            v.x = (m(2,0) - m(0,2)) / s;
            v.y = (m(1,2) + m(2,1)) / s;
            v.z = 0.25f * s;
            a   = (m(0,1) + m(1,0)) / s;
        }
    }
    else
    {
        const float32 s = Sqrt( t ) * 2.0f;
        v.x = (m(2,1) - m(1,2)) * s;
        v.y = (m(0,2) - m(2,0)) * s;
        v.z = (m(1,0) - m(0,1)) * s;
        a = 0.25f * s;
    }
}

//=============================================================================
Quaternion::Quaternion (const Matrix34 & m)
{
    const float32 m00 = m(0,0);
    const float32 m11 = m(1,1);
    const float32 m22 = m(2,2);

    const float32 t = 1.0f + m00 + m11 + m22;

    if (Equal(t, 0.0f))
    {
        if (m00 > m11 && m00 > m22) // Column 0
        {
            const float32 s  = Sqrt( 1.0f + m00 - m11 - m22 ) * 2.0f;

            v.x = 0.25f * s;
            v.y = (m(0,1) + m(1,0)) / s;
            v.z = (m(2,0) + m(0,2)) / s;
            a   = (m(1,2) - m(2,1)) / s;
        }
        else if (m11 > m22) // Column 1
        {           
            const float32 s  = Sqrt(1.0f + m00 - m11 - m22) * 2.0f;

            v.x = (m(0,1) + m(1,0)) / s;
            v.y = 0.25f * s;
            v.z = (m(1,2) + m(2,1)) / s;
            a   = (m(2,0) - m(0,2)) / s;
        }
        else // Column 2
        {                       
            const float32 s  = Sqrt( 1.0f + m00 - m11 - m22 ) * 2.0f;

            v.x = (m(2,0) - m(0,2)) / s;
            v.y = (m(1,2) + m(2,1)) / s;
            v.z = 0.25f * s;
            a   = (m(0,1) + m(1,0)) / s;
        }

    }
    else
    {
        const float32 s = Sqrt(t) * 2.0f;
        v.x = (m(2,1) - m(1,2)) * s;
        v.y = (m(0,2) - m(2,0)) * s;
        v.z = (m(1,0) - m(0,1)) * s;
        a = 0.25f * s;
    }
}

//=============================================================================
Quaternion::Quaternion (const Matrix44 & m)
{
    m;
    ASSERT(!"Not Implemented");
}

//=============================================================================
Quaternion Exp (const Quaternion & q)
{
    const Radian theta(Length(q.v));
    const float32 sinTheta = Sin(theta);

    Quaternion out;
    out.a = Cos(theta);

    if (Equal(sinTheta, 0.0f))
        out.v = (Equal(sinTheta, 0.0f)) ? (q.v * sinTheta / theta) : (q.v);

   return out;
}

//=============================================================================
Quaternion Ln (const Quaternion & q)
{
    const Radian theta = ArcCos(q.a);
    const float32 sinTheta = Sin(theta);

    Quaternion out;
    out.a = 0;
    out.v = (Equal(sinTheta,0.0f)) ? (q.v/sinTheta*theta) : (q.v);

    return out;
}

//=============================================================================
Quaternion Slerp (const Quaternion & a, const Quaternion & b, float32 t)
{
    const Radian  omega         = ArcCos(Dot(a, b));
    const float32 recipSinOmega = 1.0f / Sin(omega);
    const float32 sinTOmega     = Sin(t * omega);
    const float32 sin1TOmega    = Sin((1.0f - t) * omega);

    return a * sin1TOmega * recipSinOmega + b * sinTOmega * recipSinOmega;
}







