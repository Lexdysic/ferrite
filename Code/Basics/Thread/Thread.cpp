
#include "ThrdPch.h"

//=============================================================================
inline CRITICAL_SECTION * Convert (uint8 * data)
{
    return (CRITICAL_SECTION *)data;
}

//=============================================================================
static_assert(CriticalSection::DATA_SIZE >= sizeof(CRITICAL_SECTION), "Not enough space to old critical section data");


//=================================================================================================
//
// Thread
//
//=================================================================================================

//=============================================================================
static DWORD WINAPI ThreadEntryPoint(LPVOID param)
{
    CThread * thread = (CThread *)param;
    ASSERT(thread);

    thread->ThreadEnter();

    return 0;
}

//=============================================================================
CThread::~CThread()
{
    CloseHandle(mHandle);
}

//=============================================================================
void CThread::Start()
{
    mHandle = ::CreateThread(null, 0, ThreadEntryPoint, this, 0, (LPDWORD)&mId);
}

//=============================================================================
void CThread::Stop()
{
    ::TerminateThread(mHandle, 0);
}

//=============================================================================
void CThread::Suspend()
{
    ::SuspendThread(mHandle);
}

//=============================================================================
void CThread::Resume()
{
    ::ResumeThread(mHandle);
}

//=============================================================================
bool CThread::IsRunning() const
{
    DWORD exitCode = 0;
    ::GetExitCodeThread(mHandle, &exitCode);
    return exitCode == STILL_ACTIVE;
}



//=================================================================================================
//
// Critical Section
//
//=================================================================================================

//=============================================================================
CriticalSection::CriticalSection()
{
    ::InitializeCriticalSection(Convert(m_data));
}

//=============================================================================
CriticalSection::~CriticalSection()
{
    ::DeleteCriticalSection(Convert(m_data));
}

//=============================================================================
bool CriticalSection::TryEnter() 
{
    return ::TryEnterCriticalSection(Convert(m_data)) != 0;
}

//=============================================================================
void CriticalSection::Enter()
{
    ::EnterCriticalSection(Convert(m_data));
}

//=============================================================================
void CriticalSection::Leave()
{
    ::LeaveCriticalSection(Convert(m_data));
}




//=================================================================================================
//
// Lockable
//
//=================================================================================================

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



//=================================================================================================
//
// Exported Functions
//
//=================================================================================================

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

        numLogicProcs += Math::BitCount(ptr->ProcessorMask);
    }

    delete[] infos;
    
    return numLogicProcs;
}

//=============================================================================
void ThreadSleep (uint ms)
{
    ::Sleep(ms);
}
