#include "MathPch.h"

//=============================================================================
template<>
inline Vector2s FloorCast (const Vector2 & v)
{
    return Vector2s(
        FloorCast<sint>(v.x),
        FloorCast<sint>(v.y)
    );
}

//=============================================================================
template<>
inline Vector3s FloorCast (const Vector3 & v)
{
    return Vector3s(
        FloorCast<sint>(v.x),
        FloorCast<sint>(v.y),
        FloorCast<sint>(v.z)
    );
}



namespace Math {
namespace Noise {

//*****************************************************************************
//
// Permute
//
//*****************************************************************************

static const sint s_permute[] = 
{
  151, 160, 137,  91,  90,  15, 131,  13, 201,  95,  96,  53, 194, 233,   7, 225,
  140,  36, 103,  30,  69, 142,   8,  99,  37, 240,  21,  10,  23, 190,   6, 148,
  247, 120, 234,  75,   0,  26, 197,  62,  94, 252, 219, 203, 117,  35,  11,  32,
   57, 177,  33,  88, 237, 149,  56,  87, 174,  20, 125, 136, 171, 168,  68, 175,
   74, 165,  71, 134, 139,  48,  27, 166,  77, 146, 158, 231,  83, 111, 229, 122,
   60, 211, 133, 230, 220, 105,  92,  41,  55,  46, 245,  40, 244, 102, 143,  54,
   65,  25,  63, 161,   1, 216,  80,  73, 209,  76, 132, 187, 208,  89,  18, 169,
  200, 196, 135, 130, 116, 188, 159,  86, 164, 100, 109, 198, 173, 186,   3,  64,
   52, 217, 226, 250, 124, 123,   5, 202,  38, 147, 118, 126, 255,  82,  85, 212,
  207, 206,  59, 227,  47,  16,  58,  17, 182, 189,  28,  42, 223, 183, 170, 213,
  119, 248, 152,   2,  44, 154, 163,  70, 221, 153, 101, 155, 167,  43, 172,   9,
  129,  22,  39, 253,  19,  98, 108, 110,  79, 113, 224, 232, 178, 185, 112, 104,
  218, 246,  97, 228, 251,  34, 242, 193, 238, 210, 144,  12, 191, 179, 162, 241,
   81,  51, 145, 235, 249,  14, 239, 107,  49, 192, 214,  31, 181, 199, 106, 157,
  184,  84, 204, 176, 115, 121,  50,  45, 127,   4, 150, 254, 138, 236, 205,  93,
  222, 114,  67,  29,  24,  72, 243, 141, 128, 195,  78,  66, 215,  61, 156, 180,

  // Double to allow offsets without modulus
  151, 160, 137,  91,  90,  15, 131,  13, 201,  95,  96,  53, 194, 233,   7, 225,
  140,  36, 103,  30,  69, 142,   8,  99,  37, 240,  21,  10,  23, 190,   6, 148,
  247, 120, 234,  75,   0,  26, 197,  62,  94, 252, 219, 203, 117,  35,  11,  32,
   57, 177,  33,  88, 237, 149,  56,  87, 174,  20, 125, 136, 171, 168,  68, 175,
   74, 165,  71, 134, 139,  48,  27, 166,  77, 146, 158, 231,  83, 111, 229, 122,
   60, 211, 133, 230, 220, 105,  92,  41,  55,  46, 245,  40, 244, 102, 143,  54,
   65,  25,  63, 161,   1, 216,  80,  73, 209,  76, 132, 187, 208,  89,  18, 169,
  200, 196, 135, 130, 116, 188, 159,  86, 164, 100, 109, 198, 173, 186,   3,  64,
   52, 217, 226, 250, 124, 123,   5, 202,  38, 147, 118, 126, 255,  82,  85, 212,
  207, 206,  59, 227,  47,  16,  58,  17, 182, 189,  28,  42, 223, 183, 170, 213,
  119, 248, 152,   2,  44, 154, 163,  70, 221, 153, 101, 155, 167,  43, 172,   9,
  129,  22,  39, 253,  19,  98, 108, 110,  79, 113, 224, 232, 178, 185, 112, 104,
  218, 246,  97, 228, 251,  34, 242, 193, 238, 210, 144,  12, 191, 179, 162, 241,
   81,  51, 145, 235, 249,  14, 239, 107,  49, 192, 214,  31, 181, 199, 106, 157,
  184,  84, 204, 176, 115, 121,  50,  45, 127,   4, 150, 254, 138, 236, 205,  93,
  222, 114,  67,  29,  24,  72, 243, 141, 128, 195,  78,  66, 215,  61, 156, 180
};

const int PERMUTE_LENGTH = array_size(s_permute) / 2;

//=============================================================================
static sint Permute (sint value)
{
    const sint index = Abs(value) % PERMUTE_LENGTH;
    return s_permute[index];
}



//*****************************************************************************
//
// Gradient
//
//*****************************************************************************

static const Vector2s s_gradient[] =
{
    { 0,  0}, { 0,  1}, { 0, -1},
    { 1,  0}, { 1,  1}, { 1, -1},
    {-1,  0}, {-1,  1}, {-1, -1},
};

const sint GRADIENT_LENGTH = array_size(s_gradient);



//*****************************************************************************
//
// Helpers
//
//*****************************************************************************


//=============================================================================
static float32 CubicInterp (const float32 a, const float32 b, float t)
{
    t = 3.0f * (t * t) - 2.0f * (t * t * t);
    return Lerp(a, b, t);
}

//=============================================================================
static float32 QuinticInterp (const float32 a, const float32 b, float32 t)
{
    t = t * t * t * (t * (t * 6 - 15) + 10);
    return Lerp(a, b, t);
}

//=============================================================================
static float32 Interp (const float32 a, const float32 b, const float32 t)
{
    return CubicInterp(a, b, t);
}


//*****************************************************************************
//
// White
//
//*****************************************************************************

//=============================================================================
float32 White::Get (sint v)
{
    Hash32 hash(v);
    return uint32(hash) / float32(UINT32_MAX);
}

//=============================================================================
float32 White::Get (const Vector2s & v)
{
    Hash32 hash(v);
    return uint32(hash) / float32(UINT32_MAX);
}


//=============================================================================
float32 White::Get (float32 x)
{
    Hash32 hash(Floor(x));
    return uint32(hash) / float32(UINT32_MAX);
}

//=============================================================================
float32 White::Get (const Vector2 & v)
{
    Hash32 hash(Floor(v));
    return uint32(hash) / float32(UINT32_MAX);
}

//=============================================================================
float32 White::Get (const Vector3 & v)
{
    Hash32 hash(Floor(v));
    return uint32(hash) / float32(UINT32_MAX);
}

//=============================================================================
float32 White::Get (const Vector4 & v)
{
    Hash32 hash(Floor(v));
    return uint32(hash) / float32(UINT32_MAX);
}


//=============================================================================
float32 White::Get (float32 x, float32 y)
{
    return Get(Vector2(x, y));
}

//=============================================================================
float32 White::Get (float32 x, float32 y, float32 z)
{
    return Get(Vector3(x, y, z));
}

//=============================================================================
float32 White::Get (float32 x, float32 y, float32 z, float32 w)
{
    return Get(Vector4(x, y, z, w));
}


//*****************************************************************************
//
// Smoothed
//
//*****************************************************************************

//=============================================================================
float32 Smoothed::Get (float32 v)
{
    const sint    i = FloorCast<sint>(v);
    const float32 f = v - i;
    ASSERT(Math::IsInRange(f, 0.0f, 1.0f));

    const float32 w0 = White::Get(i);
    const float32 w1 = White::Get(i + 1);
    return Interp(w0, w1, f);
}

//=============================================================================
float32 Smoothed::Get (const Vector2 & v)
{
    const Vector2s i = FloorCast<Vector2s>(v);
    const float32 fx = v.x - i.x;
    const float32 fy = v.y - i.y;
    ASSERT(Math::IsInRange(fx, 0.0f, 1.0f));
    ASSERT(Math::IsInRange(fy, 0.0f, 1.0f));

    const float32 w00 = White::Get(i + Vector2s(0, 0));
    const float32 w01 = White::Get(i + Vector2s(1, 0));
    const float32 w10 = White::Get(i + Vector2s(0, 1));
    const float32 w11 = White::Get(i + Vector2s(1, 1));

    return Interp(
        Interp(w00, w01, fx),
        Interp(w10, w11, fx),
        fy
    );
}

//=============================================================================
float32 Smoothed::Get (const Vector3 & v)
{
    return 0;
}

//=============================================================================
float32 Smoothed::Get (const Vector4 & v)
{
    return 0;
}




//*****************************************************************************
//
// Perlin
//
//*****************************************************************************

namespace Perlin
{

//=============================================================================
template <typename T>
static float32 Get (
    const T &     v,
    const uint    octaves,
    const float32 persistence = 2.0f,
    const float32 lacunarity = 0.5f)
{
    float32 frequency = 1.0f;
    float32 amplitude = 1.0f;
    float32 total     = 0.0f;
    float32 max       = 0.0f;

    for (uint i = 0; i < octaves; ++i)
    {
        total += Smoothed::Get(v * frequency) * amplitude;
        max   += amplitude;

        frequency *= lacunarity;
        amplitude *= persistence;
    }

    return total / max;
}

} // namespace Perlin

//=============================================================================
float32 Perlin::Get (float32 v, uint octaves)
{
    return Get<float32>(v, octaves);
}

//=============================================================================
float32 Perlin::Get (const Vector2 & v, uint octaves)
{
    return Get<Vector2>(v, octaves);
}

//=============================================================================
float32 Perlin::Get (const Vector3 & v, uint octaves)
{
    return Get<Vector3>(v, octaves);
}

//=============================================================================
float32 Perlin::Get (const Vector4 & v, uint octaves)
{
    return Get<Vector4>(v, octaves);
}

//=============================================================================
float32 Perlin::Get (float32 x, float32 y, uint octaves)
{
    return Get(Vector2(x, y), octaves);
}

//=============================================================================
float32 Perlin::Get (float32 x, float32 y, float32 z, uint octaves)
{
    return Get(Vector3(x, y, z), octaves);
}

//=============================================================================
float32 Perlin::Get (float32 x, float32 y, float32 z, float32 w, uint octaves)
{
    return Get(Vector4(x, y, z, w), octaves);
}



//*****************************************************************************
//
// Simplex
//
//*****************************************************************************

namespace Simplex
{

//=============================================================================
const float32 SQRT_3 = Sqrt(3.0f);
const float32 F2 = 0.5f * (SQRT_3 - 1.0f);
const float32 G2 = (3.0f - SQRT_3) / 6.0f;

} // namespace Simplex

//=============================================================================
float32 Simplex::Get (float32 x, float32 y);
//{
//
//    const float32 SQRT_3 = Sqrt(3.0f);
//    const float32 SKEWER = (3.0f - SQRT_3) / 6.0f;
//
//    // Skew the input space to determine which cell we are in
//    const float32 f2 = 0.5f * (SQRT_3 - 1.0f);
//    const float32 s = (x + y) * f2;
//    const Vector2s cellIndex = {
//        FloatToSint(x + s),
//        FloatToSint(y + s)
//    };
//
//    const float32 t = (cellIndex.x + cellIndex.y) * SKEWER;
//    const Vector2 unskewed = {
//        cellIndex.x - t,
//        cellIndex.y - t
//    };
//    const Vector2 uv = {
//        x - unskewed.x,
//        y - unskewed.y
//    };
//
//    // Determine which simplex we are in
//    Vector2s simplex;
//    if (unskewed.x > unskewed.y)
//        simplex = { 1, 0 };
//    else
//        simplex = { 0, 1 };
//
//    const Vector2 middle = {
//        uv.x - simplex.x + SKEWER,
//        uv.y - simplex.y + SKEWER
//    };
//    const Vector2 last = {
//        uv.x - 1.0f + 2.0f * SKEWER,
//        uv.y - 1.0f + 2.0f * SKEWER
//    };
//
//
//    // Hashed gradients
//    const Vector2s hashed = {
//        cellIndex.x & 255,
//        cellIndex.y & 255
//    };
//
//    const int g0 = perm[hashed.x + perm[hashed.y]] % 12;
//    const int g1 = perm[hashed.x + simplex.x + perm[hashed.x + simplex.x]] % 12;
//    const int g2 = perm[hashed.x + 1 + perm[hashed.y + 1]] % 12;
//
//    // Calculate the corner contributions from the three corners
//    
//    float32 n0, n1, n2;
//    float32 t0 = 0.5f - LengthSq(uv);
//    if (t0 < 0.0f)
//    {
//        n0 = 0.0f;
//    }
//    else
//    {
//        t0 *= t0;
//        n0 = Sq(t0) * Dot()
//    }
//}

//=============================================================================
float32 Simplex::Get (float32 x, float32 y, float32 z);

//=============================================================================
float32 Simplex::Get (float32 x, float32 y, float32 z, float32 w);

}} // namespace Math::Noise