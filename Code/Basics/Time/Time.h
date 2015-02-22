#ifndef BASICS_TIME_H
#define BASICS_TIME_H

namespace Time
{

//*****************************************************************************
//
// Forwards
//
//*****************************************************************************

class Point;
class Delta;


//*****************************************************************************
//
// Point
//
//*****************************************************************************

class Point
{
public: // Construction

    Point ();
    Point (const Point & rhs);
    explicit Point (float64 time);

public: // Accessors

    float64 GetRaw () const { return m_time; }

public: // Operators

    Point & operator+= (const Delta & rhs);
    Point & operator-= (const Delta & rhs);
    Point & operator*= (const Delta & rhs);
    Point & operator/= (const Delta & rhs);

private: // Data

    float64 m_time;
};



//*****************************************************************************
//
// Delta
//
//*****************************************************************************

class Delta
{
public: // Construction

    Delta ();
    Delta (const Delta & rhs);
    explicit Delta (float64 seconds);

    Delta & operator= (const Delta & rhs);

public: // Conversion

	explicit operator float32 () const { return float32(m_duration); }
    explicit operator float64 () const { return m_duration; }
    explicit operator uint () const { return FloatToUint(m_duration); }
    float64 GetRaw () const { return m_duration; }
    float32 GetSeconds () const { return (float32)m_duration; }

public: // Operations

    Delta & operator+= (const Delta & rhs);
    Delta & operator-= (const Delta & rhs);
    Delta & operator*= (const Delta & rhs);
    Delta & operator/= (const Delta & rhs);

protected: // Data

    float64 m_duration;
};



//*****************************************************************************
//
// Seconds
//
//*****************************************************************************

class Seconds :
    public Delta
{
public:
    using Delta::Delta;
    Seconds (float64 seconds);
    Seconds (uint seconds);
    Seconds (sint seconds);
};



//*****************************************************************************
//
// Ms
//
//*****************************************************************************

class Ms :
    public Delta
{
public:
    using Delta::Delta;
    Ms (const Delta & delta) : Delta(delta) {} // This is temporary until Inheriting Constructors works properly
    Ms (float64 ms);
    Ms (uint ms);
    Ms (sint ms);

    static const uint MS_PER_SECOND = 1000;

	explicit operator float32 () const { return float32(m_duration * MS_PER_SECOND); }
    explicit operator float64 () const { return m_duration * MS_PER_SECOND; }
    explicit operator uint () const { return FloatToUint(m_duration * MS_PER_SECOND); }
};



//*****************************************************************************
//
// Minutes
//
//*****************************************************************************

class Minutes :
    public Delta
{
public:
    Minutes (float64 mins);
    Minutes (uint mins);
    Minutes (sint mins);
};



//*****************************************************************************
//
// Operations
//
//*****************************************************************************

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

Delta Min (Delta a, Delta b);
Delta Max (Delta a, Delta b);



//*****************************************************************************
//
// Functions
//
//*****************************************************************************

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
void    SetGamePaused (bool paused);

} // namespace Time



//*****************************************************************************
//
// CRealTimer
//
//*****************************************************************************

class CRealTimer
{
public:
    CRealTimer ();

    Time::Delta Reset ();
    Time::Delta Elapsed ();

private:
    Time::Point m_lastTime;
};



//*****************************************************************************
//
// CGameTimer
//
//*****************************************************************************

class CGameTimer
{
public:
    CGameTimer ();

    Time::Delta Reset ();
    Time::Delta Elapsed ();

private:
    Time::Point m_lastTime;
};

#endif // BASICS_TIME_H