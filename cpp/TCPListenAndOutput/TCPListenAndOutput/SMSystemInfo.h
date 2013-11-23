//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMSystemInfo.h $
//  Package : SMConnectManagerTest
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
//  information such as OS Version, Hard Drive Serial Number,...
//
//----------------------------------------------------------------------------

//#region Source control file history
// $History: SMSystemInfo.h $
// 
// *****************  Version 12  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 11  *****************
// User: Vtokarev     Date: 2/11/08    Time: 5:23a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Hidden properties of location profile
// 
// *****************  Version 10  *****************
// User: Ozhuk        Date: 1/15/08    Time: 5:23p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// SMS Messaging commands added.
// 
// *****************  Version 9  *****************
// User: Sanderson    Date: 11/06/07   Time: 3:58p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added timestamp to notifications
// 
// *****************  Version 8  *****************
// User: Sanderson    Date: 10/02/07   Time: 3:27p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Chagnes to fix HEAP errors
// 
// *****************  Version 6  *****************
// User: Arodriguez   Date: 8/01/07    Time: 6:41p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added IsRunningNT() and refactored retrieving the OSVersionInfo.
// 
// *****************  Version 5  *****************
// User: Arodriguez   Date: 6/15/07    Time: 4:20p
// Updated in $/Mobile/SMUtilities
// Added check for Vista or later.
// 
// *****************  Version 4  *****************
// User: Arodriguez   Date: 5/30/07    Time: 10:52a
// Updated in $/Mobile/SMUtilities
// Depending if the application is running in service or user mode, the
// trace utility reads from HKCU and outputs to My Documents in user mode,
// and HKLM and outputs to \SMTraceLog in service mode.
// 
// *****************  Version 3  *****************
// User: Arodriguez   Date: 5/25/07    Time: 2:01p
// Updated in $/Mobile/SMUtilities
// Exposed SMSystemInfo to the external interface.
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

#pragma once

#include "SMUtilitiesLink.h"
#include "SMString.h"

class SMUTILITIES_API SMSystemInfo
{
public:
    //------------------------------------------------------------------------
    // Drive helper functions:

    // Get the serial number of the hard drive specified by drive letter.
    static DWORD GetHardDriveSerialNumber(char chDriveLetter);


    // Assuming a path of "C:\Program Files\Smith Micro" + IDS_PRODUCT_NAME + "\main.exe",
    // these functions return the following parts:
    // Returns "C:\Program Files\SmithMicro" + IDS_PRODUCT_NAME + "\"
    static SMString GetFilePath     (const char* psFileSpec);
    // Returns "main.exe"
    static SMString GetFileName     (const char* psFileSpec);
    // Returns "main"
    static SMString GetFileBaseName (const char* psFileSpec);
    // Returns "exe"
    static SMString GetFileExtension(const char* psFileSpec);

    // Detects if the system is running Microsoft Windows Vista or later
    static bool IsRunningVistaOrLater();
    // Detects if the system is running Microsoft Windows NT or later
    static bool IsRunningNT();
    // Detects if the system is running Microsoft Windows 2000 or later
    static bool IsRunningWin2000();
    // Detects if the system is running Microsoft Windows XP or later
    static bool IsRunningWinXP();
    // Detects if the system is running Microsoft Windows 2000 service pack 4 or later
	static bool IsWin2000SP4Installed();

	// Return local time in sortable format with GMT time zone offset
	static SMString GetLocalTimestamp();
	static SMString FormatTimestamp(SYSTEMTIME sSystemTime);

	static SMString GetNetworkDomain();
	static SMString GetMACAddress(const char* ip);

private:
    // Prevent construction of SMSystemInfo.
    SMSystemInfo(void);
    ~SMSystemInfo(void);

    // Disable compiler generation of copy constructor & assignment operator.
    SMSystemInfo           (const SMSystemInfo&);
    SMSystemInfo& operator=(const SMSystemInfo&);

    // System Info Fields.
    static const int MAXIMUM_HARD_DRIVES = 26;
    DWORD m_dwHardDriveSerialNumber[MAXIMUM_HARD_DRIVES];
    SMString m_sProcessPath;
    SMString m_sProcessBaseName;
    SMString m_sHeapInformation;

    // OS Version
    static OSVERSIONINFOEX s_OSVersionInfo;
    static bool s_bOSVersionInitialized;
    static const OSVERSIONINFOEX& GetOSVersionInfo();
};
