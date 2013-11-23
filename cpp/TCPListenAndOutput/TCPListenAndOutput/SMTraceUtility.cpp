//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMTraceUtility.cpp $
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
//  $Date: 7/11/08 3:23p $
//  $Modtime: 7/09/08 5:42p $
//  $Revision: 17 $
//
//  Contains the trace logging class.
//
//----------------------------------------------------------------------------

#pragma region Source control file history
// $History: SMTraceUtility.cpp $
// 
// *****************  Version 17  *****************
// User: Tfiner       Date: 7/11/08    Time: 3:23p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Replaced the deprecated and old strstream with the safer and the more
// modern ostringstream.  Be sure to rebuild all or there will be linker
// errors.
// 
// *****************  Version 16  *****************
// User: Arodriguez   Date: 5/13/08    Time: 3:54a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Fixed service not starting issue in trace level 2 or higher.
// 
// *****************  Version 15  *****************
// User: Thelmi       Date: 4/18/08    Time: 4:36p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Fixed creation of the trace and status directories
// 
// *****************  Version 14  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 13  *****************
// User: Thelmi       Date: 2/08/08    Time: 7:28p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// -Added clear for status log manager 
// -Added C++ macros to write to the status log
// 
// *****************  Version 11  *****************
// User: Arodriguez   Date: 6/15/07    Time: 4:20p
// Updated in $/Mobile/SMUtilities
// Added system info to trace log initialization.
// 
// *****************  Version 10  *****************
// User: Arodriguez   Date: 5/30/07    Time: 10:52a
// Updated in $/Mobile/SMUtilities
// Depending if the application is running in service or user mode, the
// trace utility reads from HKCU and outputs to My Documents in user mode,
// and HKLM and outputs to \SMTraceLog in service mode.
// 
// *****************  Version 9  *****************
// User: Arodriguez   Date: 5/25/07    Time: 4:21p
// Updated in $/Mobile/SMUtilities
// Added trace level to LOG Messages.
// 
// *****************  Version 8  *****************
// User: Arodriguez   Date: 5/25/07    Time: 2:01p
// Updated in $/Mobile/SMUtilities
// Added SMUserInfo class which contains informatin pertaining to the
// current user.
// 
// *****************  Version 7  *****************
// User: Arodriguez   Date: 5/16/07    Time: 8:45a
// Updated in $/Mobile/SMUtilities
// Fixed a problem when SM_NO_MFC is not declared.
// 
// *****************  Version 6  *****************
// User: Arodriguez   Date: 4/17/07    Time: 6:17p
// Updated in $/Mobile/SMUtilities
// Read trace level from the registry.
// 
// *****************  Version 5  *****************
// User: Arodriguez   Date: 3/27/07    Time: 5:26p
// Updated in $/Mobile/SMUtilities
// Corrected format of history.
// 
// *****************  Version 4  *****************
// User: Arodriguez   Date: 3/27/07    Time: 5:25p
// Updated in $/Mobile/SMUtilities
// Fixed a problem with the trace level is not being set correctly.
// 
// *****************  Version 3  *****************
// User: Arodriguez   Date: 3/22/07    Time: 11:52a
// Updated in $/Mobile/SMUtilities
// Prevented SMTraceUtility from accessing the hard drive after the first
// time.  Also changed the trace directory from Temp to SMTraceLog.
// 
// *****************  Version 2  *****************
// User: Arodriguez   Date: 3/13/07    Time: 10:25a
// Updated in $/Mobile/SMUtilities
// Corrected problems with Trace Utility.
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 3/12/07    Time: 2:10p
// Created in $/Mobile/SMUtilities
// Added the SMUtilties library.
#pragma endregion

#include "StdAfx.h"
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/timeb.h>
#include <tchar.h>

#include "SMAppStorage.h"
#include "SMTraceUtility.h"
#include "SMUserInfo.h"
#include "SMSystemInfo.h"
#include "SMMacros.h"
#include "SMProcessInfo.h"
#include "SMPath.h"

