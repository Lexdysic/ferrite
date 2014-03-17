
#include <mutex>

typedef uint32 ThreadId;

class Thread;
class CriticalSection;



//==================================================================================================
//
// Thread
//
//==================================================================================================
class Thread
{
public:
    virtual ~Thread();
    
    void ThreadStart();
    void ThreadStop();

    virtual void ThreadEnter() = 0;

private:
    ThreadId mId;
    void *   mHandle;
};



//==================================================================================================
//
// Critical Section
//
//==================================================================================================

class CriticalSection 
{
public:
    CriticalSection();
    ~CriticalSection();

    bool TryEnter();
    void Enter();
    void Leave();

    static const uint DATA_SIZE = 32;

private:
    uint8 m_data[DATA_SIZE];
};



//==================================================================================================
//
// Lockable
//
//==================================================================================================

class Lockable : protected CriticalSection
{
public:
    inline bool TryLock() { return TryEnter(); }
    inline void Lock() { Enter(); }
    inline void Unlock() { Leave(); }
};



//==================================================================================================
//
// Functions
//
//==================================================================================================

uint ThreadLogicalProcessorCount();
void ThreadSleep (uint ms);
