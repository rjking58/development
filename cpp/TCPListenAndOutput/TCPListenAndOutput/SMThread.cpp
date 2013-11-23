//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMThread.cpp $
//  Package : SMUtilities
//
//  Copyright © 2007-2008 Smith Micro Software, Inc., All Rights Reserved.
//
//  This software is the intellectual property of Smith Micro Software, Inc.
//  It is protected by state law, copyright law, and/or international
//  treaties. Neither receipt nor possession of this software (in any
//  form) confers any right to reproduce, use, or disclose it, in whole
//  or in part, without written authorization from Smith Micro Software, Inc.
//
//  $Author: Tfiner $
//  $Date: 9/15/08 10:30a $
//  $Modtime: 9/10/08 2:19p $
//  $Revision: 12 $
//
//  This class is a wrapper of thread functionality.  This actually wraps the
//  thread handle which represents the thread object to the system.
//
//----------------------------------------------------------------------------

#ifndef VersionControlHistory
// $History: SMThread.cpp $
// 
// *****************  Version 12  *****************
// User: Tfiner       Date: 9/15/08    Time: 10:30a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added WaitForThread.
// 
// *****************  Version 11  *****************
// User: Tfiner       Date: 9/04/08    Time: 4:18p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added a simpler auto lock that doesn't require inheritance to be
// useful.
// 
// *****************  Version 10  *****************
// User: Tfiner       Date: 7/23/08    Time: 8:15a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added a function to prevent the debugger from stopping each time an
// invalid handle is passed to GetExitCodeThread.
// 
// *****************  Version 9  *****************
// User: Tfiner       Date: 7/02/08    Time: 5:31p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Observed iterator corruption and noticed that the static maps were not
// thread protected.  Added thread protection.
// 
// *****************  Version 8  *****************
// User: Tfiner       Date: 6/30/08    Time: 10:00a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Prep for x64, minor changes.
// 
// *****************  Version 7  *****************
// User: Jwilliamson  Date: 4/15/08    Time: 5:58a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// NamedThread change:  When calling std::map::erase, save the return
// value as the new iterator value.
// 
// *****************  Version 6  *****************
// User: Jwilliamson  Date: 4/03/08    Time: 9:02p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Update to the Thread Naming algorithm.  The thread ID, in addition to
// the thread handle, must be supplied to the naming routines.
// 
// *****************  Version 5  *****************
// User: Jwilliamson  Date: 4/03/08    Time: 6:10p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added thread naming ability to the SMThread class.
// 
// *****************  Version 4  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 3  *****************
// User: Sanderson    Date: 10/02/07   Time: 3:27p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Chagnes to fix HEAP errors
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 8/01/07    Time: 11:28a
// Created in $/Mobile/SMUtilities
// Added Timer, Thread, Port and Queue classes.
#endif

#include "StdAfx.h"

#include "SMException.h"
#include "SMSingleLock.h"
#include <process.h>
#include "SMThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace 
{
	bool            m_bDebuggerPresent = false;	// is a debugger attached to our service?
	HandleNameMap	m_HandleToNameMap;			// maps Thread Handles to Thread Names
	HandleIdMap		m_HandleToIdMap;				// maps Thread Handles to Thread IDs

	CRITICAL_SECTION csMapLock;					// Used to prevent corruption of handle maps.


	struct IntializeStatics {
		IntializeStatics() { ::InitializeCriticalSection( &csMapLock ); }
		~IntializeStatics() { ::DeleteCriticalSection( &csMapLock ); }
	} init;

	//----------------------------------------------------------------------------
	// Tell the debugger about the Thread's name.

	void SetThreadNameInDebugger(DWORD dwThreadID, LPCSTR szThreadName)
	{
		// Issue a exception to the debugger to have it name the thread
		typedef struct tagTHREADNAME_INFO
		{
			DWORD dwType;		// must be 0x1000
			LPCSTR szName;		// pointer to name (in user addr space)
			DWORD dwThreadID;	// thread ID (-1=caller thread)
			DWORD dwFlags;		// reserved for future use, must be zero
		} THREADNAME_INFO ;

		if (dwThreadID)
		{
			THREADNAME_INFO info;
			info.dwType = 0x1000;
			info.szName = szThreadName;
			info.dwThreadID = dwThreadID;
			info.dwFlags = 0;

			__try
			{
				RaiseException( 0x406D1388, 0, sizeof(info)/sizeof(DWORD), (ULONG_PTR*)&info );
			}
			__except(EXCEPTION_CONTINUE_EXECUTION)
			{
			}
		}
	}

} // namespace {


