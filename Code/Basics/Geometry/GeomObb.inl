
//*****************************************************************************
//
// Obb2
//
//*****************************************************************************

//=============================================================================
Matrix23 Obb2::GetMatrix () const
{
    return {
        Vector3(u[0] * extent.x, center.x),
        Vector3(u[1] * extent.y, center.y)
    };
}


//=============================================================================
float32 Obb2::ProjectedRadiusAlongVector (const Vector2 & v) const
{
    return  extent.x * Abs(Dot(v, u[0])) +
            extent.y * Abs(Dot(v, u[1]));
}


//=============================================================================
float32 Obb3::ProjectedRadiusAlongVector (const Vector3 & v) const
{
    return  extent.x * Abs(Dot(v, u[0])) +
            extent.y * Abs(Dot(v, u[1])) +
            extent.z * Abs(Dot(v, u[2]));
}
