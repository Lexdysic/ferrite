#include "MathPch.h"

//*****************************************************************************
//
// Random
//
//*****************************************************************************

//=============================================================================
void Random::Seed (uint32 seed)
{
    m_mt[0] = seed;
    for (uint i = 1; i < array_size(m_mt); ++i)
    {
        const uint32 last = m_mt[i - 1];
        m_mt[i] = uint32(0x6c078965 * (last ^ (last >> 30))  + i);
    }
}

//=============================================================================
void Random::GenerateNumbers() const
{
    for( uint i = 0; i < array_size(m_mt); ++i )
    {
        uint32 y = (m_mt[i] & 0x80000000) + m_mt[(i+1) % array_size(m_mt)] & 0xEFFFFFFF;
        m_mt[i] = m_mt[(i + 397) % array_size(m_mt)] ^ (y >> 1);
        if (y & 1)
            m_mt[i] ^= 0x9908b0df;
     }

}