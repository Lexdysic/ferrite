
//*****************************************************************************
//
// Types
//
//*****************************************************************************

typedef uint32 ThreadId;



//*****************************************************************************
//
// Forwards
//
//*****************************************************************************

class Thread;
class CriticalSection;



//*****************************************************************************
//
// CThread
//
//*****************************************************************************

class CThread
{
public:
    virtual ~CThread ();
    
    void Start ();
    void Stop ();
    void Suspend ();
    void Resume ();
    bool IsRunning () const;

    virtual void ThreadEnter () pure;

private:

    ThreadId m_id;
    void *   m_handle;
};



//*****************************************************************************
//
// CriticalSection
//
//*****************************************************************************

class CriticalSection 
{
public:
    CriticalSection ();
    ~CriticalSection ();

    bool TryEnter ();
    void Enter ();
    void Leave ();
    
    static const uint DATA_SIZE = 32;

private:

    uint8 m_data[DATA_SIZE];
};



//*****************************************************************************
//
// Lockable
//
//*****************************************************************************

class Lockable : protected CriticalSection
{
public:
    inline bool TryLock () { return TryEnter(); }
    inline void Lock () { Enter(); }
    inline void Unlock () { Leave(); }
};



//*****************************************************************************
//
// Functions
//
//*****************************************************************************

uint ThreadLogicalProcessorCount ();
void ThreadSleep (uint ms);
