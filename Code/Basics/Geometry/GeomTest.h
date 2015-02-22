namespace Geometry
{

enum class TestResult
{
    Inside,
    Outside,
    Straddle,
    On = Straddle
};


inline TestResult Test (const Point2 & point, const Plane2 & plane);

inline TestResult Test (const Sphere3 & sphere, const Plane3 & plane);
inline TestResult Test (const Obb3 & box, const Plane3 & plane);
inline TestResult Test (const Aabb3 & box, const Plane3 & plane);

} // namespace Geometry
