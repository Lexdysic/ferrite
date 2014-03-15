
#include "TimePch.h"

#pragma comment(lib, "Winmm.lib")

namespace Time
{



//==================================================================================================
//
// Constants
//
//==================================================================================================

const float SECONDS_PER_MINUTE = 60.0f;
const float SECONDS_PER_MILLI = 1.0f / 1000.0f;



//==================================================================================================
//
// Internal State
//
//==================================================================================================

static LARGE_INTEGER s_frequency;

static Point    s_framePoint;
static Delta    s_frameDelta;

static Point    s_gamePoint;
static Delta    s_gameDelta;
static float32  s_gameScale = 1.0f;

//struct CManager
//{
//    CManager ();
//
//    void Initialize ();
//    void Uninitialize ();
//    void Update ();
//
//    LARGE_INTEGER   m_frequency;
//    bool            m_isInitialized;
//    CRealTimer          m_realTimer;
//};
//
//static Manager s_manager;


//==================================================================================================
//
// Point
//
//==================================================================================================

//=============================================================================
Point::Point () :
    m_time(0.0f)
{
}

//=============================================================================
Point::Point (const Point & rhs) :
    m_time(rhs.m_time)
{
}

//=============================================================================
Point::Point (float64 time) :
    m_time(time)
{
}

//=============================================================================
Point & Point::operator+= (const Delta & rhs)
{
    m_time += rhs.GetRaw();
    return *this;
}

//=============================================================================
Point & Point::operator-= (const Delta & rhs)
{
    m_time -= rhs.GetRaw();
    return *this;
}

//=============================================================================
Point & Point::operator*= (const Delta & rhs)
{
    m_time *= rhs.GetRaw();
    return *this;
}

//=============================================================================
Point & Point::operator/= (const Delta & rhs)
{
    m_time /= rhs.GetRaw();
    return *this;
}



//==================================================================================================
//
// Duration
//
//==================================================================================================

//=============================================================================
Delta::Delta () :
    m_duration(0.0f)
{
}

//=============================================================================
Delta::Delta (const Delta & rhs) :
    m_duration(rhs.m_duration)
{
}

//=============================================================================
Delta::Delta (float64 seconds) :
    m_duration(seconds)
{
}

//=============================================================================
Delta & Delta::operator= (const Delta & rhs)
{
    m_duration = rhs.m_duration;
    return *this;
}

//=============================================================================
Delta & Delta::operator+= (const Delta & rhs)
{
    m_duration += rhs.m_duration;
    return *this;
}

//=============================================================================
Delta & Delta::operator-= (const Delta & rhs)
{
    m_duration -= rhs.m_duration;
    return *this;
}

//=============================================================================
Delta & Delta::operator*= (const Delta & rhs)
{
    m_duration *= rhs.m_duration;
    return *this;
}

//=============================================================================
Delta & Delta::operator/= (const Delta & rhs)
{
    m_duration /= rhs.m_duration;
    return *this;
}



//==================================================================================================
//
// Seconds
//
//==================================================================================================

//=============================================================================
Seconds::Seconds (float64 seconds) :
    Delta(seconds)
{
}

//=============================================================================
Seconds::Seconds (uint seconds) :
    Delta(seconds)
{
}

//=============================================================================
Seconds::Seconds (sint seconds) :
    Delta(seconds)
{
}



//==================================================================================================
//
// Ms
//
//==================================================================================================

//=============================================================================
Ms::Ms (float64 ms) :
    Delta(ms * SECONDS_PER_MILLI)
{
}

//=============================================================================
Ms::Ms (uint ms) :
    Delta(ms * SECONDS_PER_MILLI)
{
}

//=============================================================================
Ms::Ms (sint ms) :
    Delta(ms * SECONDS_PER_MILLI)
{
}



//==================================================================================================
//
// Minutes
//
//==================================================================================================

//=============================================================================
Minutes::Minutes (float64 ms) :
    Delta(ms * SECONDS_PER_MINUTE)
{
}

//=============================================================================
Minutes::Minutes (uint ms) :
    Delta(ms * SECONDS_PER_MINUTE)
{
}

//=============================================================================
Minutes::Minutes (sint ms) :
    Delta(ms * SECONDS_PER_MINUTE)
{
}




//==================================================================================================
//
// Operations
//
//==================================================================================================

//=============================================================================
Delta operator- (const Point & a, const Point & b)
{
    return Delta(a.GetRaw() - b.GetRaw());
}

//=============================================================================
Point operator+ (const Point & p, const Delta & d)
{
    return Point(p.GetRaw() + d.GetRaw());
}

//=============================================================================
Point operator+ (const Delta & d, const Point & p)
{
    return Point(p.GetRaw() + d.GetRaw());
}

//=============================================================================
Delta operator+ (const Delta & a, const Delta & b)
{
    return Delta(a.GetRaw() + b.GetRaw());
}


//=============================================================================
Delta operator* (float64 scalar, const Delta & d)
{
    return Delta(d.GetRaw() * scalar);
}

//=============================================================================
Delta operator* (const Delta & d, float64 scalar)
{
    return Delta(d.GetRaw() * scalar);
}

//=============================================================================
Delta operator/ (const Delta & d, float64 scalar)
{
    return Delta(d.GetRaw() / scalar);
}

//=============================================================================
bool operator < (const Delta & a, const Delta & b)
{
    return a.GetRaw() < b.GetRaw();
}

//=============================================================================
bool operator <= (const Delta & a, const Delta & b)
{
    return a.GetRaw() <= b.GetRaw();
}

//=============================================================================
bool operator > (const Delta & a, const Delta & b)
{
    return a.GetRaw() > b.GetRaw();
}

//=============================================================================
bool operator >= (const Delta & a, const Delta & b)
{
    return a.GetRaw() >= b.GetRaw();
}

//=============================================================================
bool operator == (const Delta & a, const Delta & b)
{
   return a.GetRaw() == b.GetRaw();
}

//=============================================================================
bool operator != (const Delta & a, const Delta & b)
{
    return a.GetRaw() != b.GetRaw();
}



//==================================================================================================
//
// API Functions
//
//==================================================================================================

//=============================================================================
AUTO_INIT_FUNC(TimeInit)
{
    ::QueryPerformanceFrequency(&s_frequency);
    timeBeginPeriod(1);
    
    s_framePoint = GetRealTime();
}

//=============================================================================
void Uninitialize ()
{
    timeEndPeriod(1);
}

//=============================================================================
void Update ()
{

    Point lastPoint = s_framePoint;
    s_framePoint = GetRealTime();
    s_frameDelta = s_framePoint - lastPoint;

    s_gameDelta = s_frameDelta * s_gameScale;
    s_gamePoint += s_gameDelta;
}

//=============================================================================
Point GetRealTime ()
{
    LARGE_INTEGER time;
    ::QueryPerformanceCounter(&time);

    const float64 f = static_cast<float64>(time.QuadPart) / static_cast<float64>(s_frequency.QuadPart);

    return Point(f);
}

//=============================================================================
Point GetFrameTime ()
{
    return s_framePoint;
}

//=============================================================================
Delta GetFrameDelta ()
{
    return s_frameDelta;
}

//=============================================================================
Point GetGameTime ()
{
    return s_gamePoint;
}

//=============================================================================
float GetGameScale ()
{
    return s_gameScale;
}

//=============================================================================
Delta GetGameDelta ()
{
    return s_gameDelta;
}

//=============================================================================
void SetGameScale (float32 scale)
{
    s_gameScale = Max(scale, 0.0f);
}

//=============================================================================
bool IsGamePaused ()
{
    return s_gameScale == 0.0f;
}

} // namespace Time


//==================================================================================================
//
// CRealTimer
//
//==================================================================================================

//=============================================================================
CRealTimer::CRealTimer ()
{
    Reset();
}

//=============================================================================
Time::Delta CRealTimer::Reset ()
{
    const Time::Point currentTime = Time::GetRealTime();
    const Time::Delta delta = currentTime - m_lastTime;
    m_lastTime = currentTime;
    return delta;
}

//=============================================================================
Time::Delta CRealTimer::Elapsed ()
{
    const Time::Point currentTime = Time::GetRealTime();
    const Time::Delta delta = currentTime - m_lastTime;
    return delta;
}


//==================================================================================================
//
// CGameTimer
//
//==================================================================================================

//=============================================================================
CGameTimer::CGameTimer ()
{
    Reset();
}

//=============================================================================
Time::Delta CGameTimer::Reset ()
{
    const Time::Point currentTime = Time::GetGameTime();
    const Time::Delta delta = currentTime - m_lastTime;
    m_lastTime = currentTime;
    return delta;
}

//=============================================================================
Time::Delta CGameTimer::Elapsed ()
{
    const Time::Point currentTime = Time::GetGameTime();
    const Time::Delta delta = currentTime - m_lastTime;
    return delta;
}
