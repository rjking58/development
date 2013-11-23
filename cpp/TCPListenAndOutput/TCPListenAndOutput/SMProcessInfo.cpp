//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMProcessInfo.cpp $
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
//  $Date: 9/15/08 6:10p $
//  $Modtime: 9/15/08 5:35p $
//  $Revision: 7 $
//
//  Process-related helper functions
//  
//----------------------------------------------------------------------------

#ifndef VersionControlHistory
// $History: SMProcessInfo.cpp $
// 
// *****************  Version 7  *****************
// User: Tfiner       Date: 9/15/08    Time: 6:10p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added version information to log output.
// 
// *****************  Version 6  *****************
// User: Sanderson    Date: 7/14/08    Time: 4:13p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Fix for IsProcessInSystemSpace() not working for non-english OS
// 
// *****************  Version 5  *****************
// User: Sanderson    Date: 7/10/08    Time: 5:13p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Temp hack for 'IsProcessInSystemSpace' returning false when running on
// some non-english systems
// 
// *****************  Version 4  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 2  *****************
// User: Arodriguez   Date: 6/15/07    Time: 12:20p
// Updated in $/Mobile/SMUtilities
// Fixed detection of IsProcessInSystemSpace() method.
// Added IsProcessAService() method.
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 5/30/07    Time: 10:52a
// Created in $/Mobile/SMUtilities
// Depending if the application is running in service or user mode, the
// trace utility reads from HKCU and outputs to My Documents in user mode,
// and HKLM and outputs to \SMTraceLog in service mode.
#endif


#include "StdAfx.h"
#include "SMSystemInfo.h"
#include "SMProcessInfo.h"

#include <sstream>
#include <iomanip>

namespace 
{

	// See http://msdn.microsoft.com/en-us/library/ms647464(VS.85).aspx
	// for more fields.
	const char* VERSION_SUBKEYS[] = 
	{
		"OriginalFilename",
		"BuildID",
	};
	const int NUM_VERSION_SUBKEYS = sizeof(VERSION_SUBKEYS)/sizeof(VERSION_SUBKEYS[0]);

	// This is English, the default for our resources.
	// See the sample code at 
	// http://msdn.microsoft.com/en-us/library/ms647464(VS.85).aspx
	// to iterate through multiple code pages.
	const unsigned short LANG = 0x0409;
	const unsigned short PAGE = 0x04b0;


	// Returns the raw version information in a vector of BYTES.  
	// Returns an empty vector on failure.
	// Check GetLastError for details.
	std::vector<BYTE> GetVersionInfo( const TCHAR* MODULE_NAME )
	{
		std::vector<BYTE> versionInfo;
		DWORD dummy = 0;
		DWORD size = GetFileVersionInfoSize( MODULE_NAME, &dummy );
		if ( 0 == size )
			return versionInfo;

		versionInfo = std::vector<BYTE>(size+1, 0);
		if ( !GetFileVersionInfo(MODULE_NAME, dummy, size, &versionInfo[0]) )
			return std::vector<BYTE>();

		return versionInfo;
	}


} // namespace {


//----------------------------------------------------------------------------
// Get the file path of the process, without the file name (such as "C:\Program Files\Smith Micro").

SMString SMProcessInfo::GetProcessPath()
{
    static bool      bGotFilePath = false;
    static SMString sFilePath;

    if (!bGotFilePath)
    {
        char sModuleName[MAX_PATH];
        ::GetModuleFileName(NULL, sModuleName, MAX_PATH);
        sFilePath = SMSystemInfo::GetFilePath(sModuleName);
        bGotFilePath = true;
    }

    return sFilePath;
}


//----------------------------------------------------------------------------
// Get the base file name of the process, without the extension (such as IDS_PRODUCT_NAME).

SMString SMProcessInfo::GetProcessBaseName()
{
    static bool     bGotBaseName = false;
    static SMString sBaseName;
    if (!bGotBaseName)
    {
        char sModuleName[MAX_PATH];
        char sLongModuleName[MAX_PATH];
        ::GetModuleFileName(NULL, sModuleName, MAX_PATH);
        //some times the sModuleName is a short file name and cause some problem
        //on locating the folder, do the short to long conversion here
        GetLongPathName(sModuleName,sLongModuleName,MAX_PATH);
        sBaseName = SMSystemInfo::GetFileBaseName(sLongModuleName);
        bGotBaseName = true;
    }

    return sBaseName;
}


