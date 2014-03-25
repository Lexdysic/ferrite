
class Polygon2
{
    Polygon2 () = default;
    Polygon2 (const TArray<Point2> & points);

    float32 ComputeArea () const;
    Point2 ComputeCentroid () const;

    TArray<Point2> points;
};