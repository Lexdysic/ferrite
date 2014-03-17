//==================================================================================================
//
// File:    GeomObb.inl
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// An oriented bounding box which does not align to any native axis
//
//=================================================================================================

//=============================================================================
float32 Obb3::ProjectedRadiusAlongVector( const v3 & v ) const
{
    return  extent.x * Abs(Dot(v, u[0])) +
            extent.y * Abs(Dot(v, u[1])) +
            extent.z * Abs(Dot(v, u[2]));
}