#if !defined(SM_NO_MFC)
#include <afxwin.h>
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//----------------------------------------------------------------------------

// These constant strings are defined like this so they will be stored in the
// DLL and shared between different executables. If they aren't done in this
// manner, copies of them will be generated for EVERY USE of the log macros!

const char* LOG_EXCEPTION   = "-->EXCEPTION streaming log message!";
const char* TRACE_EXCEPTION = "-->EXCEPTION streaming trace message!";

//----------------------------------------------------------------------------

#if !defined(SM_NO_COM)
// Define a global stream operator for the BSTR type
ostream& operator<<(ostream& ostream, const BSTR s)
{
    SMString Str(s);
    return ostream << Str;
}
#endif


// Define a global stream operator for the CString class
#if !defined(SM_NO_MFC)
ostream& operator<<(ostream& ostream, const CString& s)
{
    return ostream << (LPCTSTR)s;
}
#endif

//----------------------------------------------------------------------------

// Default to always use log file 
bool  SMTraceUtility::s_bUseLogFile = true;

// Default: don't write to console window
bool  SMTraceUtility::s_bUseConsoleWindow = false;

// Static initialization
// NOTE: Don't use SMString for any of these, or it won't be safe to
//       use logging or tracing in any constructors of static objects!
bool  SMTraceUtility::s_bInitialized = false;
char  SMTraceUtility::s_sLogFile[MAX_FILE_NAME];
int   SMTraceUtility::s_nTraceLevel = SMTRACE_OFF;
int   SMTraceUtility::s_nDefaultTraceLevel = SMTRACE_OFF;
int   SMTraceUtility::s_nErrorWriteCount = 0;

const char* SMTraceUtility::s_psAppName = NULL;

int SMTraceUtility::s_nErrorCount         = 0;
int SMTraceUtility::s_nInformationCount   = 0;
int SMTraceUtility::s_nTraceCount         = 0;
int SMTraceUtility::s_nLogFileSize        = 0;

//----------------------------------------------------------------------------
// Client code doesn't need to call this - it will be done automatically.

void SMTraceUtility::Initialize()
{
    if (!s_bInitialized)
    {
        s_bInitialized = true;

		//TT #2374
        //// Determine the default location of the trace file, it should be in My Documents
        //// if running in user mode, \SMTraceLog if running in service mode.
        //SMString sDefaultLocation = "\\SMTraceLog\\SMTrace.txt";
        //if (!SMProcessInfo::IsProcessInSystemSpace())
        //    sDefaultLocation = SMUserInfo::GetShellFolder(SMUserInfo::eMyDocuments) + "\\SMTrace.txt";
		SMString sDefaultLocation = SMUserInfo::GetLogFilePath() + "\\SMManager.txt";

        // Get the log file name from the registry
        SMString sLogFile = SMAppStorage::GetString("TraceFile", sDefaultLocation);
        SetLogFile(sLogFile);

        // If the log file is too big, then move it to a backup. This keeps the
        // log file from filling up the disk, but also guarantees that we always
        // have some log data available.
        int nDefaultMaxLogSize = 20000000; // ~20 megs
        int nMaxLogSize = SMAppStorage::GetInt("MaxTraceFileSize", nDefaultMaxLogSize);
        DWORD dwCurrentLogFileSize = GetLogFileSize();
        if (dwCurrentLogFileSize > (DWORD)nMaxLogSize)
        {
            SMString sNewFile = sLogFile + ".old.txt";
            ::DeleteFile(sNewFile);  // Remove old backup if it exists
            BOOL bRet = ::MoveFile(sLogFile, sNewFile);
            if (!bRet)
            {
                SM_LOG(HRESULT_FROM_LAST_WIN32(), 1, "SMTraceUtility::Initialize(): Log file backup failed");
            }
        }

        // Get the trace level from the registry
        CheckTraceLevel();

        SM_LOG(S_OK, 1, "SMTraceUtility::Initialize(): Trace level set to: " << s_nTraceLevel);

        // Output relevant system information here
        OutputSystemInfo();
    }
}



