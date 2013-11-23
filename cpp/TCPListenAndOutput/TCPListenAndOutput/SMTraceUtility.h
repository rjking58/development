//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMTraceUtility.h $
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
//  $Date: 7/11/08 3:22p $
//  $Modtime: 7/09/08 4:33p $
//  $Revision: 17 $
//
//  Interface definition of the trace logging class.
//
//----------------------------------------------------------------------------

#pragma region Source control file history
// $History: SMTraceUtility.h $
// 
// *****************  Version 17  *****************
// User: Tfiner       Date: 7/11/08    Time: 3:22p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Replaced the deprecated and old strstream with the safer and the more
// modern ostringstream.  Be sure to rebuild all or there will be linker
// errors.
// 
// *****************  Version 16  *****************
// User: Arodriguez   Date: 5/10/08    Time: 8:59p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added SM_TRACE_FUNCTION and SM_LOG_FUNCTION which adds the function
// name into the trace entry.
// 
// *****************  Version 15  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 14  *****************
// User: Thelmi       Date: 2/08/08    Time: 7:29p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added a #pragma directive to collapse the source safe history
// 
// *****************  Version 13  *****************
// User: Zsukhanov    Date: 12/28/07   Time: 5:28p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 12  *****************
// User: Rgraham      Date: 9/13/07    Time: 3:12p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// // Global stream operator for the BSTR type
// // Commenting out for now until we add full support BSTR
// // by order of Arodriguez
// //ostream& operator<<(ostream& ostream, const BSTR s);
// 
// // Global stream operator for the CString class
// //#if !defined(SM_NO_MFC)
// //ostream& operator<<(ostream& ostream, const CString& s);
// //#endif
// 
// *****************  Version 10  *****************
// User: Arodriguez   Date: 6/15/07    Time: 4:20p
// Updated in $/Mobile/SMUtilities
// Added system info to trace log initialization.
// 
// *****************  Version 9  *****************
// User: Arodriguez   Date: 5/29/07    Time: 9:01a
// Updated in $/Mobile/SMUtilities
// Allowed SM_LOG with trace level 0 to be logged, it was previously being
// filtered out.
// 
// *****************  Version 8  *****************
// User: Arodriguez   Date: 5/25/07    Time: 4:21p
// Updated in $/Mobile/SMUtilities
// Added trace level to LOG Messages.
// 
// *****************  Version 7  *****************
// User: Arodriguez   Date: 4/18/07    Time: 11:37a
// Updated in $/Mobile/SMUtilities
// Fixed comments.
// 
// *****************  Version 6  *****************
// User: Arodriguez   Date: 4/17/07    Time: 6:17p
// Updated in $/Mobile/SMUtilities
// Read trace level from the registry.
// 
// *****************  Version 5  *****************
// User: Arodriguez   Date: 3/13/07    Time: 10:40p
// Updated in $/Mobile/SMUtilities
// Fixed link problem with exeption handling.
// 
// *****************  Version 4  *****************
// User: Arodriguez   Date: 3/13/07    Time: 10:25a
// Updated in $/Mobile/SMUtilities
// Corrected problems with Trace Utility.
// 
// *****************  Version 3  *****************
// User: Arodriguez   Date: 3/12/07    Time: 5:57p
// Updated in $/Mobile/SMUtilities
// Enabled automatic linking.
// 
// *****************  Version 2  *****************
// User: Arodriguez   Date: 3/12/07    Time: 4:45p
// Updated in $/Mobile/SMUtilities
// Fixed errors with SourceSafe keyword expansions.
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 3/12/07    Time: 2:10p
// Created in $/Mobile/SMUtilities
// Added the SMUtilties library.
#pragma endregion

#pragma once

#include "SMUtilitiesLink.h"
#include "SMString.h"

#pragma warning(push, 3)  // Switch to warning level 3 for STL headers.
#include <sstream>
#include <iomanip>
using namespace std;
#pragma warning(pop)

//----------------------------------------------------------------------------

