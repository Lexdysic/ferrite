
//*****************************************************************************
//
// Random
//
//*****************************************************************************

//=============================================================================
Random::Random() :
    m_index(0)
{
    Seed(11232387);
}

//=============================================================================
Random::Random (uint32 seed) :
    m_index(0)
{
    Seed(seed);
}

//=============================================================================
template <typename T>
T Random::Range (const T & min, const T & max) const   
{ 
    return static_cast<T>(static_cast<T>((max - min) * GetFloat32()) + min); 
}

//=============================================================================
template<typename T>
T Random::Max (const T & max) const 
{
    return ExtractBits<T>();
}

//=============================================================================
template<>
float32 Random::Max (const float32 & max) const 
{
    return GetFloat32() * max;
}

//=============================================================================
template<>
uint32 Random::Max (const uint32 & max) const 
{
    return static_cast<uint32>(GetFloat32() * max);
}

//=============================================================================
template<>
sint32 Random::Max (const sint32 & max) const 
{
    return static_cast<sint32>(GetFloat32() * max);
}

//=============================================================================
float64 Random::GetFloat64 () const
{
    return static_cast<float64>(GetU32()) / static_cast<float64>(std::numeric_limits<uint32>::max()); 
}

//=============================================================================
float32 Random::GetFloat32 () const 
{ 
    return static_cast<float32>(GetU32()) / static_cast<float32>(std::numeric_limits<uint32>::max()); 
}

//=============================================================================
float32 Random::GetFloat32Exclusive () const
{
    return static_cast<float32>(GetU32()) / static_cast<float32>(std::numeric_limits<uint32>::max()+1LL); 
}

//=============================================================================
uint32 Random::GetU32 () const 
{ 
    return ExtractBits<uint32>(); 
}

//=============================================================================
sint32 Random::GetS32 () const 
{ 
    return ExtractBits<sint32>(); 
}
 
//=============================================================================
template<typename T>
T Random::ExtractBits () const
{
    if (m_index == 0)
        GenerateNumbers();
     
     uint32 y = m_mt[m_index];
     y ^= (y >> 11);
     y ^= (y <<  7) & 0x9d2c5680;
     y ^= (y << 15) & 0xefc60000;
     y ^= (y >> 18);
     
     m_index = (m_index + 1) % array_size(m_mt);

     return (T)( y );
}