SMString SMProcessInfo::GetProcessFullPathName()
{
    TCHAR name[MAX_PATH];
    if ( ::GetModuleFileName(NULL, name, MAX_PATH) )
		return SMString(name);

	return SMString("");
}


//---------------Copyright (c) 1997 Smith Micro Software, Inc.-----------------
// A do nothing function.  Around for the EnumDesktop Function
// Authors:	DPS

BOOL CALLBACK SMProcessInfo::EnumDesktopProc(LPTSTR /*lpszDesktop*/, LPARAM /*lParam*/)
{
	// let the iteration happen, just don't do anything with the result
	return (TRUE);
}



//--------------Copyright © 2007-2008 Smith Micro Software, Inc.----------------
// Helper function to see which function space we are running in system space.
// The idea here is to check first if the application has access to the desktop.
// If no desktop access is available, this usually means that the application is
// running in system space, however if it was granted desktop access through the
// "Allow service to interact with desktop" option, it won't pass this first check.
// The second check detects which user is associated with the running process, if
// it is one of the system level users (SYSTEM, LOCAL SERVICE, or NETWORK SERVICE),
// then we can assume it is running in system space.
// TODO: Check if we can remove the first check (EnumDesktops) and just rely on
//       the logged on user.
// Authors:	DPS, AR

bool SMProcessInfo::IsProcessInSystemSpace(void)
{
    bool bInSystemSpace = false;
    HWINSTA hStation = GetProcessWindowStation();

    if (hStation != NULL)
    {
        // Most service applications do not communicate with the desktop so this should be good...
        if (EnumDesktops(hStation, (DESKTOPENUMPROC) EnumDesktopProc, NULL) == FALSE)
        {
            // NT running under the System address space gets here
            bInSystemSpace = true;
        }
        else
        {
            // ...but for services that allow access to the desktop, this check will fail, 

			// There is a problem with the original logic below, in that it does not support localization, i.e. "SYSTEM" (english) != "SYSTEEM" (dutch).
			/*
            // so let's detect the user associated with the calling thread.
            static const int USER_NAME_SIZE = 256;
            static const char SYSTEM_USER_NAME[] = "SYSTEM";
            static const char LOCAL_SERVICE_USER_NAME[] = "LOCAL SERVICE";
            static const char NETWORK_SERVICE_USER_NAME[] = "NETWORK SERVICE";
            DWORD dwUserNameSize = USER_NAME_SIZE;
            char szUserName[USER_NAME_SIZE];
            ::GetUserName(szUserName, &dwUserNameSize);

            if ((::_strcmpi(szUserName, SYSTEM_USER_NAME) == 0) || 
                (::_strcmpi(szUserName, LOCAL_SERVICE_USER_NAME) == 0) ||
                (::_strcmpi(szUserName, NETWORK_SERVICE_USER_NAME) == 0))
            {
                // only system users should get in here.
                bInSystemSpace = true;
            }
			*/

            // so let's detect if the process is running with system privilege.
			HANDLE hProcess = NULL;
			HANDLE token = NULL;

			hProcess = ::GetCurrentProcess();

			if (hProcess)
			{
				if (OpenProcessToken(hProcess, TOKEN_READ, &token))
				{
					DWORD dwLength = 0;
					
					// First call GetTokenInformation with NULL buffer to get required buffer size
					GetTokenInformation(token, TokenPrivileges, NULL, 0, &dwLength);

					if (dwLength > 0)
					{
						TOKEN_PRIVILEGES *ptp;
						DWORD dwSize = 1023;
						char szName[1024];

						szName[0] = 0;
						ptp = (TOKEN_PRIVILEGES *) malloc(dwLength);
						if (ptp)
						{
							if (GetTokenInformation(token, TokenPrivileges, ptp, dwLength, &dwLength))
							{
								int i;
								for ( i = 0; i < (int) ptp->PrivilegeCount; ++ i )
								{
									if (LookupPrivilegeName(NULL, &ptp->Privileges[i].Luid, szName, &dwSize))
									{
										if (strcmp("SeTcbPrivilege", szName) == 0) // System process privilege
											bInSystemSpace = true;
									}
								}
							}
							free (ptp);
						}
					}
				}
			}
        }
    }
    // ...else... Windows 9x gets here

    return bInSystemSpace;
}


