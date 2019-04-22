#include "ThrdPch.h"


//*****************************************************************************
//
// Validation
//
//*****************************************************************************

//=============================================================================
static_assert(CriticalSection::DATA_SIZE >= uint(sizeof(CRITICAL_SECTION)), "Not enough space to old critical section data");



//*****************************************************************************
//
// Helpers
//
//*****************************************************************************

//=============================================================================
inline CRITICAL_SECTION * ConvertCritSec (uint8 * data)
{
    return (CRITICAL_SECTION *)data;
}

//=============================================================================
static DWORD WINAPI ThreadEntryPoint (LPVOID param)
{
    CThread * thread = (CThread *)param;
    ASSERT(thread);

    thread->ThreadEnter();

    return 0;
}



//*****************************************************************************
//
// Thread
//
//*****************************************************************************

//=============================================================================
CThread::CThread () :
    m_id(0),
    m_handle(NULL)
{
}

//=============================================================================
CThread::~CThread ()
{
    CloseHandle(m_handle);
}

//=============================================================================
void CThread::Start()
{
    m_handle = ::CreateThread(null, 0, ThreadEntryPoint, this, 0, (LPDWORD)&m_id);
}

//=============================================================================
void CThread::Stop()
{
    ::TerminateThread(m_handle, 0);
}

//=============================================================================
void CThread::Suspend()
{
    ::SuspendThread(m_handle);
}

//=============================================================================
void CThread::Resume()
{
    ::ResumeThread(m_handle);
}

//=============================================================================
bool CThread::IsRunning() const
{
    DWORD exitCode = 0;
    const BOOL success = ::GetExitCodeThread(m_handle, &exitCode);
    ASSERT(success);
    return exitCode == STILL_ACTIVE;
}



//*****************************************************************************
//
// CriticalSection
//
//*****************************************************************************

//=============================================================================
CriticalSection::CriticalSection ()
{
    ::InitializeCriticalSection(ConvertCritSec(m_data));
}

//=============================================================================
CriticalSection::~CriticalSection ()
{
    ::DeleteCriticalSection(ConvertCritSec(m_data));
}

//=============================================================================
bool CriticalSection::TryEnter () 
{
    return ::TryEnterCriticalSection(ConvertCritSec(m_data)) != 0;
}

//=============================================================================
void CriticalSection::Enter ()
{
    ::EnterCriticalSection(ConvertCritSec(m_data));
}

//=============================================================================
void CriticalSection::Leave ()
{
    ::LeaveCriticalSection(ConvertCritSec(m_data));
}


//*****************************************************************************
//
// Semaphore
//
//*****************************************************************************

Semaphore::Semaphore (uint32_t initialValue)
{
    m_handle = ::CreateSemaphoreW(
        nullptr,
        initialValue,
        std::numeric_limits<LONG>::max(),
        nullptr
    );
}

Semaphore::~Semaphore ()
{
    ::CloseHandle(m_handle);
}

bool Semaphore::Wait ()
{
    return ::WaitForSingleObject(m_handle, INFINITE) == WAIT_OBJECT_0;
}

void Semaphore::Post ()
{
    ::ReleaseSemaphore(m_handle, LONG(1), nullptr);
}


//*****************************************************************************
//
// Event
//
//*****************************************************************************

Event::Event (bool initialState)
{
    m_handle = ::CreateEventW(nullptr, false, initialState, nullptr);
}

Event::~Event ()
{
    ::CloseHandle(m_handle);
}

void Event::Wait ()
{
    ::WaitForSingleObject(m_handle, INFINITE);
}

void Event::Post ()
{
    SetEvent(m_handle);
}


//*****************************************************************************
//
// Lockable
//
//*****************************************************************************

////=============================================================================
//void Lockable::Lock () const
//{
//    m_mutex.lock();
//}
//
////=============================================================================
//bool Lockable::TryLock () const
//{
//    return m_mutex.try_lock();
//}
//
////=============================================================================
//void Lockable::Unlock () const
//{
//    m_mutex.unlock();
//}



//*****************************************************************************
//
// Functions
//
//*****************************************************************************

//=============================================================================
uint ThreadLogicalProcessorCount ()
{
    DWORD numStructs = 0;
    GetLogicalProcessorInformation(null, &numStructs);

    SYSTEM_LOGICAL_PROCESSOR_INFORMATION * infos = new SYSTEM_LOGICAL_PROCESSOR_INFORMATION[numStructs];
    GetLogicalProcessorInformation(infos, &numStructs);

    uint numLogicProcs = 0;
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION * ptr = infos;
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION * end = ptr + numStructs;
    for ( ; ptr < end; ++ptr )
    {
        if ( ptr->Relationship != RelationProcessorCore)
            continue;

        numLogicProcs += Math::BitCount(uint64_t(ptr->ProcessorMask));
    }

    delete[] infos;
    
    return numLogicProcs;
}

//=============================================================================
void ThreadSleep (Time::Delta duration)
{
    Time::Ms ms = duration;
    ::Sleep(uint(ms));
}
