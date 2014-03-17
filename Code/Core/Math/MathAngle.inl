//==================================================================================================
//
// File:    MathAngle.inl
// Author:  Jason Jackson
// Date:    September 21, 2008
//
// Explicitly defines degrees and radians as separate types.
//
//=================================================================================================

//=============================================================================
//
// Degree
//
//=============================================================================

//=============================================================================
Degree::Degree ()
{
}

//=============================================================================
Degree::Degree (float32 value) :
    m_value(value)
{
}

//=============================================================================
Degree::Degree (Radian rad) :
    m_value(rad * 180.0f / Math::Pi)
{
}

//=============================================================================
Degree::operator float32() const
{
    return m_value;
}

//=============================================================================
Degree & Degree::operator*= (float32 s)
{
    m_value *= s;
    return *this;
}

//=============================================================================
Degree & Degree::operator/= (float32 s)
{
    m_value /= s;
    return *this;
}

//=============================================================================
Degree & Degree::operator*= (const Degree & angle)
{
    m_value *= angle.m_value;
    return *this;
}

//=============================================================================
Degree & Degree::operator/= (const Degree & angle)
{
    m_value /= angle.m_value;
    return *this;
}

//=============================================================================
Degree & Degree::operator+= (const Degree & angle)
{
    m_value += angle.m_value;
    return *this;
}

//=============================================================================
Degree & Degree::operator-= (const Degree & angle)
{
    m_value -= angle.m_value;
    return *this;
}




//=============================================================================
//
// Radian
//
//=============================================================================

//=============================================================================
Radian::Radian () :
    m_value(0.0f)
{
}
//=============================================================================
Radian::Radian (float32 value) :
    m_value(value)
{
}

//=============================================================================
Radian::Radian (Degree deg) :
    m_value(deg * Math::Pi / 180.0f)
{
}

//=============================================================================
Radian::operator float32 () const
{
    return m_value;
}

//=============================================================================
Radian & Radian::operator*= (float32 s)
{
    m_value *= s;
    return *this;
}

//=============================================================================
Radian & Radian::operator/= (float32 s)
{
    m_value /= s;
    return *this;
}

//=============================================================================
Radian & Radian::operator*= (const Radian & angle)
{
    m_value *= angle.m_value;
    return *this;
}

//=============================================================================
Radian & Radian::operator/= (const Radian & angle)
{
    m_value /= angle.m_value;
    return *this;
}

//=============================================================================
Radian & Radian::operator+= (const Radian & angle)
{
    m_value += angle.m_value;
    return *this;
}

//=============================================================================
Radian & Radian::operator-= (const Radian & angle)
{
    m_value -= angle.m_value;
    return *this;
}



//=============================================================================
//
// Operators
//
//=============================================================================

Radian operator+ (Radian a,     Radian b)       { return Radian(float32(a) + float32(b)); }
Radian operator- (Radian a,     Radian b)       { return Radian(float32(a) - float32(b)); }
Radian operator* (Radian ang,   float32 x )     { return Radian(float32(ang) * x); }
Radian operator/ (Radian ang,   float32 x )     { return Radian(float32(ang) / x); }
Radian operator+ (Radian ang,   float32 x )     { return Radian(float32(ang) + x); }
Radian operator- (Radian ang,   float32 x )     { return Radian(float32(ang) - x); }
Radian operator* (float32 x,    Radian ang )    { return Radian(x * float32(ang)); }
Radian operator/ (float32 x,    Radian ang )    { return Radian(x / float32(ang)); }
Radian operator+ (float32 x,    Radian ang )    { return Radian(x + float32(ang)); }
Radian operator- (float32 x,    Radian ang )    { return Radian(x - float32(ang)); }

Degree operator+ (Degree a,     Degree b)       { return Degree(float32(a) + float32(b)); }
Degree operator- (Degree a,     Degree b)       { return Degree(float32(a) - float32(b)); }
Degree operator* (Degree ang,   float32 x )     { return Degree(float32(ang) * x); }
Degree operator/ (Degree ang,   float32 x )     { return Degree(float32(ang) / x); }
Degree operator+ (Degree ang,   float32 x )     { return Degree(float32(ang) + x); }
Degree operator- (Degree ang,   float32 x )     { return Degree(float32(ang) - x); }
Degree operator* (float32 x,    Degree ang )    { return Degree(x * float32(ang)); }
Degree operator/ (float32 x,    Degree ang )    { return Degree(x / float32(ang)); }
Degree operator+ (float32 x,    Degree ang )    { return Degree(x + float32(ang)); }
Degree operator- (float32 x,    Degree ang )    { return Degree(x - float32(ang)); }
