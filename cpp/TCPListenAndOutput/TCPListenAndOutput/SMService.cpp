//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMService.cpp $
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
//  $Author: Tfiner $
//  $Date: 7/11/08 3:24p $
//  $Modtime: 7/10/08 5:57p $
//  $Revision: 10 $
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
// $History: SMService.cpp $
// 
// *****************  Version 10  *****************
// User: Tfiner       Date: 7/11/08    Time: 3:24p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added a check for a valid handle, clarified the code and added some
// debugging statements.
// 
// *****************  Version 9  *****************
// User: Arodriguez   Date: 5/10/08    Time: 8:59p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Used new SM_TRACE_FUNCTION macro.
// 
// *****************  Version 8  *****************
// User: Thelmi       Date: 4/22/08    Time: 10:16a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added some trace info
// 
// *****************  Version 7  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 6  *****************
// User: Cchang       Date: 1/30/08    Time: 5:10p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 6  *****************
// User: Cchang       Date: 1/15/08    Time: 9:18a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Add Group, Dependent, Description, Output to Event Viewer
// 
// *****************  Version 5  *****************
// User: Sanderson    Date: 01/15/08   Time: 12:15a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// updated event viewer posting and service description
//
// *****************  Version 4  *****************
// User: Sanderson    Date: 10/29/07   Time: 10:56a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// updated service dependency list
// 
// *****************  Version 3  *****************
// User: Sanderson    Date: 10/25/07   Time: 12:01p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 2  *****************
// User: Sanderson    Date: 10/23/07   Time: 2:35p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// temp fix for getting the service to start automatically.  Had to add
// some service 'dependencies'.
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 8/10/07    Time: 3:59p
// Created in $/Mobile/Orbiter/Source Code/SMUtilities
// Initial check-in of Orbiter solution.
// 6     4/10/07 11:27a Arodriguez
// Refactored and also changed warning level to 4.
// 5     3/01/07 1:32p Arodriguez
// Reimplemented usage of pre-compiled headers.
// 4     2/23/06 12:14p Sziegler
// Fixed a problem with the $NoKeywords VSS tag where it was missing a
// closing $
// 3     2/18/04 11:26a Sschunker
// Added IsInstalled function, that checks to see if the service is
// already installed.
// 2     3/10/03 6:09p Dsperling
// fixed link error
// 1     3/10/03 5:05p Dsperling
// 10    9/10/99 5:09p Dsperling
// new log param
// 9     1/26/99 1:23p Dsperling
// renamed confusing GetLastError() member function
// 8     8/21/98 4:42p Aquezada
// added new checkpoing variable
// 7     6/03/98 2:51p Smsi_build2
// added UserControl and NT non system mode
// 6     6/03/98 9:12a Dsperling
// ready for others to use...
// 5     6/03/98 8:43a Dsperling
// added comments
// 4     3/16/98 8:31a Dsperling
// Robustificaation
// 3     3/15/98 3:52p Dsperling
// New ideas from codeguru
// 1     12/30/97 7:10p Dsperling
// First version of a NT Service that is also Windows 95 friendly
// $NoKeywords: $
#endif

#include "stdafx.h"
#include "SMSystemInfo.h"
#include "SMProcessInfo.h"
#include "SMService.h"
#include "SMTraceUtility.h"
					 
//----------------------------------------------------------------------------
// Global stuff

VOID WINAPI ServiceControlGlobal(DWORD dwCtrlCode);
VOID WINAPI ServiceMainGlobal(DWORD dwArgc, LPTSTR *lpszArgv);
// the one and only SMService
static SMService *gpService = NULL;
BOOL SMService::m_bInstance = FALSE;


//---------------Copyright (c) 1997 Smith Micro Software, Inc.-----------------
// Purpose:	helper function to retrieve the global service pointer
// Authors:	DPS

SMService *GetService()
{
	return (gpService);
}


//---------------Copyright (c) 1997 Smith Micro Software, Inc.-----------------
// Purpose:	Constructs the SMService and sets the all important global
// Authors:	DPS

