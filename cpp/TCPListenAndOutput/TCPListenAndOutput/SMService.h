//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMService.h $
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
//  Creator: DPS
//  $Author: Arodriguez $
//  $Date: 2/15/08 3:08p $
//  $Modtime: 2/15/08 2:50p $
//  $Revision: 3 $
//
//  Base class for an NT Service
//  Warning: Due the the nature of the NT services functions, this class only
//           supports one SMService per EXE.  You can implement multiple 
//           services in NT, but I cannot figure out how do do this in C++ 
//           without setting a nasty global variable that points to the one 
//           and only SMService*.  I found some code at www.codeguru.com
//           that did the same thing.
//
//----------------------------------------------------------------------------

#ifndef VersionControlHistory
// $History: SMService.h $
// 
// *****************  Version 3  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 2  *****************
// User: Cchang       Date: 1/15/08    Time: 9:18a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 8/10/07    Time: 3:59p
// Created in $/Mobile/Orbiter/Source Code/SMUtilities
// Initial check-in of Orbiter solution.
// 4     4/10/07 11:27a Arodriguez
// Refactored and also changed warning level to 4.
// 3     2/23/06 12:14p Sziegler
// Fixed a problem with the $NoKeywords VSS tag where it was missing a
// closing $
// 2     2/18/04 11:26a Sschunker
// Added IsInstalled function, that checks to see if the service is
// already installed.
// 1     3/10/03 5:05p Dsperling
// 10    9/10/99 5:09p Dsperling
// new log param
// 9     1/26/99 1:23p Dsperling
// renamed confusing GetLastError() member function
// 8     8/21/98 4:37p Aquezada
// Added Checkpoint variable
// 7     6/03/98 2:52p Smsi_build2
// added UserControl and NT non system mode
// 6     6/03/98 8:43a Dsperling
// added comments and a new helper function
// 5     3/17/98 7:22a Dsperling
// Made Log Event public
// 4     3/16/98 8:30a Dsperling
// Robustificaation
// 3     3/15/98 3:52p Dsperling
// New ideas from codeguru
// 2     12/30/97 7:52p Dsperling
// include proper windows headers
// 1     12/30/97 7:10p Dsperling
// First version of a NT Service that is also Windows 95 friendly
// $NoKeywords: $
#endif

#pragma once


#include <winsvc.h>

//----------------------------------------------------------------------------

#define MAX_SERVICE_NAME_LENGTH	50


//----------------------------------------------------------------------------

class SMUTILITIES_API SMService
{
protected:
	static BOOL				m_bInstance;	// only one SMService object per application

	TCHAR					m_szServiceName[MAX_SERVICE_NAME_LENGTH];
	TCHAR					m_szDisplayName[MAX_SERVICE_NAME_LENGTH];
	SERVICE_STATUS			m_ssStatus;     // current status of the service
	SERVICE_STATUS_HANDLE	m_sshStatusHandle;
	BOOL					m_bNonServiceMode;	// Win9x or NT from user space
	BOOL					m_bDebugMode;		// Debug Mode
	BOOL					m_bServiceCapable;	// TRUE = NT (or some other future OS)
	HANDLE					m_hServiceStopEvent;
	DWORD					m_dwError;
    TCHAR					m_szPath[_MAX_PATH * sizeof(TCHAR)];
    DWORD					m_dwCheckPoint;

	// Parameters to the "CreateService()" function:
	DWORD			m_dwDesiredAccess;		// default: SERVICE_ALL_ACCESS
	DWORD			m_dwServiceType;		// default: SERVICE_WIN32_OWN_PROCESS
	DWORD			m_dwStartType;			// default: SERVICE_AUTO_START
	DWORD			m_dwErrorControl;		// default: SERVICE_ERROR_NORMAL
	LPCTSTR			m_pszLoadOrderGroup;	// default: NULL
	DWORD			m_dwTagID;				// retrieves the tag identifier
	LPCTSTR			m_pszDependencies;		// default: NULL
	LPCTSTR			m_pszStartName;			// default: NULL
	LPCTSTR			m_pszPassword;			// default: NULL

	LPSTR			m_pszDescription;

public:
	SMService(LPCTSTR lpServiceName, LPCTSTR lpDisplayName);

	virtual ~SMService();

	// Start things off
	virtual BOOL Start(void);

	// Functions called from global functions
	virtual void Prepare(DWORD dwArgc, LPTSTR *lpszArgv);
	virtual void Control(DWORD dwCtrlCode);

	// Install/Uninstall
	virtual BOOL Install(void);
	virtual BOOL IsInstalled();
	virtual BOOL Remove(void);

	void SetDebug(BOOL bDebug = TRUE)	{ m_bNonServiceMode = bDebug; m_bDebugMode = bDebug; } 
	BOOL NonServiceMode(void)			{ return(m_bNonServiceMode); }
	BOOL IsDebugMode(void)				{ return(m_bDebugMode); }
	BOOL IsOSServiceCapable(void)		{ return(m_bServiceCapable); }

	// Functions to deal with error conditions
	DWORD GetLastErrorCode(void) { return (m_dwError); }
	LPTSTR GetLastErrorText( LPTSTR lpszBuf, DWORD dwSize);

	// Access functions to retreive the name strings
	LPCTSTR GetServiceName(void) { return (m_szServiceName); }
	LPCTSTR GetServiceDisplayName(void) { return (m_szDisplayName); }

	// Default implementation does a SetEvent on m_hServiceStopEvent
	virtual void Stop(void);
	virtual void Pause(void) { }
	virtual void Continue(void) { }
	virtual void Shutdown(void) { }
	virtual void UserControl(DWORD /*dwCtrlCode*/) { }	// can be used for user definable control codes

	// Talking to the NT Event Viewer
	virtual void LogEvent(LPCTSTR lpEventText, WORD wEventType = EVENTLOG_ERROR_TYPE, DWORD dwID = 0);

	// Helper functions to set parameters before calling Install
	// for this to actually work, the ReportStatus function may need to
	// also set some flags to enable pause/continue - this has not been tested
	void SetPauseCapable(void) { m_dwDesiredAccess |= SERVICE_PAUSE_CONTINUE; }

protected:
	// Helper functions
	virtual BOOL ReportStatus(DWORD dwCurrentState, DWORD dwWaitHint = 3000);

	BOOL ReportStatusRunning() { return (ReportStatus(SERVICE_RUNNING)); }

	virtual void WaitForStop(int nPriority = THREAD_PRIORITY_LOWEST);
	virtual SC_HANDLE CreateService(SC_HANDLE schSCManager);

	virtual void Main(DWORD dwArgc, LPTSTR *lpszArgv) = 0;
};


// Retrieve the one and only SMService object
SMService *GetService();
