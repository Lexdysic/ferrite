

//*****************************************************************************
//
// TCurve
//
//*****************************************************************************

//=============================================================================
template <typename Point>
TCurve<Point>::TCurve () :
    m_length(0.0f),
    m_isClosed(false)
{

}

//=============================================================================
template <typename Point>
bool TCurve<Point>::IsClosed () const
{
    return m_isClosed;
}

//=============================================================================
template <typename Point>
float32 TCurve<Point>::Length () const
{
    return m_length;
}

//=============================================================================
template <typename Point>
bool TCurve<Point>::IsValid () const
{
    return m_points.Count() >= 2;
}

//=============================================================================
template <typename Point>
float32 TCurve<Point>::CorrectDistance (float32 dist) const
{
    if (m_isClosed)
        return Mod(dist, m_length);
    else
        return Clamp(dist, 0.0f, m_length);
}



//*****************************************************************************
//
// LinearCurve
//
//*****************************************************************************

//=============================================================================
template <typename Point, typename Vector, typename Segment>
Point TLinearCurve<Point, Vector, Segment>::Eval (float32 destDist)
{
    destDist = CorrectDistance(destDist);
    
    float32 currDist = 0.01f;

    Point * lastPoint = m_points.Ptr();
    Point * currPoint = m_points.Ptr() + 1;
    Point * termPoint = m_points.Term();
    for ( ; currPoint < termPoint; lastPoint = currPoint, ++currPoint)
    {
        const float32 segmentDist = Distance(*lastPoint, *currPoint);
        if (currDist + segmentDist >= destDist)
        {
            const float inSegment = destDist - currDist;
            const float t = inSegment / segmentDist;
            return Lerp(*lastPoint, *currPoint, t);
        }
        currDist += segmentDist;
    }

    if (m_isClosed)
    {
        lastPoint = m_points.Top();
        currPoint = m_points.Ptr();

        const float32 segmentDist = Distance(*lastPoint, *currPoint);
        
        const float inSegment = destDist - currDist;
        const float t = inSegment / segmentDist;
        return Lerp(*lastPoint, *currPoint, t);
    }

    FATAL_EXIT("Surpassed extents of curve");
}

//=============================================================================
template <typename Point, typename Vector, typename Segment>
void TLinearCurve<Point, Vector, Segment>::ComputeLength ()
{
    m_length = 0.0f;

    if (m_points.Count() <= 1)
        return;

    Point * lastPoint = m_isClosed ? m_points.Top() : m_points.Ptr();
    Point * currPoint = m_isClosed ? m_points.Ptr() : (m_points.Ptr() + 1);
    Point * termPoint = m_points.Term();
    for ( ; currPoint < termPoint; lastPoint = currPoint, ++currPoint)
    {
        m_length += Distance(*lastPoint, *currPoint);
    }
}

//=============================================================================
template <typename Point, typename Vector, typename Segment>
void TLinearCurve<Point, Vector, Segment>::Set (const TArray<Point> & points)
{
    m_points = points;
    ComputeLength();
}

//=============================================================================
template <typename Point, typename Vector, typename Segment>
float32 TLinearCurve<Point, Vector, Segment>::Closest (const Point & point) const
{
    float32 closestDistSq = FLT_MAX;
    float32 bestDist = 0.0f;


    float32 currDist = 0.0f;

    const Point * lastPoint = m_points.Ptr();
    const Point * currPoint = m_points.Ptr() + 1;
    const Point * termPoint = m_points.Term();

    auto test = [&]()
    {
        const Point & closest = ::Closest(point, Segment(*lastPoint, *currPoint));
        const float32 distSq = DistanceSq(closest, point);
        if (distSq < closestDistSq)
        {
            closestDistSq = distSq;
            bestDist = currDist + Distance(*lastPoint, closest);
        }
    };


    for ( ; currPoint < termPoint; lastPoint = currPoint, ++currPoint)
    {
        test();
        //const Point & closest = Closest(point, Segment(*lastPoint, *currPoint));
        //const float32 distSq = DistanceSq(closest, point);
        //if (distSq < closestDistSq)
        //{
        //    closestDistSq = distSq;
        //    bestDist = currDist + Distance(*lastPoint, closest);
        //}
        currDist += Distance(*lastPoint, *currPoint);
    }

    if (m_isClosed)
    {
        lastPoint = m_points.Top();
        currPoint = m_points.Ptr();

        test();
        //const Point & closest = Closest(point, Segment(*lastPoint, *currPoint));
        //const float32 distSq = DistanceSq(closest, point);
        //if (distSq < closestDistSq)
        //{
        //    closestDistSq = distSq;
        //    bestDist = currDist + Distance(*lastPoint, closest);
        //}
    }

    return bestDist;
}
