namespace Time
{

class Point;
class Delta;


//==================================================================================================
//
// Point
//
//==================================================================================================

class Point
{
public:

    Point ();
    Point (const Point & rhs);
    explicit Point (float64 time);

    float64 GetRaw () const { return m_time; }

    Point & operator+= (const Delta & rhs);
    Point & operator-= (const Delta & rhs);
    Point & operator*= (const Delta & rhs);
    Point & operator/= (const Delta & rhs);

private:

    float64 m_time;
};


//==================================================================================================
//
// Delta
//
//==================================================================================================

class Delta
{
public:

    // Construction
    Delta ();
    Delta (const Delta & rhs);
    explicit Delta (float64 seconds);

    Delta & operator= (const Delta & rhs);

    // Conversion
	explicit operator float32 () const { return float32(m_duration); }
    explicit operator float64 () const { return m_duration; }
    float64 GetRaw () const { return m_duration; }
    float32 GetSeconds () const { return (float32)m_duration; }

    // Operations
    Delta & operator+= (const Delta & rhs);
    Delta & operator-= (const Delta & rhs);
    Delta & operator*= (const Delta & rhs);
    Delta & operator/= (const Delta & rhs);

private:

    float64 m_duration;
};



//==================================================================================================
//
// Seconds
//
//==================================================================================================

class Seconds :
    public Delta
{
public:
    Seconds (float64 seconds);
    Seconds (uint seconds);
    Seconds (sint seconds);
};




//==================================================================================================
//
// Ms
//
//==================================================================================================

class Ms :
    public Delta
{
public:
    Ms (float64 ms);
    Ms (uint ms);
    Ms (sint ms);
};




//==================================================================================================
//
// Minutes
//
//==================================================================================================

class Minutes :
    public Delta
{
public:
    Minutes (float64 mins);
    Minutes (uint mins);
    Minutes (sint mins);
};



//==================================================================================================
//
// Operations
//
//==================================================================================================

Delta operator- (const Point & a, const Point & b);
Point operator+ (const Point & p, const Delta & d);
Point operator+ (const Delta & d, const Point & p);
Delta operator+ (const Delta & a, const Delta & b);

Delta operator* (float64 scalar, const Delta & d);
Delta operator* (const Delta & a, float64 scalar);
Delta operator/ (const Delta & a, float64 scalar);

bool operator <  (const Delta & a, const Delta & b);
bool operator <= (const Delta & a, const Delta & b);
bool operator >  (const Delta & a, const Delta & b);
bool operator >= (const Delta & a, const Delta & b);
bool operator == (const Delta & a, const Delta & b);
bool operator != (const Delta & a, const Delta & b);



//==================================================================================================
//
// API Functions
//
//==================================================================================================

void Update ();

// Real-time
Point GetRealTime ();

// Frame-time
Point GetFrameTime ();
Delta GetFrameDelta ();

// Game-time
Point   GetGameTime ();
float32 GetGameScale ();
void    SetGameScale (float32 scale);
Delta   GetGameDelta ();
bool    IsGamePaused ();

} // namespace Time



//==================================================================================================
//
// CRealTimer
//
//==================================================================================================

class CRealTimer
{
public:
    CRealTimer ();

    Time::Delta Reset ();
    Time::Delta Elapsed ();

private:
    Time::Point m_lastTime;
};



//==================================================================================================
//
// CGameTimer
//
//==================================================================================================

class CGameTimer
{
public:
    CGameTimer ();

    Time::Delta Reset ();
    Time::Delta Elapsed ();

private:
    Time::Point m_lastTime;
};