// Facility codes
#define FACILITY_WSA  30   // WinSock facility (MS didn't define one)
#define FACILITY_MSC  31   // C Library (MS didn't define one)
#define FACILITY_SM   50   // SM facility

// Known MS error codes:
//     1 -  9999    General Win32 errors
// 10004 - 10112    Winsock errors
// 11001 - 11031    Winsock errors
// 12001 - 12174    Internet APIs
// 13001 - 13005    WinSpool BIDI errors
// 15000 - 15019    NetSh errors
// 16384 - 16420    COM errors
// 20480 - 20578    SAPI5 (ITF) errors
// 23000 - 23003    Win32 Filter API errors

// Base for all SM-specific errors
#define SM_BASE_ERROR 14000

#define SM_HRESULT_ERROR(x)   MAKE_HRESULT(SEVERITY_ERROR,  FACILITY_SM,SM_BASE_ERROR+(x))
#define SM_HRESULT_SUCCESS(x) MAKE_HRESULT(SEVERITY_SUCCESS,FACILITY_SM,SM_BASE_ERROR+(x))

// SM-specific error codes

//   0 - 19   general
#define SM_E_COM_CALL_BEFORE_INIT      SM_HRESULT_ERROR(1)
#define SM_E_CM_NOT_VALID              SM_HRESULT_ERROR(2)
#define SM_E_INVALID_PARAMETER         SM_HRESULT_ERROR(3)
#define SM_E_TIMEOUT                   SM_HRESULT_ERROR(4)
#define SM_E_PHONE_COMM_ERROR          SM_HRESULT_ERROR(5)
#define SM_E_RIM_INIT_ERROR			   SM_HRESULT_ERROR(6)


//----------------------------------------------------------------------------

#define HRESULT_FROM_WSA(x) MAKE_HRESULT(SEVERITY_ERROR,FACILITY_WSA,(x))
#define HRESULT_FROM_MSC(x) MAKE_HRESULT(SEVERITY_ERROR,FACILITY_MSC,(x))

#define HRESULT_FROM_LAST_WIN32() HRESULT_FROM_WIN32(::GetLastError())
#define HRESULT_FROM_LAST_ERRNO() HRESULT_FROM_MSC(errno)
#define HRESULT_FROM_LAST_WSA()   HRESULT_FROM_WSA(::WSAGetLastError())

//----------------------------------------------------------------------------

#if !defined(_NO_LOG)
    //extern const char* LOG_EXCEPTION;

    // Use this for logging informational and error messages
    #define SM_LOG(hresult, level, stream) { SMTraceUtility::Initialize(); \
        int nTL = SMTraceUtility::GetTraceLevel(); if (level <= nTL) {\
        ostringstream _Msg; try { _Msg << stream << ends; } catch (...) { _Msg /*<< LOG_EXCEPTION*/ << ends; }\
        SMTraceUtility::Log(__FILE__, __LINE__, level, hresult, &_Msg); } }
 
	// Use this for logging information and error messages prefixed with the function name.
	#define SM_LOG_FUNCTION(hresult, level, stream) SM_LOG(hresult, level, __FUNCTION__ << "(): " << stream)

    // Use this for logging a message that is prefixed with the object name
    #define SM_LOG_NAME(hresult, level, stream) SM_LOG(hresult, level, GetName() << ": " << stream)

    // Use this for displaying messages in a message box that also get logged
    #define SM_MESSAGE_BOX(hresult, prefix, stream) { ostringstream _Msg;\
    try { _Msg << stream << ends; } catch (...) { _Msg /*<< LOG_EXCEPTION*/ << ends; }\
    SMTraceUtility::MessageBox(__FILE__, __LINE__, hresult, prefix, &_Msg); }
#else
    #define SM_LOG(hresult, level, stream) ((void)0)
    #define SM_LOG_NAME(hresult, level, stream) ((void)0)
#endif

