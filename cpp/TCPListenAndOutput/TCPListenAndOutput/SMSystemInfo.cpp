//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMSystemInfo.cpp $
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
//  $Author: Arodriguez $
//  $Date: 2/15/08 3:08p $
//  $Modtime: 2/15/08 2:50p $
//  $Revision: 12 $
//
//  This class represents a set of methods that retrieves pertinent system 
//  information such as OS Version, Hard Drive Serial Number, Process Information...
//
//----------------------------------------------------------------------------

//#region Source control file history
// $History: SMSystemInfo.cpp $
// 
// *****************  Version 12  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 11  *****************
// User: Vtokarev     Date: 2/14/08    Time: 11:44a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Retrieving network parameters for profile creation
// 
// *****************  Version 10  *****************
// User: Vtokarev     Date: 2/11/08    Time: 5:23a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Hidden properties of location profile
// 
// *****************  Version 9  *****************
// User: Ozhuk        Date: 1/15/08    Time: 5:23p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// SMS Messaging commands added.
// 
// *****************  Version 8  *****************
// User: Sanderson    Date: 11/06/07   Time: 3:58p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added timestamp to notifications
// 
// *****************  Version 7  *****************
// User: Sanderson    Date: 10/02/07   Time: 3:27p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Chagnes to fix HEAP errors
// 
// *****************  Version 5  *****************
// User: Arodriguez   Date: 8/01/07    Time: 6:41p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added IsRunningNT() and refactored retrieving the OSVersionInfo.
// 
// *****************  Version 4  *****************
// User: Arodriguez   Date: 6/15/07    Time: 4:20p
// Updated in $/Mobile/SMUtilities
// Added check for Vista or later.
// 
// *****************  Version 3  *****************
// User: Arodriguez   Date: 5/30/07    Time: 10:52a
// Updated in $/Mobile/SMUtilities
// Depending if the application is running in service or user mode, the
// trace utility reads from HKCU and outputs to My Documents in user mode,
// and HKLM and outputs to \SMTraceLog in service mode.
// 
// *****************  Version 2  *****************
// User: Arodriguez   Date: 4/17/07    Time: 6:17p
// Updated in $/Mobile/SMUtilities
// Added process related utility functions.
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 3/13/07    Time: 6:01p
// Created in $/Mobile/SMUtilities
// Added encrypion and system information.
//#endregion

#include "StdAfx.h"
#include "SMString.h"
#include "SMSystemInfo.h"
#include "SMTraceUtility.h"

//-Static Members-------------------------------------------------------------

OSVERSIONINFOEX SMSystemInfo::s_OSVersionInfo;
bool SMSystemInfo::s_bOSVersionInitialized = false;


//----------------------------------------------------------------------------
// Retrieves the hard drive serial number based on the drive letter specified
// in chDriveLetter.

DWORD SMSystemInfo::GetHardDriveSerialNumber(char chDriveLetter)
{
    SMString sDirectory = chDriveLetter;
    sDirectory += ":\\";

    // Get hard drive volume information
    DWORD dwSerialNumber = 0;
	::GetVolumeInformation(sDirectory, NULL, 255, &dwSerialNumber, NULL, NULL, NULL, 255);

    return dwSerialNumber;
}



//----------------------------------------------------------------------------
// Assuming a path of "C:\Program Files\Smith Micro" + IDS_PRODUCT_NAME + "\main.exe",
// this function returns "C:\Program Files\Smith Micro" + IDS_PRODUCT_NAME + "\main.exe".

SMString SMSystemInfo::GetFilePath(const char* psFileSpec)
{
    SMString sFileSpec(psFileSpec);
    SMString sFileName = GetFileName(psFileSpec);
    return sFileSpec.Left(sFileSpec.GetLength() - sFileName.GetLength());
}


//----------------------------------------------------------------------------
// Assuming a path of "C:\Program Files\Smith Micro" + IDS_PRODUCT_NAME + "\main.exe",
// this function returns "main.exe".

