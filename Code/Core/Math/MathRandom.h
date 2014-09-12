#ifdef MATHRANDOM_H
#  error "Cannot include header more than once."
#endif
#define MATHRANDOM_H

//*****************************************************************************
//
// Random
//
//*****************************************************************************

class Random
{
public: // Construction

    inline Random ();
    inline Random (uint32 seed);

    void Seed (uint32 seed);

public: // Generators

    template<typename T> inline T Range (const T & min, const T & max) const;  

    template<typename T> inline T   Max (const T & max)  const;
    template<>           inline float32 Max (const float32 & max) const;
    template<>           inline uint32 Max (const uint32 & max) const;
    template<>           inline sint32 Max (const sint32 & max) const;

    template <typename T>
    inline T Get () const; // TODO: implement specializations, remove functions below

    inline float64 GetFloat64() const;
    inline float32 GetFloat32() const;
    inline float32 GetFloat32Exclusive() const;
    inline uint32 GetU32() const;
    inline sint32 GetS32() const;

private: // Helpers

    template<typename T>
    T ExtractBits() const;
    void GenerateNumbers() const;

private: // Data

    mutable uint32 m_mt[624];
    mutable uint32 m_index;
};