SMService::SMService(LPCTSTR lpServiceName, LPCTSTR lpDisplayName)
{
	m_bInstance = TRUE;		// only one object per EXE allowed
	gpService = this;

	lstrcpyn(m_szServiceName, lpServiceName, MAX_SERVICE_NAME_LENGTH);
	lstrcpyn(m_szDisplayName, lpDisplayName, MAX_SERVICE_NAME_LENGTH);

	// SERVICE_STATUS members that don't change
	//
	m_ssStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	m_ssStatus.dwServiceSpecificExitCode = 0;
	m_sshStatusHandle = 0;

	m_bNonServiceMode = FALSE;
	m_bDebugMode = FALSE;
    m_bServiceCapable = SMSystemInfo::IsRunningNT();

	m_dwDesiredAccess = SERVICE_ALL_ACCESS;
	m_dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	m_dwStartType = SERVICE_AUTO_START;
	m_dwErrorControl = SERVICE_ERROR_NORMAL;
	m_pszLoadOrderGroup = __TEXT("NetworkProvider");
	m_dwTagID = 0;
	m_pszDescription = __TEXT("Provide Smith Micro Connection Manager Service");
	// Quick and dirty fix for service not automatically starting.
	// TODO: Determin 'exactly' what services (or service groups) SMManager depends on
	m_pszDependencies = __TEXT("RasMan\0NetMan\0winmgmt\0");

	m_pszStartName = NULL;
	m_pszPassword = NULL;
	m_hServiceStopEvent = NULL;
    m_dwCheckPoint = 0;

	GetModuleFileName( NULL, m_szPath, sizeof(m_szPath));
}


//---------------Copyright (c) 1997 Smith Micro Software, Inc.-----------------
// Purpose:	Clean up - don't do much in here as derived classes will usually
//			be declared as global classes
// Authors:	DPS

SMService::~SMService()
{
	m_bInstance = FALSE;
	gpService = NULL;
    if (m_hServiceStopEvent)
        CloseHandle(m_hServiceStopEvent);
}


//---------------Copyright (c) 1997 Smith Micro Software, Inc.-----------------
// Purpose:	Called from ServiceMainGlobal.  We get here is we are running as a
//			true service
// Authors:	DPS

void SMService::Prepare(DWORD dwArgc, LPTSTR *lpszArgv)
{
    m_sshStatusHandle = RegisterServiceCtrlHandler( GetServiceName(), ServiceControlGlobal);
    if (m_sshStatusHandle)
	{
		// report the status to the service control manager.
		//
		if (ReportStatus(SERVICE_START_PENDING))
		{
			Main( dwArgc, lpszArgv );
		}
        ReportStatus(SERVICE_STOPPED);
	}
}


//---------------Copyright (c) 1997 Smith Micro Software, Inc.-----------------
// Purpose:	Called from ServiceControlGlobal.  We get here is we are running as a
//			true service.  Control calls come from the Windows Service Control
//			manager.
// Authors:	DPS

void SMService::Control(DWORD dwCtrlCode)
{
    // Handle the requested control code.
    //
    switch(dwCtrlCode)
    {
        // Stop the service.
        //
        // SERVICE_STOP_PENDING should be reported before
        // setting the Stop Event - hServerStopEvent - in
        // ServiceStop().  This avoids a race condition
        // which may result in a 1053 - The Service did not respond...
        // error.
        case SERVICE_CONTROL_STOP:
            ReportStatus(SERVICE_STOP_PENDING);
            Stop();
            return;

        case SERVICE_CONTROL_PAUSE:
            Pause();
            return;

        case SERVICE_CONTROL_CONTINUE:
            Continue();
            return;

		case SERVICE_CONTROL_SHUTDOWN:
			Shutdown();
            return;

		// Update the service status.
        case SERVICE_CONTROL_INTERROGATE:
            break;

        // User defined control codes
        default:
			if ((dwCtrlCode >= 128) && (dwCtrlCode <= 255))
			{
				UserControl(dwCtrlCode);
				return;
			}
            break;
    }

    ReportStatus(m_ssStatus.dwCurrentState);
}


//---------------Copyright (c) 1997 Smith Micro Software, Inc.-----------------
// Purpose:	Called by the application (WinMain or InitInstance) to start things
//			off.  This function determines the OS and calls the service functions,
//			or just calls Main() itself (under Win95 or debug mode).
// Authors:	DPS