SMString SMSystemInfo::GetFileName(const char* psFileSpec)
{
    SMString sFileSpec(psFileSpec);
    return sFileSpec.RightSpanExcluding("/\\");
}


//----------------------------------------------------------------------------
// Assuming a path of "C:\Program Files\Smith Micro" + IDS_PRODUCT_NAME + \main.exe",
// this function returns IDS_PRODUCT_NAME.

SMString SMSystemInfo::GetFileBaseName(const char* psFileSpec)
{
    SMString sFileName  = GetFileName(psFileSpec);
    int       nExtLength = sFileName.RightSpanExcluding(".").GetLength();
    return (nExtLength > 0 ? sFileName.Left(sFileName.GetLength() - nExtLength - 1) : sFileName);
}


//----------------------------------------------------------------------------
// Assuming a path of "C:\Program Files\Smith Micro" + IDS_PRODUCT_NAME + "\main.exe",
// this function returns "exe".

SMString SMSystemInfo::GetFileExtension(const char* psFileSpec)
{
    SMString sFileName = GetFileName(psFileSpec);
    return sFileName.RightSpanExcluding(".");
}


//----------------------------------------------------------------------------
// Detects if the system is running Microsoft Windows Vista or later

bool SMSystemInfo::IsRunningVistaOrLater()
{
    return ((GetOSVersionInfo().dwPlatformId == VER_PLATFORM_WIN32_NT) && (GetOSVersionInfo().dwMajorVersion >= 6));
}


//----------------------------------------------------------------------------
// Detects if the system is running Microsoft Windows NT or later

bool SMSystemInfo::IsRunningNT()
{
    return (GetOSVersionInfo().dwPlatformId == VER_PLATFORM_WIN32_NT);
}


//----------------------------------------------------------------------------
// Detects if the system is running Microsoft Windows 2000 or later

bool SMSystemInfo::IsRunningWin2000(void)
{
	if (GetOSVersionInfo().dwPlatformId == VER_PLATFORM_WIN32_NT)
	{
		return (GetOSVersionInfo().dwMajorVersion >= 5);
	}
	return (FALSE);
}


//----------------------------------------------------------------------------
// Detects if the system is running Microsoft Windows XP or later

bool SMSystemInfo::IsRunningWinXP(void)
{
	if (GetOSVersionInfo().dwPlatformId == VER_PLATFORM_WIN32_NT)
	{
		if (GetOSVersionInfo().dwMajorVersion > 5)
			return TRUE;

		if ((GetOSVersionInfo().dwMajorVersion == 5) && (GetOSVersionInfo().dwMinorVersion >= 1))
			return (TRUE);
	}
	return (FALSE);
}

//----------------------------------------------------------------------------
// Detects if the system is running Microsoft Windows 2000 Service Pack 4 or later

bool SMSystemInfo::IsWin2000SP4Installed(void)
{
	if (IsRunningWin2000())
	{
		if (GetOSVersionInfo().wServicePackMajor >= 4)
			return TRUE;
	}
	return FALSE;
}


//----------------------------------------------------------------------------
// Gets the OS Version Info structure.

const OSVERSIONINFOEX& SMSystemInfo::GetOSVersionInfo()
{
    if (!s_bOSVersionInitialized)
    {
    	s_OSVersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	    GetVersionEx((LPOSVERSIONINFO) &s_OSVersionInfo);
        s_bOSVersionInitialized = true;
    }

    return s_OSVersionInfo;
}

//----------------------------------------------------------------------------
// Return local time in sortable format with GMT time zone offset

