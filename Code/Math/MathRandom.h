//==================================================================================================
//
// File:    MathRandom.h
// Author:  Jason Jackson
// Date:    September 20, 2008
//
// Produces pseudo random numbers
//
//==================================================================================================

#ifdef MATHRANDOM_H
#  error "Cannot include header more than once."
#endif
#define MATHRANDOM_H

//=============================================================================
//
// Class which will generate psuedo random numbers
//
//=============================================================================
class Random
{
public:
    inline Random ();
    inline Random (uint32 seed);

    //! seeds the gerator to a new state
    void Seed (uint32 seed);

    //! generates in the range [min, max]
    template<typename T> inline T Range( const T & min, const T & max ) const;  
    // TODO: make specializations of Range()

    template<typename T> inline T   Max( const T & max )  const;    //!< generates a type in the range [0, max]
    template<>           inline float32 Max( const float32 & max) const;    //!< generates a float32 in the range [0.0f, max]
    template<>           inline uint32 Max( const uint32 & max) const;    //!< generates a uint32 in the range [0, max]
    template<>           inline sint32 Max( const sint32 & max) const;    //!< generates an sint32 in the range [0, max]

    inline float64 GetFloat64() const;
    inline float32 GetFloat32() const;              //!< generates a float32 in the range [0, 1]
    inline float32 GetFloat32Exclusive() const;     //!< generates a float32 in the range [0, 1)
    inline uint32 GetU32() const;              //!< generates a uint32 in the range [0, maxU32]
    inline sint32 GetS32() const;              //!< generates an sint32 in the range [minS32, maxS32]

private:
    static const uint32 sDimensions = 624;

    //! will generate 4 bytes of randomized bits
    template<typename T>
    T ExtractBits() const;

    //! generates a new state array
    void GenerateNumbers() const;

    mutable uint32     mMt[sDimensions];   //!< represents the current state of the generator
    mutable uint32     mIndex;             //!< index into mMt used in retreival
};