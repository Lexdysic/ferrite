namespace Math
{

const float32 Epsilon   = std::numeric_limits<float32>::epsilon();
const float32 Infinity  = std::numeric_limits<float32>::infinity();
const float32 E         = 2.71828182845904523536f;
const float32 Pi        = 3.14159265358979323846f;
const float32 Tau       = 2.0f * Pi;
const float32 HalfPi    = 0.5f * Pi;
const sint    MaxUlps   = 32;

} // namespace Math


enum EAxis
{
    AXIS_X = 0,
    AXIS_Y = 1,
    AXIS_Z = 2,
    AXES
};