//----------------------------------------------------------------------------

#define VALIDATE_THREAD_HANDLE(MethodName) if (m_hObject == NULL) { hr = E_FAIL; \
        SM_LOG(hr, 1, "SMThread::"#MethodName"(): Thread handle isn't initialized!"); return hr; }

//-Constructor----------------------------------------------------------------

SMThread::SMThread(SMString sName,
				   PTHREAD_FUNCTION pfThreadFunction /*= NULL*/, 
                   void* pParameter /*= NULL*/,
				   bool bSuspended /*= true*/)
    : m_nThreadId(0)
    , m_bIsPaused(false)
    , m_bIsPermittedToRun(false)
    , m_StopEvent(SMEvent::eManualReset)
    , m_pParameter(NULL)
	, m_sName(sName)
{
    SM_TRACE(SMDEBUG, "SMThread::SMThread()");

    // If a thread function was specified, create the thread now (otherwise,
    // the client must call the Create method).
    if (pfThreadFunction != NULL)
    {
        Create(pfThreadFunction, pParameter, bSuspended);
    }
}


//-Destructor-----------------------------------------------------------------

SMThread::~SMThread()
{
    SM_TRACE(SMDEBUG, "SMThread::~SMThread(), ID=0x" << hex << m_nThreadId);

    // Destroy();
}


//----------------------------------------------------------------------------
// Create the thread.

HRESULT SMThread::Create(PTHREAD_FUNCTION pfThreadFunction, void* pParameter /* = NULL */,
                          bool bSuspended /* = true */)
{
    SM_TRACE(SMDEBUG, "SMThread::Create()");

    HRESULT hr = S_OK;

    // Destroy any existing thread
    // Destroy();

    // Create the thread. Use the default stack size.
    m_pfThreadFunction  = pfThreadFunction;
    m_pParameter        = pParameter;
    m_bIsPermittedToRun = true;
    m_bIsPaused         = bSuspended;
    m_hObject           = (HANDLE)::_beginthreadex(NULL, 0,
            (unsigned int (__stdcall *)(void*))_ThreadFunction,
            this, bSuspended ? CREATE_SUSPENDED : 0, (UINT*)&m_nThreadId);

	SMString name;
	if (!m_sName.IsEmpty())
		name = m_sName;
	else
		name = "unnamed";

	SMString msg;
	msg.Format(" %s handle: 0x%08x stop: 0x%08x" , 
		name.Data(), m_hObject, m_StopEvent.GetHandle() );

	SM_TRACE(SMDEBUG, __FUNCTION__ << msg.Data() );

    if (m_hObject == NULL)
    {
        m_bIsPermittedToRun = false;
        hr = HRESULT_FROM_LAST_ERRNO();
        SM_LOG(hr, 1, "SMThread::SMThread(): _beginthreadex FAILED!");
    }
	else
	{
		SetThreadName(m_hObject, m_nThreadId, m_sName);
	}

    return hr;
}


//----------------------------------------------------------------------------
// _ThreadFunction - Static method which is called by _beginthreadex

UINT __stdcall SMThread::_ThreadFunction(SMThread& Thread)
{
    SM_TRY

    // Check if we're still permitted to run (the thread may have been stopped
    // before it ever got a chance to run).
    if (Thread.m_bIsPermittedToRun)
    {
        SM_TRACE(SMDEBUG, "SMThread::_ThreadFunction(): New thread running...");

        // Install a structured exception handler for this new thread
        SMStructuredException::InstallTranslator();

        // Call the Client's thread function
        (*Thread.m_pfThreadFunction)(Thread);

        Thread.m_bIsPermittedToRun = false;
        Thread.m_StopEvent.Set();

		// 1. endthreadex_ is called implicitly after return, see the docs on beginthreadex_
		// 2. endthreadex_ does not call CloseHandle, so we need to.
		// endthreadex_: http://msdn.microsoft.com/en-us/library/hw264s73(VS.80).aspx
		// 3. It's ok to close a handle in use.  Like all kernel objects, a thread's handle is
		// reference counted and OK to close while the thread is running.
		::CloseHandle(Thread.m_hObject);

		// Keep SMThreadSync::~SMThreadSync from closing m_hObject twice.
		Thread.m_hObject = NULL;
    }

    SM_CATCH_ALL_DEFAULT_NO_HR

    return 0; // endthreadex_(0); called implicitly here.
}


//----------------------------------------------------------------------------
// Start the thread.

HRESULT SMThread::Start()
{
    SM_TRACE(SMDEBUG, "SMThread::Start(), ID=0x" << hex << m_nThreadId);

    return Resume();
}


//----------------------------------------------------------------------------
// Stops the thread. Waits up to the specified time-out for the thread to 
// terminate. The thread method should terminate if the stop event is fired,
// OR if the IsPermittedToRun flag is false.  This method will NOT forcibly 
// terminate a thread - if it fails, the client must try again or call Terminate.

HRESULT SMThread::Stop(DWORD dwWaitTime /* = 0 */)
{
    SM_TRACE(SMDEBUG, "SMThread::Stop(), ID=0x" << hex << m_nThreadId);

    HRESULT hr = S_OK;

    // Clear the permitted-to-run flag, and set the shutdown event
    m_bIsPermittedToRun = false;
    m_StopEvent.Set();

    if (dwWaitTime != 0)
    {
        VALIDATE_THREAD_HANDLE(Stop);

        if (IsActive())
        {
            // If the thread is still active, wait for it to stop
            hr = Lock(dwWaitTime);
        }
    }

    return hr;
}


//----------------------------------------------------------------------------
// Pause (suspend) the thread.

HRESULT SMThread::Pause()
{
    SM_TRACE(SMDEBUG, "SMThread::Pause(), ID=0x" << hex << m_nThreadId);

    HRESULT hr = S_OK;

    VALIDATE_THREAD_HANDLE(Pause);

    int nSuspendCount = ::SuspendThread(m_hObject);
    if (nSuspendCount == -1)
    {
        HRESULT hr = HRESULT_FROM_LAST_WIN32();
        SM_LOG(hr, 1, "SMThread::Pause(): SuspendThread failed!");
    }
    else
    {
        m_bIsPaused = true;
    }

    return hr;
}


//----------------------------------------------------------------------------
// Resume the thread (from a paused state).

HRESULT SMThread::Resume()
{
    SM_TRACE(SMDEBUG, "SMThread::Resume(), ID=0x" << hex << m_nThreadId);

    HRESULT hr = S_OK;

    VALIDATE_THREAD_HANDLE(Resume);
    
    int nSuspendCount = ::ResumeThread(m_hObject);
    if (nSuspendCount == -1)
    {
        HRESULT hr = HRESULT_FROM_LAST_WIN32();
        SM_LOG(hr, 1, "SMThread::Resume(): ResumeThread failed!");
    }
    else if (nSuspendCount == 1)
    {
        // ResumeThread returns the previous suspend count. If it's 1, then
        // the thread has been resumed, otherwise it's still suspended.
        m_bIsPaused = false;
    }

    return hr;
}


//----------------------------------------------------------------------------
// Put the thread to sleep for the specified number of milliseconds.
// This call will exit early if the Thread's StopEvent is signalled.

HRESULT SMThread::Sleep(DWORD dwWaitTime)
{
    SM_TRACE(SMDEBUG, "SMThread::Sleep()");

    // Anything over 5 minutes is almost certainly a mistake
    //ASSERT(dwWaitTime <= 300000);

    HRESULT hr = S_OK;

    VALIDATE_THREAD_HANDLE(Sleep);

    SMSingleLock SingleLock(&GetStopEvent(), true, dwWaitTime);

    return hr;
}



//----------------------------------------------------------------------------
// Check if the thread is currently running. Perform an active check using an
// API call to determine for certain if the thread is running.
// NOTE: If the thread is suspended, it will still be reported as active.
//       Use the IsPaused() method to check this case.

bool SMThread::IsActive()
{
    bool bIsActive = false;

    if (m_hObject != NULL)
    {
        HRESULT hr;
        DWORD nExitCode = 0;
        if (!::GetExitCodeThread(m_hObject, &nExitCode))
        {
            hr = HRESULT_FROM_LAST_WIN32();
            SM_LOG(hr, 1, "SMThread::IsActive(): GetExitCodeThread failed!");
        }
        else if (nExitCode == STILL_ACTIVE)
        {
            bIsActive = true;
        }
        else
        {
            // Make sure the thread's state is accurate
            if (m_bIsPermittedToRun)
            {
                SM_LOG(E_FAIL, 1, "SMThread::IsActive(): THREAD STATE IS WRONG! Fixing...");
                m_bIsPermittedToRun = false;
                m_StopEvent.Set();
            }
        }
    }

    return bIsActive;
}


//----------------------------------------------------------------------------
// Get the thread's execution priority.

int SMThread::GetPriority() const
{
    HRESULT hr = S_OK;

    VALIDATE_THREAD_HANDLE(GetPriority);

    int nPriority = ::GetThreadPriority(m_hObject);
    if (nPriority == THREAD_PRIORITY_ERROR_RETURN)
    {
        hr = HRESULT_FROM_LAST_WIN32();
        SM_LOG(hr, 1, "SMThread::GetPriority(): GetThreadPriority failed!");
    }

    return nPriority;
}


//----------------------------------------------------------------------------
// Set the execution priority of the thread.

HRESULT SMThread::SetPriority(int nPriority)
{
    HRESULT hr = S_OK;

    VALIDATE_THREAD_HANDLE(SetPriority);

    if (!::SetThreadPriority(m_hObject, nPriority))
    {
        hr = HRESULT_FROM_LAST_WIN32();
        SM_LOG(hr, 1, "SMThread::SetPriority(): SetThreadPriority failed!");
    }
    else
    {
        SM_LOG(S_OK, 1, "SMThread::SetPriority(): Thread priority changed to: " << nPriority);
    }

    return hr;
}

//----------------------------------------------------------------------------
// Thread Name member functions
//
// Adapted from the Microsoft article located at:
//   http://msdn2.microsoft.com/en-us/library/xcb2z8hs(VS.71).aspx

//----------------------------------------------------------------------------
// Set the thread's name.

void SMThread::SetThreadName(HANDLE Thread, DWORD dwThreadID, LPCSTR szThreadName)
{
	SMSimpleAutoLock lock(&csMapLock);

	// save the association of this thread ID to its name
	m_HandleToNameMap[ Thread ] = szThreadName;
	m_HandleToIdMap[ Thread ] = dwThreadID;
    SM_LOG(S_OK, 1, "SMThread::SetThreadName(): Thread " << Thread << " named as " << szThreadName);

	// Give the name to the debugger if it is present
	if (::IsDebuggerPresent())
	{
		SetThreadNameInDebugger(dwThreadID, szThreadName);
	}
}

BOOL GetExitCodeThreadNoThrow( __in  HANDLE hThread, __out LPDWORD lpExitCode )
{
	BOOL gotExitCode = FALSE;
	__try {
		gotExitCode = GetExitCodeThread(hThread, lpExitCode);
	} __except ( EXCEPTION_EXECUTE_HANDLER ) {
		// Can't use SM_LOG anywhere in this function...
	}
	return gotExitCode;
}


//----------------------------------------------------------------------------
// Gives all the stored names in the map to the debugger to actually name the threads.

void SMThread::UpdateThreadNamesInDebugger()
{
	SMSimpleAutoLock lock(&csMapLock);

	// Names are given to a thread through an exception that the debugger handles.  This can only happen
	// if a debugger is present.  Note that this means that you can assign thread names until you're blue
	// in the face while there is no debugger, but then when a debugger attaches, none of those threads
	// will have the assigned names because the debugger wasn't around when you named them!  Therefore,
	// we'll have to periodically check if the debugger is present, and when it becomes present we'll
	// have to pump it up with all the names stored in our ID-to-Name map.

	if (::IsDebuggerPresent())
	{
		// Check if our debugger flag is false. If it is false, we have to load all of the other thread names
		if (m_bDebuggerPresent == false)
		{
			HandleNameMap::iterator Iter;
			for (Iter = m_HandleToNameMap.begin(); Iter != m_HandleToNameMap.end();)
			{
				// Remove any thread from the map that has exited
				// TODO:  We can also do this by WaitForMultipleObjects on the thread handles to save time

				// See if the thread has exited - if it has, get rid of its entry
				DWORD dwExitCode = STATUS_WAIT_0;
				if (!GetExitCodeThreadNoThrow(Iter->first, &dwExitCode))
					SM_LOG(GetLastError(), 1, "SMThread::GetExitCodeThread(): failed for handle: " 
						<< "0x" << hex << setw(8) << setfill('0') << Iter->first );

				// Either the handle is invalid, or the thread is finished.
				// The code initially only used to remove threads that had exit codes.
				// Now it removes invalid thread handles too.
				if (dwExitCode != STILL_ACTIVE)
				{
					// Save the handle
					HANDLE Thread = Iter->first;

					// thread is dead - remove its name
					Iter = m_HandleToNameMap.erase(Iter);	// this will advance Iter to the next map item

					// remove the corresponding thread ID from the other map
					HandleIdMap::iterator Iter2 = m_HandleToIdMap.find( Thread );
					if ( Iter2 != m_HandleToIdMap.end( ) )
						m_HandleToIdMap.erase(Iter2);

					continue;
				}

				// Thread is (might be) still running - get its ID from the other map
				HandleIdMap::iterator Iter2;
				Iter2 = m_HandleToIdMap.find( Iter->first );
				if ( Iter2 != m_HandleToIdMap.end( ) )
					SetThreadNameInDebugger(Iter2->second, Iter->second);

				Iter++;	// this will advance Iter to the next map item
			}
			m_bDebuggerPresent = true;
		}
	}
	else
	{
		if (m_bDebuggerPresent == true)
		{
			m_bDebuggerPresent = false;
		}
	}
}


DWORD SMThread::WaitForThreadToEnd( HANDLE hThread, int retries, DWORD sleep ) 
{
	int nRetry = retries;
	DWORD dwStatus = STILL_ACTIVE;
	do 
	{
		if ( !::GetExitCodeThread(hThread, &dwStatus) )
		{
			dwStatus = 0; // I don't think we should send back STILL_ACTIVE
			break; // Error!  What to do?
		}

		if (STILL_ACTIVE == dwStatus)
			::Sleep(sleep);
		
		nRetry--;
	} while ( STILL_ACTIVE == dwStatus && nRetry > 0 );

	return dwStatus;
}


//----------------------------------------------------------------------------
// Remove the thread's name from our Handle-to-Name map, and Handle-to-ID map.

void SMThread::RemoveThreadName(HANDLE Thread)
{
	SMSimpleAutoLock lock(&csMapLock);

	HandleNameMap::iterator Iter;
    Iter = m_HandleToNameMap.find( Thread );

    if ( Iter != m_HandleToNameMap.end( ) )
	{
		m_HandleToNameMap.erase(Iter);

		// remove the corresponding thread ID from the other map
		HandleIdMap::iterator Iter2;
		Iter2 = m_HandleToIdMap.find( Thread );

		if ( Iter2 != m_HandleToIdMap.end( ) )
			m_HandleToIdMap.erase(Iter2);
	}
}




//----------------------------------------------------------------------------
// Get a thread's name from the Handle-to-Name map.

SMString SMThread::GetThreadName(HANDLE Thread)
{
	SMSimpleAutoLock lock(&csMapLock);

	SMString name;
	HandleNameMap::iterator Iter;
    Iter = m_HandleToNameMap.find( Thread );

    if ( Iter != m_HandleToNameMap.end( ) )
		name = Iter->second;

	return name;
}


//----------------------------------------------------------------------------
// Get a thread's ID from the Handle-to-ID map.

DWORD SMThread::GetThreadId(HANDLE Thread)
{
	DWORD ThreadID = 0;
	HandleIdMap::iterator Iter;
    Iter = m_HandleToIdMap.find( Thread );

    if ( Iter != m_HandleToIdMap.end( ) )
		ThreadID = Iter->second;

	return ThreadID;
}


//----------------------------------------------------------------------------
// EOF
