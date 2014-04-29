
//=============================================================================
//
// TColorBase
//
//=============================================================================

//=============================================================================
template <typename T>
TColorBase<T>::TColorBase () :
    r(0),
    g(0),
    b(0),
    a(1)
{
}

//=============================================================================
template <typename T>
TColorBase<T>::TColorBase (const TColorBase<T> & rhs) :
    r(rhs.r),
    g(rhs.g),
    b(rhs.b),
    a(rhs.a)
{
}

//=============================================================================
template <typename T>
TColorBase<T>::TColorBase (
    const T & r,
    const T & g,
    const T & b,
    const T & a
) :
    r(r),
    g(g),
    b(b),
    a(a)
{
}

//=============================================================================
template <typename T>
TColorBase<T> & TColorBase<T>::operator+= (const TColorBase<T> & rhs)
{
    r += rhs.r;
    g += rhs.g;
    b += rhs.b;
    a += rhs.a;
}

//=============================================================================
template <typename T>
TColorBase<T> & TColorBase<T>::operator-= (const TColorBase<T> & rhs)
{
    r -= rhs.r;
    g -= rhs.g;
    b -= rhs.b;
    a -= rhs.a;
}

//=============================================================================
template <typename T>
TColorBase<T> & TColorBase<T>::operator*= (const TColorBase<T> & rhs)
{
    r *= rhs.r;
    g *= rhs.g;
    b *= rhs.b;
    a *= rhs.a;
}

//=============================================================================
template <typename T>
TColorBase<T> & TColorBase<T>::operator*= (const T & rhs)
{
    r *= rhs;
    g *= rhs;
    b *= rhs;
    a *= rhs;
}

//=============================================================================
template <typename T>
TColorBase<T> & TColorBase<T>::operator/= (const TColorBase<T> & rhs)
{
    r /= rhs.r;
    g /= rhs.g;
    b /= rhs.b;
    a /= rhs.a;
}

//=============================================================================
template <typename T>
TColorBase<T> & TColorBase<T>::operator/= (const T & rhs)
{
    r /= rhs;
    g /= rhs;
    b /= rhs;
    a /= rhs;
}


//=============================================================================
template <typename T>
TColorBase<T> operator+ (const TColorBase<T> & lhs, const TColorBase<T> & rhs)
{
    return TColorBase<T>(
        lhs.r + rhs.r,
        lhs.g + rhs.g,
        lhs.b + rhs.b,
        lhs.a + rhs.a
    );
}

//=============================================================================
template <typename T>
TColorBase<T> operator- (const TColorBase<T> & lhs, const TColorBase<T> & rhs)
{
    return TColorBase<T>(
        lhs.r - rhs.r,
        lhs.g - rhs.g,
        lhs.b - rhs.b,
        lhs.a - rhs.a
    );
}

//=============================================================================
template <typename T>
TColorBase<T> operator* (const TColorBase<T> & lhs, const TColorBase<T> & rhs)
{
    return TColorBase<T>(
        lhs.r * rhs.r,
        lhs.g * rhs.g,
        lhs.b * rhs.b,
        lhs.a * rhs.a
    );
}

//=============================================================================
template <typename T>
TColorBase<T> operator* (const TColorBase<T> & lhs, const T & rhs)
{
    return TColorBase<T>(
        lhs.r * rhs,
        lhs.g * rhs,
        lhs.b * rhs,
        lhs.a * rhs
    );
}

//=============================================================================
template <typename T>
TColorBase<T> operator/ (const TColorBase<T> & lhs, const TColorBase<T> & rhs)
{
    return TColorBase<T>(
        lhs.r / rhs.r,
        lhs.g / rhs.g,
        lhs.b / rhs.b,
        lhs.a / rhs.a
    );
}

//=============================================================================
template <typename T>
TColorBase<T> operator/ (const TColorBase<T> & lhs, const T & rhs)
{
    return TColorBase<T>(
        lhs.r / rhs,
        lhs.g / rhs,
        lhs.b / rhs,
        lhs.a / rhs
    );
}



//=============================================================================
//
// Color
//
//=============================================================================

//=============================================================================
Color::Color () :
    TColorBase<float32>() 
{
}

//=============================================================================
Color::Color (const Color & color) :
    TColorBase<float32>(color)
{
}

Color::Color (const Color & color, float32 alpha) :
    TColorBase<float32>(color.r, color.g, color.b, alpha)
{
}

//=============================================================================
Color::Color (float32 r, float32 g, float32 b, float32 a) :
    TColorBase<float32>(r, g, b, a)
{
}

//=============================================================================
Color & Color::operator+= (const Color & rhs)
{
    r += rhs.r;
    g += rhs.g;
    b += rhs.b;
    a += rhs.a;
    return *this;
}

//=============================================================================
Color & Color::operator-= (const Color & rhs)
{
    r -= rhs.r;
    g -= rhs.g;
    b -= rhs.b;
    a -= rhs.a;
    return *this;
}

//=============================================================================
Color & Color::operator*= (const Color & rhs)
{
    r *= rhs.r;
    g *= rhs.g;
    b *= rhs.b;
    a *= rhs.a;
    return *this;
}

//=============================================================================
Color & Color::operator/= (const Color & rhs)
{
    r /= rhs.r;
    g /= rhs.g;
    b /= rhs.b;
    a /= rhs.a;
    return *this;
}

//=============================================================================
Color & Color::operator*= (const float32 & rhs)
{
    r *= rhs;
    g *= rhs;
    b *= rhs;
    a *= rhs;
    return *this;
}

//=============================================================================
Color & Color::operator/= (const float32 & rhs)
{
    r /= rhs;
    g /= rhs;
    b /= rhs;
    a /= rhs;
    return *this;
}


//=============================================================================
Color operator+ (const Color & lhs, const Color & rhs)
{
    return Color(
        lhs.r + rhs.r,
        lhs.g + rhs.g,
        lhs.b + rhs.b,
        lhs.a + rhs.a
    );
}

//=============================================================================
Color operator- (const Color & lhs, const Color & rhs)
{
    return Color(
        lhs.r - rhs.r,
        lhs.g - rhs.g,
        lhs.b - rhs.b,
        lhs.a - rhs.a
    );
}

//=============================================================================
Color operator* (const Color & lhs, const Color & rhs)
{
    return Color(
        lhs.r * rhs.r,
        lhs.g * rhs.g,
        lhs.b * rhs.b,
        lhs.a * rhs.a
    );
}

//=============================================================================
Color operator/ (const Color & lhs, const Color & rhs)
{
    return Color(
        lhs.r / rhs.r,
        lhs.g / rhs.g,
        lhs.b / rhs.b,
        lhs.a / rhs.a
    );
}

//=============================================================================
Color operator* (const Color & lhs, const float32 & rhs)
{
    return Color(
        lhs.r * rhs,
        lhs.g * rhs,
        lhs.b * rhs,
        lhs.a * rhs
    );
}

//=============================================================================
Color operator/ (const Color & lhs, const float32 & rhs)
{
    return Color(
        lhs.r / rhs,
        lhs.g / rhs,
        lhs.b / rhs,
        lhs.a / rhs
    );
}



//=============================================================================
//
// Hsl
//
//=============================================================================

//=============================================================================
Hsl::Hsl () :
    h(0.0f),
    s(0.0f),
    l(0.0f),
    a(1.0f)
{
}

//=============================================================================
Hsl::Hsl (float32 h, float32 s, float32 l, float32 a) :
    h(h),
    s(s),
    l(l),
    a(a)
{
}
