#ifdef COLOR_H
#  error "Cannot include header more than once."
#endif
#define COLOR_H


struct Color;
struct Hsl;

//=============================================================================
//
// TColorBase
//
//=============================================================================

template <typename T>
struct TColorBase
{
    inline TColorBase ();
    inline TColorBase (const TColorBase<T> & rhs);
    inline TColorBase (const T & r, const T & g, const T & b, const T & a);

    TColorBase<T> & operator+= (const TColorBase<T> & rhs);
    TColorBase<T> & operator-= (const TColorBase<T> & rhs);
    TColorBase<T> & operator*= (const TColorBase<T> & rhs);
    TColorBase<T> & operator*= (const T & rhs);
    TColorBase<T> & operator/= (const TColorBase<T> & rhs);
    TColorBase<T> & operator/= (const T & rhs);

    friend TColorBase<T> operator+ (const TColorBase<T> & lhs, const TColorBase<T> & rhs);
    friend TColorBase<T> operator- (const TColorBase<T> & lhs, const TColorBase<T> & rhs);
    friend TColorBase<T> operator* (const TColorBase<T> & lhs, const TColorBase<T> & rhs);
    friend TColorBase<T> operator* (const TColorBase<T> & lhs, const T & rhs);
    friend TColorBase<T> operator/ (const TColorBase<T> & lhs, const TColorBase<T> & rhs);
    friend TColorBase<T> operator/ (const TColorBase<T> & lhs, const T & rhs);

    T r, g, b, a;
};


//=============================================================================
//
// Color
//
//=============================================================================

struct Color : TColorBase<float32>
{
    inline Color ();
    inline Color (const Color & rhs);
    inline Color (float32 r, float32 g, float32 b, float32 a = 1.0f);
    explicit Color (const Hsl & hsl);

    inline Color & operator+= (const Color & rhs);
    inline Color & operator-= (const Color & rhs);
    inline Color & operator*= (const Color & rhs);
    inline Color & operator/= (const Color & rhs);
    inline Color & operator/= (const float32 & rhs);
    inline Color & operator*= (const float32 & rhs);

    friend inline Color operator+ (const Color & lhs, const Color & rhs);
    friend inline Color operator- (const Color & lhs, const Color & rhs);
    friend inline Color operator* (const Color & lhs, const Color & rhs);
    friend inline Color operator/ (const Color & lhs, const Color & rhs);
    friend inline Color operator/ (const Color & lhs, const float32 & rhs);
    friend inline Color operator* (const Color & lhs, const float32 & rhs);

    static const Color White;
    static const Color Black;
    static const Color Red;
    static const Color Green;
    static const Color Blue;
};


//=============================================================================
//
// Hsl
//
//=============================================================================

struct Hsl
{
    inline Hsl ();
    inline Hsl (float32 h, float32 s, float32 l, float32 a = 1.0f);
    Hsl (const Color & color);

    float32 h, s, l, a;
};



//=============================================================================
//
// Helpers
//
//=============================================================================

float32 ColorGetLuminance (const Color & color);


#include "Color.inl"