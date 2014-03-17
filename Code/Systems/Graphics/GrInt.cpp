#include "GrPch.h"

namespace Graphics
{

D2D1_MATRIX_3X2_F ToD2DMatrix23 (const Matrix23 & mat)
{
    return D2D1::Matrix3x2F(
        mat.m00, mat.m10,
        mat.m01, mat.m11,
        mat.m02, mat.m12
    );
}


} // namespace Graphics