BOOL SMService::Start(void)
{
	TCHAR *szCommandLine = TEXT("");  // empty command line used if we manually call Main()
    
	SM_TRACE_FUNCTION(1, "Starting Service Application...");
	SERVICE_TABLE_ENTRY dispatchTable[] =
    {
        { (LPTSTR) GetServiceName(), (LPSERVICE_MAIN_FUNCTION)ServiceMainGlobal },
        { NULL, NULL }
    };

	if (m_hServiceStopEvent == NULL)
	{
		SM_TRACE_FUNCTION(3, "Creating Stop Event");

		m_hServiceStopEvent = CreateEvent(
			NULL,    // no security attributes
			TRUE,    // manual reset event
			FALSE,   // not-signalled
			NULL);   // no name
	
		if (m_hServiceStopEvent == NULL)
			return (FALSE);

		SM_TRACE_FUNCTION(3, "Stop Event is not NULL");
	}
	
	LogEvent(TEXT("Trying to Start SMService"),EVENTLOG_INFORMATION_TYPE,0);
    
	if (SMProcessInfo::IsProcessInSystemSpace() == FALSE)
	{
		// ok, we are running on 9x or NT but not in service mode
		m_bNonServiceMode = TRUE;
		// we do this becase StartServiceCtrlDispatcher takes 10 seconds or
		// so to return if we are running NT but not in the system space
	}

	if (m_bNonServiceMode)
	{
		// just call the main function ourselves since we cannot
		// call StartServiceCtrlDispatcher when we are debugging
		Main(1, &szCommandLine);
	}
	else
	{
		if (!StartServiceCtrlDispatcher(dispatchTable))
		{
			m_dwError = GetLastError();

			// 1054 = ERROR_SERVICE_NO_THREAD
			// 1055 = ERROR_SERVICE_DATABASE_LOCKED 
			// 1056 = ERROR_SERVICE_ALREADY_RUNNING
			SM_TRACE_FUNCTION(1, "Service Dispatch Failed: " << m_dwError);

			// Win95 returns ERROR_CALL_NOT_IMPLEMENTED
			// Win98 returns ERROR_SUCCESS
			if ((m_dwError == ERROR_CALL_NOT_IMPLEMENTED) || (m_dwError == ERROR_SUCCESS))
			{
				// just call the main function for Win95
				m_dwError = ERROR_SUCCESS;
				m_bNonServiceMode = TRUE;
				Main(1, &szCommandLine);
			}
			else
				return (FALSE);
		}
	}

	LogEvent(TEXT("SMService Started"),EVENTLOG_INFORMATION_TYPE, 0);

	return (TRUE);
}


//---------------Copyright (c) 1997 Smith Micro Software, Inc.-----------------
// Purpose:	We give the SCM the address of this function to run our service
// Authors:	DPS

void WINAPI ServiceMainGlobal(DWORD dwArgc, LPTSTR *lpszArgv)
{
	GetService()->Prepare(dwArgc, lpszArgv);
}


//---------------Copyright (c) 1997 Smith Micro Software, Inc.-----------------
// Purpose:	We give the SCM the address of this function after it calls
//			ServiceMainGlobal
// Authors:	DPS

VOID WINAPI ServiceControlGlobal(DWORD dwCtrlCode)
{
	GetService()->Control(dwCtrlCode);
}


//---------------Copyright (c) 1997 Smith Micro Software, Inc.-----------------
// Purpose:	Tell the SCM what we are doing.  This function is safe to call
//			even if you are running under Win95 or debug mode
// Authors:	DPS

BOOL SMService::ReportStatus(DWORD dwCurrentState, DWORD dwWaitHint)
{
    if ( m_bNonServiceMode ) // when debugging we don't report to the SCM
		return TRUE;

	if (dwCurrentState == SERVICE_START_PENDING)
        m_ssStatus.dwControlsAccepted = 0;
    else
        m_ssStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;

    m_ssStatus.dwCurrentState = dwCurrentState;
    m_ssStatus.dwWin32ExitCode = NO_ERROR;

    if ( ( dwCurrentState == SERVICE_RUNNING ) ||
         ( dwCurrentState == SERVICE_STOPPED ) )
	{
        m_ssStatus.dwWaitHint = 0;
		m_dwCheckPoint = 0;
	}
    else
	{
        m_ssStatus.dwWaitHint = dwWaitHint;
         ++m_dwCheckPoint;
	}
	m_ssStatus.dwCheckPoint	= m_dwCheckPoint;

    // Report the status of the service to the service control manager.
    //
	BOOL fResult = TRUE;
	if ( m_sshStatusHandle ) 
	{
		fResult = SetServiceStatus(m_sshStatusHandle, &m_ssStatus);

		if (!fResult)
			LogEvent(TEXT("SetServiceStatus"),EVENTLOG_INFORMATION_TYPE,0);
    } 
	else 
	{
		LogEvent(TEXT("SetServiceStatus Invalid Status Handle!"),EVENTLOG_INFORMATION_TYPE,0);
	}

    return fResult;
}


