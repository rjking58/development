//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMThread.h $
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
//  $Modtime: 9/10/08 2:05p $
//  $Revision: 8 $
//
//  This class is a wrapper of thread functionality.  This actually wraps the
//  thread handle which represents the thread object to the system.
//
//----------------------------------------------------------------------------

#ifndef VersionControlHistory
// $History: SMThread.h $
// 
// *****************  Version 8  *****************
// User: Tfiner       Date: 9/15/08    Time: 10:30a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added WaitForThread.
// 
// *****************  Version 7  *****************
// User: Tfiner       Date: 9/04/08    Time: 4:18p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added a simpler auto lock that doesn't require inheritance to be
// useful.
// 
// *****************  Version 6  *****************
// User: Tfiner       Date: 7/02/08    Time: 5:31p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Observed iterator corruption and noticed that the static maps were not
// thread protected.  Added thread protection.
// 
// *****************  Version 5  *****************
// User: Jwilliamson  Date: 4/03/08    Time: 9:02p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Update to the Thread Naming algorithm.  The thread ID, in addition to
// the thread handle, must be supplied to the naming routines.
// 
// *****************  Version 4  *****************
// User: Jwilliamson  Date: 4/03/08    Time: 6:10p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added thread naming ability to the SMThread class.
// 
// *****************  Version 3  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 8/01/07    Time: 11:28a
// Created in $/Mobile/SMUtilities
// Added Timer, Thread, Port and Queue classes.
#endif

#pragma once

#include <map>
#include "SMUtilitiesLink.h"
#include "SMEvent.h"
#include "SMThreadSync.h"
#include "SMTraceUtility.h"

//----------------------------------------------------------------------------

class SMThread;
typedef UINT (__stdcall *PTHREAD_FUNCTION)(SMThread& Thread);
typedef std::map<HANDLE, SMString> HandleNameMap;
typedef std::map<HANDLE, DWORD> HandleIdMap;

//----------------------------------------------------------------------------
// This class is a wrapper of thread functionality. This actually wraps the
// thread handle which represents the thread object to the system.

class SMUTILITIES_API SMThread : public SMThreadSync
{
public:
    // Note that the default behavior for a thread is to create suspended, so
    // that 'Start()' must be called before the thread actually starts running.
    // This is the safest way to use threads. If the thread starts the moment
    // it is created, there may be a small timing window in which a crash could
    // occur. For example, "m_pThread = new SMThread(..." is unsafe if the
    // thread function uses 'm_pThread' and starts running immediately, because
    // the assignment will not take place until a later time.
    SMThread(SMString sName, PTHREAD_FUNCTION pfThreadFunction = NULL, void* pParameter = NULL, bool bSuspended = true);
    ~SMThread();

    // Main thread control methods. A thread can be created by the constructor
    // above, or after construction using the Create method.
    HRESULT Create(PTHREAD_FUNCTION pfThreadFunction, void* pParameter = NULL, bool bSuspended = true);
    HRESULT Start();
    HRESULT Stop(DWORD dwWaitTime = 0);
    HRESULT Pause();
    HRESULT Resume();
    HRESULT Sleep(DWORD dwWaitTime);

    // Indicates that the thread has been created and hasn't stopped yet.
    bool    IsActive();

    // Indicates whether or not the thread has been paused.
    bool    IsPaused() const { return m_bIsPaused; }

    // Indicates that the thread method may continue to execute.
    bool    IsPermittedToRun() const { return m_bIsPermittedToRun; }

    // Get/Set the thread priority of this thread.
    int     GetPriority() const;
    HRESULT SetPriority(int nPriority);

    // Returns the parameter to be accessed by the thread method.
    void*   GetParameter() { return m_pParameter; }

    // Returns the thread ID
    UINT    GetThreadId()  { return m_nThreadId; }

    // Returns the stop event - which will be signaled if the thread is trying
    // to stop. The thread function should wait on this event (in addition to
    // any other events) whenever it needs to wait. It should NEVER call the
    // Sleep API, or make any blocking calls - otherwise the thread will not be
    // capable of terminating immediately.
    SMEvent& GetStopEvent() { return m_StopEvent; }

	// These guys are static so that threads created outside of SMThread
	//  can still use them to name threads
	static void     SetThreadName(HANDLE Thread, DWORD dwThreadID, LPCSTR szThreadName);
	static void     RemoveThreadName(HANDLE Thread);
	static SMString GetThreadName(HANDLE Thread);
	static DWORD    GetThreadId(HANDLE Thread);
	static void     UpdateThreadNamesInDebugger();

	// Wait for thread to end, check status up to retries, sleeping for sleep between each loop.
	// The exit status is returned.  If STILL_ACTIVE is returned, use ::GetLastError to determine why.
	static DWORD    WaitForThreadToEnd( HANDLE hThread, int retries, DWORD sleep );

protected:
    UINT     m_nThreadId;          // The ID for this thread.
    SMEvent  m_StopEvent;          // Signals that the thread should stop.
    bool     m_bIsPaused;          // True if the thread is paused.
    bool     m_bIsPermittedToRun;  // True if the thread may continue to run.
    SMString  m_sName;             // The name of the thread
    PTHREAD_FUNCTION m_pfThreadFunction;  // Client's thread function
    void*            m_pParameter;        // Parameter passed to the thread.

//	static bool m_bDebuggerPresent;
//	static HandleNameMap	m_HandleToNameMap;
//	static HandleIdMap		m_HandleToIdMap;

private:
    static UINT __stdcall _ThreadFunction(SMThread& Thread);
//	static void SetThreadNameInDebugger(DWORD dwThreadID, LPCSTR szThreadName);

    // Disallow copy construction and assignment for now.
    SMThread           (const SMThread&);
    SMThread& operator=(const SMThread&);

};

/*
 This class was written to be used in the RAII idiom.  No inheritance is necessary.
 Use with an already initialized critical section, this class always releases the 
 critical section, even in the face of exceptions.

 Ex:
	::InitializeCriticalSection( &csMapLock );

	func in thread A:
		SMSimpleAutoLock lock(&csMapLock);
		...

	func in thread B:
	SMSimpleAutoLock lock(&csMapLock);
		...

	::DeleteCriticalSection( &csMapLock );
*/
class SMSimpleAutoLock {
public:
	SMSimpleAutoLock(LPCRITICAL_SECTION _critical) : critical(_critical) { ::EnterCriticalSection(critical); }
	~SMSimpleAutoLock() { ::LeaveCriticalSection(critical); }

private:
	LPCRITICAL_SECTION critical;
};