//----------------------------------------------------------------------------
// Output relevant system as part of the trace log

void SMTraceUtility::OutputSystemInfo()
{
    SM_LOG(S_OK, 2, "SMTraceUtility::OutputSystemInfo: "
        << " RunInSystemSpace=" << (SMProcessInfo::IsProcessInSystemSpace() ? "true" : "false")
        << ", IsVistaOrLater=" << (SMSystemInfo::IsRunningVistaOrLater() ? "true" : "false")
		// IsProcessAService uses StartServiceCtrlDispatcher to detect if a process is a service
		// application.  Unfortunately, this method can only be called once within a service.  In 
		// one instance, this method is called before the service and prevents the service from 
		// starting.  TODO: Move this log to to SMProcessInfo so that it can be called explicitly.
        //<< ", IsAService=" << (SMProcessInfo::IsProcessAService() ? "true" : "false")
	);
}


//----------------------------------------------------------------------------
// May be called at program shutdown to clean up any memory allocations.

void SMTraceUtility::Cleanup()
{
    s_bInitialized = false;
}

//----------------------------------------------------------------------------

void SMTraceUtility::SetAppName(const char* psAppName)
{
    s_psAppName = psAppName;
}

//----------------------------------------------------------------------------

void SMTraceUtility::Log(const char* psFile, int nLine, int nLevel, HRESULT hr, ostringstream* pMsg)
{
    if (!s_bInitialized) // Check this here to save a call in most cases
        Initialize();

    // Build the log message in the following formats:
    // AAA:PPP TTT ERROR:0:00000000 "Error Message" file.cpp:line
    // AAA:PPP TTT INFOR:0:00000000 "Log Message" file.cpp:line

    // Build the log message in ASCII
    ostringstream Message;
    Message << (s_psAppName == NULL ? "---" : s_psAppName)
            << ':' << setfill('0') << hex << setw(3) << GetCurrentProcessId() << ' ' 
            << setw(3) << GetCurrentThreadId() << (FAILED(hr) ? " ERROR:" : " INFOR:")
            << dec << nLevel << ':' << CAST_INT_TO_PVOID(hr);
    if (pMsg != NULL)
    {
		Message << " \"" << pMsg->str().c_str() << '\"';
    }
	const char* psFileSpec = ::strrchr(psFile, '\\');
    const char* psFileName = psFileSpec + 1;
	if ((s_psAppName == NULL) || (psFileSpec == NULL))
		psFileName = psFile;
    Message << ' ' << psFileName << ':' << nLine;

    if (FAILED(hr))
    {
        s_nErrorCount++;

        // Get error string from system for Win32 errors
        if (HRESULT_FACILITY(hr) == FACILITY_WIN32)
        {
            char* psExtended = NULL;
            ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_MAX_WIDTH_MASK,
                            NULL, HRESULT_CODE(hr), MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
                            (LPTSTR)&psExtended, 0, NULL);
            if (psExtended != NULL)
            {
                Message << " \"" << psExtended << '"';
                ::LocalFree(psExtended);
            }
        }
    }
    else
    {
        s_nInformationCount++;
    }
    Message << ends;

    TimestampAndOutput(Message);
}

//----------------------------------------------------------------------------

