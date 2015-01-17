

namespace Math {
namespace Noise {



namespace White {
float32 Get (sint x);
float32 Get (const Vector2s & v);

float32 Get (float32 x);
float32 Get (float32 x, float32 y);
float32 Get (float32 x, float32 y, float32 z);
float32 Get (float32 x, float32 y, float32 z, float32 w);

float32 Get (const Vector2 & v);
float32 Get (const Vector3 & v);
float32 Get (const Vector4 & v);
} // namespace White






class CSmoothed
{
public:
    CSmoothed ();

public: //
    float32 Get (float32 x);
    float32 Get (const Vector2 & v);
    float32 Get (const Vector3 & v);
    float32 Get (const Vector4 & v);

private:
    uint32 m_seed;
};





namespace Smoothed
{
float32 Get (float32 x);
float32 Get (const Vector2 & v);
float32 Get (const Vector3 & v);
float32 Get (const Vector4 & v);
} // namespace Smoothed




class CPerlin
{
public:

private:
    CSmoothed m_smoothed;
    uint      m_octaves;
    float32   m_persistence;
    float32   m_lacunarity;
};

namespace Perlin {
float32 Get (float32 x, uint octaves = 7);
float32 Get (const Vector2 & v, uint octaves = 7);
float32 Get (const Vector3 & v, uint octaves = 7);
float32 Get (const Vector4 & v, uint octaves = 7);
float32 Get (float32 x, float32 y, uint octaves = 7);
float32 Get (float32 x, float32 y, float32 z, uint octaves = 7);
float32 Get (float32 x, float32 y, float32 z, float32 w, uint octaves = 7);
} // namespace Perlin




class CSimplex
{
};

namespace Simplex {
float32 Get (float32 x, float32 y);
float32 Get (float32 x, float32 y, float32 z);
float32 Get (float32 x, float32 y, float32 z, float32 w);
} // namespace Simplex



}} // namespace Math::Noise