//---------------Copyright (c) 1997 Smith Micro Software, Inc.-----------------
// Purpose:	Sends strings to the WinNT Event Viewer
// Authors:	DPS

VOID SMService::LogEvent(LPCTSTR lpszMsg, WORD wEventType, DWORD dwID)
{
    TCHAR   szMsg[256];
    HANDLE  hEventSource;
    LPCTSTR  lpszStrings[2];

    if ( !m_bNonServiceMode )
    {
        m_dwError = GetLastError();

        // Use event logging to log the error.
        //
        hEventSource = RegisterEventSource(NULL, GetServiceName());

        wsprintf(szMsg, TEXT("%s info: %d"), GetServiceName(), m_dwError);
        lpszStrings[0] = szMsg;
        lpszStrings[1] = lpszMsg;

        if (hEventSource != NULL) {
            ReportEvent(hEventSource, // handle of event source
                wEventType,			  // event type
                0,                    // event category
                dwID,                  // event ID
                NULL,                 // current user's SID
                2,                    // strings in lpszStrings
                0,                    // no bytes of raw data
                (LPCTSTR *) lpszStrings, // array of error strings
                NULL);                // no raw data

            (VOID) DeregisterEventSource(hEventSource);
        }
    }
}


//---------------Copyright (c) 1997 Smith Micro Software, Inc.-----------------
// Purpose:	handy function that gives us an english description of the Win32 error
//			We should use this in more of our apps!
// Authors:	DPS

LPTSTR SMService::GetLastErrorText( LPTSTR lpszBuf, DWORD dwSize)
{
    DWORD dwRet;
    LPTSTR lpszTemp = NULL;

    dwRet = FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_ARGUMENT_ARRAY,
                           NULL,
                           m_dwError,
                           LANG_NEUTRAL,
                           (LPTSTR)&lpszTemp,
                           0,
                           NULL );

    // supplied buffer is not long enough
    if ( !dwRet || ( (long)dwSize < (long)dwRet+14 ) )
        lpszBuf[0] = TEXT('\0');
    else
    {
        lpszTemp[lstrlen(lpszTemp)-2] = TEXT('\0');  //remove cr and newline character
        wsprintf( lpszBuf, TEXT("%s (0x%x)"), lpszTemp, m_dwError);
    }

    if ( lpszTemp )
        LocalFree((HLOCAL) lpszTemp );

    return lpszBuf;
}


//---------------Copyright (c) 1997 Smith Micro Software, Inc.-----------------
// Purpose:	Called from Install.  The following code handles service 
//          installation and removal
// Authors:	DPS

SC_HANDLE SMService::CreateService(SC_HANDLE schSCManager)
{
	return (::CreateService(
            schSCManager,
            GetServiceName(),
            GetServiceDisplayName(),
            m_dwDesiredAccess,
            m_dwServiceType,
            m_dwStartType,
            m_dwErrorControl,
            m_szPath,
            m_pszLoadOrderGroup,
			((m_dwServiceType == SERVICE_KERNEL_DRIVER || m_dwServiceType == SERVICE_FILE_SYSTEM_DRIVER) &&
			(m_dwStartType == SERVICE_BOOT_START || m_dwStartType == SERVICE_SYSTEM_START)) ?
				&m_dwTagID : 0,
            m_pszDependencies,
            m_pszStartName,
            m_pszPassword));
	
		

}


//---------------Copyright (c) 2000 Smith Micro Software, Inc.-----------------
// Purpose:	The following code checks to see if the service is already installed
// Authors:	SS