//--------------Copyright © 2007-2008 Smith Micro Software, Inc.----------------
// This function detects if the current process is running as service.  The
// idea is that a service would attach ServiceMain at startup.

bool SMProcessInfo::IsProcessAService()
{
    bool bProcessAService = false;

    SERVICE_TABLE_ENTRY serviceTableEntry;
    ::ZeroMemory(&serviceTableEntry, sizeof(SERVICE_TABLE_ENTRY));
    if (!::StartServiceCtrlDispatcher(&serviceTableEntry))
    {
        DWORD dwLastError = ::GetLastError();
        // A service would fail StartServiceCtrlDispatcher with one of the two error codes.
        if (dwLastError == ERROR_FAILED_SERVICE_CONTROLLER_CONNECT)
        {
            bProcessAService = true;
        }
    }
    // ...else all other conditions would indicate that we're running as a regular user.

    return bProcessAService;
}

SMString SMProcessInfo::GetVersionOther( const TCHAR* MODULE_NAME ) 
{
	SMString modName;
	if ( MODULE_NAME )
		modName = MODULE_NAME;
	else
		modName = GetProcessFullPathName();

	std::vector<BYTE> info = GetVersionInfo( modName.Data() );
	if ( info.empty() )
		return "";

	stringstream key;
	key << "\\StringFileInfo\\" 
		<< setw(4) << setfill('0') << hex << LANG
		<< setw(4) << setfill('0') << hex << PAGE;

	stringstream versionOther;
	for ( int i = 0; i < NUM_VERSION_SUBKEYS; i++ )
	{
		stringstream ssubkey;
		ssubkey << key.str() << "\\" << VERSION_SUBKEYS[i];
		string subkey = ssubkey.str();
		const LPSTR lpKey = const_cast<LPSTR>(subkey.c_str());
		wchar_t* pValue = 0;
		UINT sizeValue = 0;
		if ( !VerQueryValueA(&info[0], lpKey, 
				reinterpret_cast<LPVOID*>(&pValue), &sizeValue) )
			continue;

		versionOther << VERSION_SUBKEYS[i] << ": " << (char*)pValue << "  ";
	}

	return versionOther.str();
}


SMString SMProcessInfo::GetVersionNumber( const TCHAR* MODULE_NAME ) 
{
	SMString modName;
	if ( MODULE_NAME )
		modName = MODULE_NAME;
	else
		modName = GetProcessFullPathName();

	std::vector<BYTE> info = GetVersionInfo( modName.Data() );
	if ( info.empty() )
		return "";

	LPVOID pVi = 0;
	UINT sizeVi = 0;
	if ( !VerQueryValue(&info[0], _T("\\"), &pVi, &sizeVi) )
		return "";

	// We can't do anything if the structure doesn't match the expected size.
	// It's also a security flaw to ignore this check.
	if ( sizeVi != sizeof(VS_FIXEDFILEINFO) )
		return "";

	VS_FIXEDFILEINFO* pVsffi = reinterpret_cast<VS_FIXEDFILEINFO*>(pVi);
	stringstream versionNumber;
	versionNumber 
		<< "file: " 
		<< ((pVsffi->dwFileVersionMS >> 16) & 0x0000FFFF) << "." 
		<< (pVsffi->dwFileVersionMS & 0x0000FFFF) << "." 
		<< ((pVsffi->dwFileVersionLS >> 16) & 0x0000FFFF) << "."
		<< (pVsffi->dwFileVersionLS & 0x0000FFFF) << "  "
		<< "prod: "
		<< ((pVsffi->dwProductVersionMS >> 16) & 0x0000FFFF) << "."
		<< (pVsffi->dwProductVersionMS & 0x0000FFFF) << "."
		<< ((pVsffi->dwProductVersionLS >> 16) & 0x0000FFFF) << "."
		<< (pVsffi->dwProductVersionLS & 0x0000FFFF);

	return versionNumber.str();
}

//----------------------------------------------------------------------------
// EOF