void SMTraceUtility::Trace(const char* psFile, int nLine, int nLevel, ostringstream* pMsg)
{
    // Do this check in the macro, so that the trace level is accurate.
    if (!s_bInitialized)
        Initialize();

    // Build the trace message in the following format:
    // AAA:PPP TTT TRACE:0 "Trace Message" file.cpp:line

    // Build the log message in ASCII
    ostringstream Message;
    Message << (s_psAppName == NULL ? "---" : s_psAppName)
            << ':' << setfill('0') << hex << setw(3) << GetCurrentProcessId()
            << ' ' << setw(3) << GetCurrentThreadId() << " TRACE:" << dec << nLevel;
    if (pMsg != NULL)
    {
		Message << " \"" << pMsg->str().c_str() << '\"';
    }
	const char* psFileSpec = ::strrchr(psFile, '\\');
    const char* psFileName = psFileSpec + 1;
	if ((s_psAppName == NULL) || (psFileSpec == NULL))
		psFileName = psFile;
    Message << ' ' << psFileName << ':' << nLine << ends;

    s_nTraceCount++;

    TimestampAndOutput(Message);
}

//----------------------------------------------------------------------------

void SMTraceUtility::MessageBox(const char* psFile, int nLine, int nLevel, 
                                HRESULT hr, const char* psPrefix, ostringstream* pMsg)
{
    if (!s_bInitialized) // Check this here to save a call in most cases
        Initialize();

    ostringstream FullMsg;
	try { 
		FullMsg << psPrefix << ": " << pMsg->str().c_str() << ends; 
	}catch (...) { 
		FullMsg << LOG_EXCEPTION << ends; 
	}
    Log(psFile, nLine, hr, nLevel, &FullMsg);
#if !defined(SM_NO_MFC)
    ::AfxMessageBox(pMsg->str().c_str(), SUCCEEDED(hr) ? (MB_ICONINFORMATION | MB_OK) : (MB_ICONEXCLAMATION | MB_OK));
#endif
}

//----------------------------------------------------------------------------

void SMTraceUtility::TimestampAndOutput(ostringstream& Message)
{
    // Create timestamped trace string
    struct _timeb Time;
    ::_ftime_s(&Time);
    struct tm pTM;
	::localtime_s(&pTM, &Time.time);

	std::string msg = Message.str();
	SM_ASSERT( !msg.empty() );

    SMString sTimeStampedAsciiMsg;
    sTimeStampedAsciiMsg.sprintf("%02d/%02d/%02d %02d:%02d:%02d.%03d %s\n",
                                 pTM.tm_mon + 1, pTM.tm_mday, pTM.tm_year - 100, 
								 pTM.tm_hour, pTM.tm_min, pTM.tm_sec,
                                 Time.millitm, msg.c_str());

    // Log to console window if applicable
    if (s_bUseConsoleWindow)
    {
        ::_putts(sTimeStampedAsciiMsg.Data());
    }

    if (s_bUseLogFile)
    {
        // Log to the logfile
        int nLogFile;
		errno_t result = _sopen_s(&nLogFile, s_sLogFile, _O_WRONLY|_O_CREAT|_O_APPEND, _SH_DENYNO, _S_IREAD|_S_IWRITE);
        if (result == 0)
        {
            ::_write(nLogFile, sTimeStampedAsciiMsg.Data(), sTimeStampedAsciiMsg.GetLength());
            long nFileSize = ::_lseek(nLogFile, 0, SEEK_CUR);
            s_nLogFileSize = nFileSize;
            ::_close(nLogFile);
        }
        else
        {
            s_nErrorWriteCount++;
            // If we've gone 500 times without being able to log.
            if (s_nErrorWriteCount > 500)
            {
                // Prevent it from logging again.
                s_bUseLogFile = false;
            }
        }
    }

#if defined(_DEBUG)
    // Log to the debugger
	{
		const char* str = sTimeStampedAsciiMsg.Data();
		::OutputDebugString( str );
	}
#endif

}

//----------------------------------------------------------------------------

int SMTraceUtility::GetTraceLevel()
{
    return s_nTraceLevel;
}

//----------------------------------------------------------------------------

void SMTraceUtility::SetTraceLevel(int nLevel)
{
    s_nTraceLevel = nLevel;
    SM_LOG(S_OK, 1, "SMTraceUtility::SetTraceLevel(): Set trace level to: " << nLevel);
}

//----------------------------------------------------------------------------