BOOL SMService::IsInstalled()
{
	BOOL bServiceInstalled = FALSE;
	SC_HANDLE   schService = NULL;
	SC_HANDLE   schSCManager;

	schSCManager = OpenSCManager(
						NULL,                   // machine (NULL == local)
						NULL,                   // database (NULL == default)
						GENERIC_READ   // access required
						);
	if (!schSCManager )
		return bServiceInstalled;
    schService = OpenService(schSCManager, GetServiceName(), GENERIC_READ);
	if (schService)
	{
		bServiceInstalled = TRUE;
		CloseServiceHandle(schService);
	}
	CloseServiceHandle(schSCManager);
	m_dwError = GetLastError();
	return bServiceInstalled;
}


//---------------Copyright (c) 1997 Smith Micro Software, Inc.-----------------
// Purpose:	Called from our app.  The easiest thing to do is to call this on a
//			MYAPP -RegServer
// Authors:	DPS

BOOL SMService::Install(void)
{
    SC_HANDLE   schService;
    SC_HANDLE   schSCManager;

    schSCManager = OpenSCManager(
                        NULL,                   // machine (NULL == local)
                        NULL,                   // database (NULL == default)
                        SC_MANAGER_ALL_ACCESS   // access required
                        );
    if ( schSCManager )
    {
        schService = CreateService(schSCManager);

        if ( schService == NULL)
        {
			m_dwError = GetLastError();
			return (FALSE);
        }
		else //ccc:
		{
			 //   Set   service   description  
			SERVICE_DESCRIPTION   ServiceDesc;  
			ServiceDesc.lpDescription   =   m_pszDescription;  
   			::ChangeServiceConfig2(schService,   SERVICE_CONFIG_DESCRIPTION,   &ServiceDesc);  
		}
        
		CloseServiceHandle(schSCManager);
		return (TRUE);
    }
	m_dwError = GetLastError();
	return (FALSE);
}


//---------------Copyright (c) 1997 Smith Micro Software, Inc.-----------------
// Purpose:	Called from our app.  The easiest thing to do is to call this on a
//			MYAPP -UnRegServer
// Authors:	DPS

BOOL SMService::Remove()
{
    SC_HANDLE   schService;
    SC_HANDLE   schSCManager;

    schSCManager = OpenSCManager(
                        NULL,                   // machine (NULL == local)
                        NULL,                   // database (NULL == default)
                        SC_MANAGER_ALL_ACCESS   // access required
                        );
    if ( schSCManager )
    {
        schService = OpenService(schSCManager, GetServiceName(), SERVICE_ALL_ACCESS);

        if (schService)
        {
            // try to stop the service
            if ( ControlService( schService, SERVICE_CONTROL_STOP, &m_ssStatus ) )
            {
                Sleep( 1000 );

                while( QueryServiceStatus( schService, &m_ssStatus ) )
                {
                    if ( m_ssStatus.dwCurrentState == SERVICE_STOP_PENDING )
                    {
                        Sleep( 1000 );
                    }
                    else
                        break;
                }

                if ( m_ssStatus.dwCurrentState != SERVICE_STOPPED )
				{
					// service failed to stop
				}
            }

            // now remove the service
            if( DeleteService(schService) == FALSE)
				m_dwError = GetLastError();

            CloseServiceHandle(schService);
        }
        else
			m_dwError = GetLastError();

        CloseServiceHandle(schSCManager);
    }
    else
		m_dwError = GetLastError();

	return (m_dwError == ERROR_SUCCESS);
}


//---------------Copyright (c) 1997 Smith Micro Software, Inc.-----------------
// Purpose:	A helper function that is only useful in the simplest of services
//			usually you would do a WaitForMultiple... on m_hServiceStopEvent
//			and some other event
// Authors:	DPS

void SMService::WaitForStop(int nPriority)
{
	SetThreadPriority(GetCurrentThread(), nPriority);
	WaitForSingleObject(m_hServiceStopEvent, INFINITE);
}


//---------------Copyright (c) 1997 Smith Micro Software, Inc.-----------------
// Purpose:	Called automatically from the Control function.  This can be
//			overridden to do more fancy stuff
// Authors:	DPS

void SMService::Stop()
{
    if ( m_hServiceStopEvent )
        SetEvent(m_hServiceStopEvent);
}


//----------------------------------------------------------------------------
// EOF