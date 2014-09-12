
//*****************************************************************************
//
// TCurve
//
//*****************************************************************************

template <typename Point>
class TCurve
{
public:
    TCurve ();

    inline bool IsClosed () const;
    inline float32 Length () const;
    inline bool IsValid () const;

protected:
    float32 CorrectDistance (float32 dist) const;

    TArray<Point> m_points;
    float32       m_length;
    bool          m_isClosed;
};



//*****************************************************************************
//
// LinearPath
//
//*****************************************************************************

template <typename Point, typename Vector, typename Segment>
class TLinearCurve : public TCurve<Point>
{
public:

    //TLinearCurve ();
    //TLinearPath (const TArray<Point> & points);

    Point Eval (float32 dist);
    void Set (const TArray<Point> & points);

    float32 Closest (const Point & point) const;

private:

    void ComputeLength ();
};

typedef TLinearCurve<Point2, Vector2, Segment2> LinearPath2;
typedef TLinearCurve<Point3, Vector3, Segment3> LinearPath3;



//*****************************************************************************
//
// TQuadraticCurve
//
//*****************************************************************************

template <typename Point, typename Vector>
class TQuadraticCurve : public TCurve<Point>
{
public:
    TQuadraticCurve () {}
    TQuadraticCurve (const Point & p0, const Point & p1, const Point & p2) :
        m_p0(p0),
        m_p1(p1),
        m_p2(p2)
    {}

    Point Eval (float32 t) const
    {
        return Lerp(
            Lerp(m_p0, m_p1, t),
            Lerp(m_p1, m_p2, t),
            t
        );
    }

    void Set (const Point & p0, const Point & p1, const Point & p2)
    {
        m_p0 = p0;
        m_p1 = p1;
        m_p2 = p2;
    }

//private:

    Point m_p0;
    Point m_p1;
    Point m_p2;
};

typedef TQuadraticCurve<Point2, Vector2> QuadraticCurve2;
typedef TQuadraticCurve<Point3, Vector3> QuadraticCurve3;



//*****************************************************************************
//
// TCubicCurve
//
//*****************************************************************************

template <typename Point, typename Vector>
class TCubicCurve : public TCurve<Point>
{
public:
    TCubicCurve () {}
    TCubicCurve (const Point & p0, const Point & p1, const Point & p2, const Point & p3) :
        m_p0(p0),
        m_p1(p1),
        m_p2(p2),
        m_p3(p3)
    {}

    TCubicCurve (const Point & p0, const Vector & v0, const Point & p1, const Vector & v1) :
        m_p0(p0),
        m_p1(p0 + v0),
        m_p2(p1 - v1),
        m_p3(p1)
    {}

    Point Eval (float32 t) const
    {
        const Point a = Lerp(
            Lerp(m_p0, m_p1, t),
            Lerp(m_p1, m_p2, t),
            t
        );
        const Point b = Lerp(
            Lerp(m_p1, m_p2, t),
            Lerp(m_p2, m_p3, t),
            t
        );
        return Lerp(a, b, t);
    }

    void Set (const Point & p0, const Point & p1, const Point & p2, const Point & p3)
    {
        m_p0 = p0;
        m_p1 = p1;
        m_p2 = p2;
        m_p3 = p3;
    }

//private:

    Point m_p0;
    Point m_p1;
    Point m_p2;
    Point m_p3;
};

typedef TCubicCurve<Point2, Vector2> CubicCurve2;
typedef TCubicCurve<Point3, Vector3> CubicCurve3;