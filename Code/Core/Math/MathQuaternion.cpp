//==================================================================================================
//
// File:    MathQuaternion.cpp
// Author:  Jason Jackson
// Date:    September 20, 2008
//
// Defines a four dimentional complex number
//
//==================================================================================================

#include "MathPch.h"

//=============================================================================
// 
//    Quaternion::Quaternion
//    
// Description: 
//    Converts a rotation matrix to a quaternion
//    
// Parameters: 
//    [const Matrix33 & m] - The rotation matrix to extract the rotation from
//    
//=============================================================================
Quaternion::Quaternion( const Matrix33 & m )
{
    float32 m00 = m(0,0);
    float32 m11 = m(1,1);
    float32 m22 = m(2,2);

    float32 t = 1.0f + Trace( m );

    //
    // Is the trace zero?
    //
    if( Equal( t, 0.0f ) )
    {
        //
        // Find the column that has the greatest value to save percision
        //
        if ( m00 > m11 && m00 > m22 ) // Column 0: 
        {
            float32 s  = Sqrt( 1.0f + m00 - m11 - m22 ) * 2.0f;

            v.x = 0.25f * s;
            v.y = (m(0,1) + m(1,0)) / s;
            v.z = (m(2,0) + m(0,2)) / s;
            a   = (m(1,2) - m(2,1)) / s;
        }
        else if ( m11 > m22 ) // Column 1: 
        {           
            float32 s  = Sqrt( 1.0f + m00 - m11 - m22 ) * 2.0f;

            v.x = (m(0,1) + m(1,0)) / s;
            v.y = 0.25f * s;
            v.z = (m(1,2) + m(2,1)) / s;
            a   = (m(2,0) - m(0,2)) / s;
        }
        else // Column 2:
        {                       
            float32 s  = Sqrt( 1.0f + m00 - m11 - m22 ) * 2.0f;

            v.x = (m(2,0) - m(0,2)) / s;
            v.y = (m(1,2) + m(2,1)) / s;
            v.z = 0.25f * s;
            a   = (m(0,1) + m(1,0)) / s;
        }
    }
    else
    {
        float32 s = Sqrt( t ) * 2.0f;
        v.x = (m(2,1) - m(1,2)) * s;
        v.y = (m(0,2) - m(2,0)) * s;
        v.z = (m(1,0) - m(0,1)) * s;
        a = 0.25f * s;
    }
}

//=============================================================================
// 
//    Quaternion::Quaternion
//    
// Description: 
//    Converts a rotation matrix to a quaternion
//    
// Parameters: 
//    [const Matrix33 & m] - The rotation matrix to extract the rotation from
//    
//=============================================================================
Quaternion::Quaternion( const Matrix34 & m )
{
    float32 m00 = m(0,0);
    float32 m11 = m(1,1);
    float32 m22 = m(2,2);

    float32 t = 1.0f + m00 + m11 + m22;

    //
    // Is the trace zero?
    //
    if( Equal( t, 0.0f ) )
    {
        if ( m00 > m11 && m00 > m22 ) // Column 0: 
        {
            float32 s  = Sqrt( 1.0f + m00 - m11 - m22 ) * 2.0f;

            v.x = 0.25f * s;
            v.y = (m(0,1) + m(1,0)) / s;
            v.z = (m(2,0) + m(0,2)) / s;
            a   = (m(1,2) - m(2,1)) / s;
        }
        else if ( m11 > m22 ) // Column 1: 
        {           
            float32 s  = Sqrt( 1.0f + m00 - m11 - m22 ) * 2.0f;

            v.x = (m(0,1) + m(1,0)) / s;
            v.y = 0.25f * s;
            v.z = (m(1,2) + m(2,1)) / s;
            a   = (m(2,0) - m(0,2)) / s;
        }
        else // Column 2:
        {                       
            float32 s  = Sqrt( 1.0f + m00 - m11 - m22 ) * 2.0f;

            v.x = (m(2,0) - m(0,2)) / s;
            v.y = (m(1,2) + m(2,1)) / s;
            v.z = 0.25f * s;
            a   = (m(0,1) + m(1,0)) / s;
        }

    }
    else
    {
        float32 s = Sqrt( t ) * 2.0f;
        v.x = (m(2,1) - m(1,2)) * s;
        v.y = (m(0,2) - m(2,0)) * s;
        v.z = (m(1,0) - m(0,1)) * s;
        a = 0.25f * s;
    }
}

//=============================================================================
// 
//    Quaternion::Quaternion
//    
// Description: 
//    Converts a rotation matrix to a quaternion
//    
// Parameters: 
//    [const Matrix44 & m] - The rotation matrix to extract the rotation from
//    
//=============================================================================
Quaternion::Quaternion( const Matrix44 & m )
{
    m;
    ASSERT(!"Not Implemented");
}


//=============================================================================
// 
//    Exp
//    
// Description: 
//    Exponentiation of a quaternion
//    
// Parameters: 
//    [const Quaternion & q] - quaternion to exponentiate
//    
// Return: 
//    [Quaternion] - e^q
//=============================================================================
Quaternion Exp( const Quaternion & q )
{
    Quaternion out;
    Radian  theta( Length( q.v ) );
    float32     sinTheta    = Sin( theta );

    out.a = Cos( theta );

    if( Equal( sinTheta, 0.0f ) )
        out.v = (Equal(sinTheta, 0.0f)) ? (q.v * sinTheta / theta) : (q.v);

   return out;
}


//=============================================================================
// 
//    Ln
//    
// Description: 
//    Natural logarithm of a quaternion
//    
// Parameters: 
//    [const Quaternion & q] - the quaternion to take the logarithm of
//    
// Return: 
//    [Quaternion] - 
//=============================================================================
Quaternion Ln( const Quaternion & q )
{
    Quaternion out;
    

    Radian theta = ArcCos( q.a );
    float32 sinTheta = Sin( theta );

    out.a = 0;
    out.v = (Equal(sinTheta,0.0f)) ? (q.v/sinTheta*theta) : (q.v);

    return out;
}

//=============================================================================
// 
//    Slerp
//    
// Description: 
//    Spherical linear interpolation between to quaternions
//    
// Parameters: 
//    [const Quaternion & a] - Start quaternion at t = 0.0
//    [const Quaternion & b] - End quaternion at t = 1.0
//    [float32 t] - Time of the interpolation
//    
// Return: 
//    [Quaternion] - A quaternion in between quaternions a and b
//=============================================================================
Quaternion Slerp( const Quaternion & a, const Quaternion & b, float32 t )
{
    Radian  omega           = ArcCos( Dot( a, b ) );
    float32     recipSinOmega   = 1.0f / Sin( omega );
    float32     sinTOmega       = Sin( t * omega );
    float32     sin1TOmega      = Sin( (1.0f-t) * omega );

    return a * sin1TOmega * recipSinOmega + b * sinTOmega * recipSinOmega;
}