#if !defined(_NO_TRACE)
    //extern const char* TRACE_EXCEPTION;

    // Use this for logging trace messages
    #define SM_TRACE(level, stream) { SMTraceUtility::Initialize(); int nTL = SMTraceUtility::GetTraceLevel(); if ((nTL != 0) && (level <= nTL)) {\
        ostringstream _Msg; try { _Msg << stream << ends; } catch (...) { _Msg /*<< TRACE_EXCEPTION*/ << ends; }\
        SMTraceUtility::Trace(__FILE__, __LINE__, level, &_Msg); } }

	#define SM_TRACE_FUNCTION(level, stream) SM_TRACE(level, __FUNCTION__ << "(): " << stream)

    // Use this for tracing a message that is prefixed with the object name
    #define SM_TRACE_NAME(level, stream) SM_TRACE(level, GetName() << ": " << stream)
#else
    #define SM_TRACE(level, stream) ((void)0)
    #define SM_TRACE_NAME(level, stream) ((void)0)
#endif

// Use this for doing an ASSERT that also gets logged
#ifdef _DEBUG
	#define SM_ASSERT(exp) { if (!(exp)) SM_LOG(E_FAIL, 1, "Assertion failed: "#exp); _ASSERT((exp)); }
	#define SM_ASSERT_COMMENT(exp, comment) { if (!(exp)) SM_LOG(E_FAIL, 1, "Assertion failed: "#comment); _ASSERT((exp)); }
#else
	#define SM_ASSERT(exp) ((void)0)
	#define SM_ASSERT_COMMENT(exp, comment) ((void)0)
#endif

//----------------------------------------------------------------------------

// Trace levels:
#define SMTRACE_OFF 0
#define SMINFO      1
#define SMTRACE     2
#define SMDEBUG     3

const int MAX_FILE_NAME = 256;

// Global stream operator for the BSTR type
// RMG - Commenting out for now until we add full support BSTR
// by order of Arodriguez
//ostream& operator<<(ostream& ostream, const BSTR s);

// Global stream operator for the CString class
//#if !defined(SM_NO_MFC)
//ostream& operator<<(ostream& ostream, const CString& s);
//#endif

//----------------------------------------------------------------------------

class SMUTILITIES_API SMTraceUtility
{
public:
    static void    Initialize();
    static void    Cleanup();
    static void    SetAppName(const char* psAppName);
    static void    Log(  const char* pFile, int nLine, int nLevel, HRESULT hr, ostringstream* pMsg = NULL);
    static void    Trace(const char* pFile, int nLine, int nLevel, ostringstream* pMsg = NULL);
    static void    MessageBox(const char* psFile, int nLine, int nLevel, HRESULT hr, const char* psPrefix, ostringstream* pMsg);

    static int     GetTraceLevel();
    static void    SetTraceLevel(int nLevel);
    static void    CheckTraceLevel();

    static bool    GetUseConsoleWindow();
    static void    SetUseConsoleWindow(bool bUseConsoleWindow);

    static bool    GetUseLogFile();
    static void    SetUseLogFile(bool bUseLogFile);
    static void    SetLogFile(const SMString& spLogFile);
    static void    KillLogFile();
    static DWORD   GetLogFileSize();
    static __int64 GetLogDriveFreeSpace();
    static void    LogStatus();

    // Diagnostics
    static int s_nErrorCount;
    static int s_nInformationCount;
    static int s_nTraceCount;
    static int s_nLogFileSize;

private:
    static void TimestampAndOutput(ostringstream& Message);
    static void OutputSystemInfo();

    // This is a utility class - don't allow instantiation.
    SMTraceUtility();
    ~SMTraceUtility();
    SMTraceUtility(           const SMTraceUtility&);
    SMTraceUtility& operator=(const SMTraceUtility&);

    static int   s_nTraceLevel;
    static bool  s_bUseLogFile;
    static bool  s_bUseConsoleWindow;
    static bool  s_bInitialized;
    static char  s_sLogFile[MAX_FILE_NAME]; // Do NOT use SMString here
    static int   s_nDefaultTraceLevel;
    static int   s_nErrorWriteCount;

    static const char* s_psAppName;
};


//----------------------------------------------------------------------------