SMString SMSystemInfo::GetLocalTimestamp(void)
{
	SMString sTime;
	SYSTEMTIME sSystemTime;
	TIME_ZONE_INFORMATION sTZInfo;
	DWORD dwDaylight;

	// Get local time
	GetLocalTime(&sSystemTime);
	
	// Calculate GMT time zone offset in -/+HH:MM format
	dwDaylight = GetTimeZoneInformation(&sTZInfo);
	int nBias = sTZInfo.Bias;
	if (dwDaylight == TIME_ZONE_ID_DAYLIGHT)
		nBias += sTZInfo.DaylightBias;
	if (dwDaylight == TIME_ZONE_ID_STANDARD)
		nBias += sTZInfo.StandardBias;
	
	sTime.Format("%d-%.2d-%.2dT%.2d:%.2d:%.2d.%d%+.2d:%.2d",
		sSystemTime.wYear,
		sSystemTime.wMonth,
		sSystemTime.wDay,
		sSystemTime.wHour,
		sSystemTime.wMinute,
		sSystemTime.wSecond,
		sSystemTime.wMilliseconds,
		- (nBias / 60), // inverse for localtime relative to UTC(GMT)
		abs(nBias % 60));

	return sTime;
}

//----------------------------------------------------------------------------
// Return time in sortable format with GMT time zone offset
SMString SMSystemInfo::FormatTimestamp(SYSTEMTIME sSystemTime)
{
	SMString sTime;
	TIME_ZONE_INFORMATION sTZInfo;
	DWORD dwDaylight;
	
	// Calculate GMT time zone offset in -/+HH:MM format
	dwDaylight = GetTimeZoneInformation(&sTZInfo);
	int nBias = sTZInfo.Bias;
	if (dwDaylight == TIME_ZONE_ID_DAYLIGHT)
		nBias += sTZInfo.DaylightBias;
	if (dwDaylight == TIME_ZONE_ID_STANDARD)
		nBias += sTZInfo.StandardBias;
	
	sTime.Format("%d-%.2d-%.2dT%.2d:%.2d:%.2d.%d%+.2d:%.2d",
		sSystemTime.wYear,
		sSystemTime.wMonth,
		sSystemTime.wDay,
		sSystemTime.wHour,
		sSystemTime.wMinute,
		sSystemTime.wSecond,
		sSystemTime.wMilliseconds,
		- (nBias / 60), // inverse for localtime relative to UTC(GMT)
		abs(nBias % 60));

	return sTime;
}

SMString SMSystemInfo::GetNetworkDomain()
{
	FIXED_INFO * FixedInfo;
	ULONG    ulOutBufLen;
	
	FixedInfo = (FIXED_INFO *) GlobalAlloc( GPTR, sizeof( FIXED_INFO ) );
	ulOutBufLen = sizeof( FIXED_INFO );

	if( ERROR_BUFFER_OVERFLOW == GetNetworkParams( FixedInfo, &ulOutBufLen ) ) 
	{
		GlobalFree( FixedInfo );
		FixedInfo = (FIXED_INFO *) GlobalAlloc( GPTR, ulOutBufLen );
	}

	SMString res;
	if ( ERROR_SUCCESS != GetNetworkParams( FixedInfo, &ulOutBufLen ) ) 
	{
		SM_TRACE(1, "Call to GetNetworkParams failed.");
	}
	else 
	{
		res = FixedInfo->DomainName;
	}
	GlobalFree(FixedInfo);
	return res;
}

SMString SMSystemInfo::GetMACAddress(const char* ip)
{
	IPAddr  ipAddr;
    ULONG   pulMac[2];
    ULONG   ulLen;

    ipAddr = inet_addr (ip);
    memset (pulMac, 0xff, sizeof (pulMac));
    ulLen = 6;
    
    if ( NO_ERROR != SendARP (ipAddr, 0, pulMac, &ulLen) )
	{
		SM_TRACE(1, "SendARP failed.");
		return "";
	}
    
    PBYTE pbHexMac = (PBYTE) pulMac;
	SMString res;
    //
    // Convert the binary MAC address into human-readable
    //
    for ( size_t i = 0; i < ulLen; ++i ) 
	{
		SMString s;
		s.Format("%02X", pbHexMac[i]);
		if ( i > 0 ) res += ":";
		res += s;
    }
    
    return res;
}

//----------------------------------------------------------------------------
// EOF