void SMTraceUtility::CheckTraceLevel()
{
    // Get the trace level from the registry
    int nTraceLevel = SMAppStorage::GetInt("TraceLevel", s_nDefaultTraceLevel);
    if (s_nTraceLevel != nTraceLevel)
        SetTraceLevel(nTraceLevel);
}

//----------------------------------------------------------------------------

bool SMTraceUtility::GetUseLogFile()
{
    return s_bUseLogFile;
}

//----------------------------------------------------------------------------

void SMTraceUtility::SetUseLogFile(bool bUseLogFile)
{
    s_bUseLogFile = bUseLogFile;
}

//----------------------------------------------------------------------------

bool SMTraceUtility::GetUseConsoleWindow()
{
    return s_bUseConsoleWindow;
}

//----------------------------------------------------------------------------

void SMTraceUtility::SetUseConsoleWindow(bool bUseConsoleWindow)
{
    s_bUseConsoleWindow = bUseConsoleWindow;
}

//----------------------------------------------------------------------------

void SMTraceUtility::SetLogFile(const SMString& sLogFile)
{
    if (sLogFile.GetLength() < sizeof(s_sLogFile))
    {
        ::strcpy_s(s_sLogFile, sizeof(s_sLogFile), sLogFile);
        SM_LOG(S_OK, 1, "SMTraceUtility::SetLogFile(): Set logfile to: " << s_sLogFile);
    }
    else
    {
        SM_LOG(E_FAIL, 1, "SMTraceUtility::SetLogFile(): Logfile name too long! File not changed.");
	}

	if (sLogFile.GetLength() > 0)
	{
		//Make sure the directory exists, if not, create the directory
		SMString sPath = SMPath::GetDirectory(sLogFile);
		if (!SMPath::PathExists(sPath))
			//Create the directory
			SMPath::CreatePath(sPath);
	}
}

//----------------------------------------------------------------------------

void SMTraceUtility::KillLogFile()
{
    ::DeleteFile(s_sLogFile);
}

//----------------------------------------------------------------------------

DWORD SMTraceUtility::GetLogFileSize()
{
    // Make sure we're initialized
    if (!s_bInitialized)
        return 0;

    DWORD nFileSizeHighWord = 0;
    DWORD nFileSize = 0;
    int nLogFile;
	errno_t result = ::_sopen_s(&nLogFile, s_sLogFile, _O_RDONLY, _SH_DENYNO, _S_IREAD);
    if (result == 0)
    {
        nFileSize = ::GetFileSize((HANDLE)::_get_osfhandle(nLogFile), &nFileSizeHighWord);
        if (nFileSize == INVALID_FILE_SIZE)
        {
            SM_LOG(HRESULT_FROM_LAST_WIN32(), 1, "GetLogFileSize(): GetFileSize failed!");
        }
        ::_close(nLogFile);
    }

    return nFileSize;
}

//----------------------------------------------------------------------------

__int64 SMTraceUtility::GetLogDriveFreeSpace()
{
    Initialize();

    SMString sLogFile(s_sLogFile);
    ULARGE_INTEGER AvailBytes, TotalBytes, TotalFreeBytes;
    if (::GetDiskFreeSpaceEx(sLogFile, &AvailBytes, &TotalBytes, &TotalFreeBytes))
    {
        return AvailBytes.QuadPart;
    }

    return 0;
}

//----------------------------------------------------------------------------

void SMTraceUtility::LogStatus()
{
    // Log file size & disk space status
    char sBuf[32];
    ::sprintf_s(sBuf, sizeof(sBuf), "%I64d", GetLogDriveFreeSpace());
    SM_LOG(S_OK, 1, "SMTraceUtility::LogStatus(): Logfile size=" << GetLogFileSize() << ", Free Space=" << sBuf);

    // Check the registry & update the trace level if changed
    CheckTraceLevel();
}

//----------------------------------------------------------------------------
// EOF
