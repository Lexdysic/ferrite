
namespace Graphics
{

class CImage;
class CContext;

//=============================================================================
inline Vector2u ToVector2u (const D2D1_SIZE_U & size) { return Vector2u(size.width, size.height); }
inline Vector2 ToVector2 (const D2D1_SIZE_F & size) { return Vector2(size.width, size.height); }
inline D2D1_SIZE_U ToSizeU (const Vector2u & v) { return D2D1::SizeU(v.x, v.y); }
inline D2D1_SIZE_F ToSizeF (const Vector2u & v) { return D2D1::SizeF((float)v.x, (float)v.y); }
inline D2D1_COLOR_F ToColorF (const Color & c) { return D2D1::ColorF(c.r, c.g, c.b, c.a); }
D2D1_MATRIX_3X2_F ToD2DMatrix23 (const Matrix23 & mat);
inline D2D1_POINT_2F ToD2DPoint2F (const Point2 & p) { return D2D1::Point2F(p.x, p.y); }
inline D2D1_POINT_2U ToD2DPoint2U (const Point2u & p) { return D2D1::Point2U(p.x, p.y); }

//=============================================================================
template <typename T>
inline void SafeRelease (T *& obj)
{
    if (!obj)
        return;
    obj->Release();
    obj = null;
}

//=============================================================================
//template <typename T>
//inline void SafeRelease(T const * obj)
//{
//    if (!obj)
//        return;
//    obj->Release();
//}

} // namespace Graphics