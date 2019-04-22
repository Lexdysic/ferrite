#ifndef BASICS_THREAD_H
#define BASICS_THREAD_H

#include "Basics/Time.h"


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
    CThread ();
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
    
    static const uint DATA_SIZE = 48;

private:
    uint8 m_data[DATA_SIZE];
};


//*****************************************************************************
//
// Semaphore
//
//*****************************************************************************

class Semaphore {
public:
    Semaphore (uint32_t initialValue = 0);
    ~Semaphore ();
    
    bool Wait ();
    void Post ();
    
private:
    void * m_handle;
};


//*****************************************************************************
//
// Event
//
//*****************************************************************************

class Event {
public:
    Event (bool initialState = false);
    ~Event ();
    
    void Wait ();
    void Post ();
    
private:
    void * m_handle;
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
void ThreadSleep (Time::Delta duration);

#endif // BASICS_THREAD_H