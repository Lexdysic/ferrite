//==================================================================================================
//
// File:    MathAngle.h
// Author:  Jason Jackson
// Date:    September 21, 2008
//
// Explicitly defines degrees and radians as separate types.
//
//=================================================================================================

#ifdef MATHANGLE_H
#  error "Cannot include header more than once"
#endif
#define MATHANGLE_H

class Degree;
class Radian;



//=============================================================================
//
// Degree representation of an angle
//
//=============================================================================

class Degree
{
public:
    inline Degree();
    inline explicit Degree (float32 value);
    inline explicit Degree (Radian rad);

    inline operator float32 () const; // TODO: make explicit

    inline Degree &    operator*= (float32 s);
    inline Degree &    operator/= (float32 s);
    inline Degree &    operator*= (const Degree & angle);
    inline Degree &    operator/= (const Degree & angle);
    inline Degree &    operator+= (const Degree & angle);
    inline Degree &    operator-= (const Degree & angle);

private:
    float32 m_value;
};

inline Degree operator+ (Degree a, Degree b);
inline Degree operator- (Degree a, Degree b);
inline Degree operator* (Degree ang, float32 x);
inline Degree operator/ (Degree ang, float32 x);
inline Degree operator+ (Degree ang, float32 x);
inline Degree operator- (Degree ang, float32 x);
inline Degree operator* (float32 x,  Degree ang);
inline Degree operator/ (float32 x,  Degree ang);
inline Degree operator+ (float32 x,  Degree ang);
inline Degree operator- (float32 x,  Degree ang);



//=============================================================================
//
// Radian representation of an angle
//
//=============================================================================

class Radian
{
public:
    inline Radian ();
    inline explicit Radian (float32 value);
    inline explicit Radian (Degree deg);

    inline operator float32() const; // TODO: make explicit

    inline Radian &    operator*= (float32 s);
    inline Radian &    operator/= (float32 s);
    inline Radian &    operator*= (const Radian & angle);
    inline Radian &    operator/= (const Radian & angle);
    inline Radian &    operator+= (const Radian & angle);
    inline Radian &    operator-= (const Radian & angle);

private:
    float32 m_value;
};

inline Radian operator+ (Radian a, Radian b);
inline Radian operator- (Radian a, Radian b);
inline Radian operator* (Radian ang, float32 x);
inline Radian operator/ (Radian ang, float32 x);
inline Radian operator+ (Radian ang, float32 x);
inline Radian operator- (Radian ang, float32 x);
inline Radian operator* (float32 x,  Radian ang);
inline Radian operator/ (float32 x,  Radian ang);
inline Radian operator+ (float32 x,  Radian ang);
inline Radian operator- (float32 x,  Radian ang);



//=============================================================================
//
// Euler
//
//=============================================================================

struct Euler
{
    Radian x, y, z;
};
