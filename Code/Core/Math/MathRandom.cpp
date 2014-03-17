//==================================================================================================
//
// File:    MathRandom.cpp
// Author:  Jason Jackson
// Date:    September 20, 2008
//
// Random number generation using the mersenne twister functions
//
//==================================================================================================

#include "MathPch.h"

//=============================================================================
void Random::Seed( uint32 seed )
{
    mMt[0] = seed;
    for( uint i = 1; i< sDimensions; ++i )
    {
        const uint32 last = mMt[i-1];
        mMt[i] = uint32( 0x6c078965 * (last ^ (last >> 30) )  + i);
    }
}

//=============================================================================
void Random::GenerateNumbers() const
{
    for( uint i = 0; i < sDimensions; ++i )
    {
        uint32 y = (mMt[i] & 0x80000000) + mMt[(i+1) % 624] & 0xEFFFFFFF;
        mMt[i] = mMt[ (i + 397) % sDimensions] ^ (y >> 1);
        if( y & 1 )
            mMt[i] ^= 0x9908b0df;
     }

}