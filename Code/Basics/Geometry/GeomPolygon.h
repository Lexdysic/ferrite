
class Polygon2
{
public:
    Polygon2 () = default;
    Polygon2 (const TArray<Point2> & points);

    float32 ComputeArea () const;
    Point2 ComputeCentroid () const;
    void ComputeCentroidInfo (Point2 * centroid, float32 * area) const;
    Interval ProjectedIntervalAlongVector (const Vector2 & v) const;

public: // 

    static Polygon2 Clip (const Polygon2 & subjectPoly, const Polygon2 & clipPoly);

public: // data
    TArray<Point2> points;
};

